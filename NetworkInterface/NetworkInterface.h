/* NetworkInterface library

MIT license
written by Berto 'd Sera
*/

#ifndef NetworkInterface_h
#define NetworkInterface_h

#include "Arduino.h"
#include <Time.h>
#include <Logger.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>

#ifndef NTP_PACKET_SIZE
#define NTP_PACKET_SIZE 48 // NTP time is in the first 48 bytes of message
#endif


class NetworkInterface {
  private: 
    static const IPAddress    timeServer; 
    static const int          timeZone;
    static const unsigned int localUdpPort;  // local port to listen for UDP packets    
    static const unsigned int httpPort;    
    EthernetServer            *HTTPserver;
    EthernetUDP               *Udp;   
    byte                      packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets  
  public:    
    NetworkInterface(void);
    void   sendNTPpacket(void);
    time_t getNtpTime(void);
    String getSunriseSunset(String, String);
    void   homepage(void);    
};

//extern NetworkInterface *eth0;

#endif