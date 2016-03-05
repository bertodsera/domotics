/* Generic Pin library

MIT license
written by Berto 'd Sera
*/
#include "Arduino.h"
#include <Time.h>
#include <Logger.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetServer.h>
#include <EthernetClient.h>
#include <EthernetUdp.h>
#include <NetworkInterface.h>

const IPAddress    NetworkInterface::timeServer(192, 168, 0, 18); 
const int          NetworkInterface::timeZone = 0;         // GMT
const unsigned int NetworkInterface::httpPort = 80;        // Http service port
const unsigned int NetworkInterface::localUdpPort = 8888;  // local port to listen for UDP packets  

NetworkInterface::NetworkInterface(void) {  
  const char *msgIP = "IP number assigned by DHCP is ";    
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };  
  //log("NetworkInterface::NetworkInterface Starting");  
  
  if (Ethernet.begin(mac) == 0) {
    // no point in carrying on, so do nothing forevermore:
    while (1) {
      //log("Failed to configure Ethernet using DHCP");
      delay(10000);
    }
  }
   
  // Cannot use log() before time is initialized 
  Serial.print(msgIP);
  Serial.println(Ethernet.localIP());  
  
  bool startServer = true;
  HTTPserver = (new EthernetServer(httpPort)); 
  HTTPserver->begin();

  Udp = (new EthernetUDP);  
  Udp->begin(localUdpPort); 

  delay(2000); 
}


// send an NTP request to the time server at the given address
void NetworkInterface::sendNTPpacket(void)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
  
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:                 
  Udp->beginPacket(timeServer, 123); //NTP requests are to port 123
  Udp->write(packetBuffer, NTP_PACKET_SIZE);
  Udp->endPacket();
}


time_t NetworkInterface::getNtpTime(void) {
  while (Udp->parsePacket() > 0) ; // discard any previously received packets
  sendNTPpacket();
  
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = Udp->parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      Udp->read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }
  return 0; // return 0 if unable to get the time
}



String NetworkInterface::getSunriseSunset(String _lat, String _lng) {
  EthernetClient client;

  // build request string
  String     request               = "GET /json?lat="+_lat+"&lng="+_lng+"&date=today&formatted=0 HTTP/1.1";
  const char *server               = "api.sunrise-sunset.org";    // name address for the publishing site (using DNS)
  const char *hostHeader           = "Host: api.sunrise-sunset.org";  
  const char *connectionHeader     = "Connection: close";    
  const char *userAgentHeader      = "User-Agent: arduino-ethernet";     
  const char *acceptCharsetHeader  = "Accept-Charset: ISO-8859-1;q=0.7,*;q=0.7";  
  const char *cacheControlHeader   = "Cache-Control: no-cache";    
  const char *acceptLanguageHeader = "Accept-Language: de,en;q=0.7,en-us;q=0.3";   
  
  const char *msgDisconnected      = "NetworkInterface::getSunriseSunset got disconnected";
  const char *msgTimeOut           = "NetworkInterface::getSunriseSunset Time out or over 500 chars";
  const char *msgConnectionFailed  = "NetworkInterface::getSunriseSunset connection failed";
  
  // connect and send HTTP request
  if (client.connect(server, httpPort)) {
    // Make a HTTP request:
    client.println("GET /json?lat="+_lat+"&lng="+_lng+"&date=today&formatted=0 HTTP/1.1");
    client.println(hostHeader);  
    client.println(connectionHeader);
    client.println(userAgentHeader);    
    client.println(acceptCharsetHeader);
    client.println(cacheControlHeader);
    client.println(acceptLanguageHeader); 
    client.println();
    delay(250);
    
    // if we have a connection, read the string
    if (client.available()) {
      int  bracketCount = 0;
      int  cycles = 0;
      bool received = false;
      String json;
      char c; 

      while (not received) {
        // count passages
        cycles++;

        // if the server's disconnected, stop the client:
        if (!client.connected()) {
          log(msgDisconnected);
          client.stop();    
          received = true;
        }
        else {
          c = client.read();
          if (c=='{') { bracketCount++; }
          if (bracketCount>0) { 
            json += c;
          }          
          if (c=='}') { bracketCount--; }
          received = ( bracketCount==0 && json.length()>0 );
        }
        
        // disconnect if too long or time-out 
        if (cycles>1500 || json.length()>499) {
          received = true;
          log(msgTimeOut);
        }
      }  
      return json;
    }
  }  
  else {
    // if you didn't get a connection to the serv
    log(msgConnectionFailed);
    return " ";
  }  
}


void NetworkInterface::homepage(void) {
  // listen for incoming clients
  EthernetClient client = HTTPserver->available();
  delay(500);     

  if (client) {
    // an http request ends with a blank line
    bool currentLineIsBlank = true; 
    while (client.connected()) {
      if (client.available()) {
    
        char c = client.read();
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          
          // VASES PRESENCE LOOP
          client.println("PLANTERS<br />");          
      
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(500);
    // close the connection:
    client.flush();
    client.stop();
  }
}
