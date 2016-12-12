// A simple web server that always just says "Hello World"

#include "etherShield.h"
#include "ETHER_28J60.h"

int api;
int sensorAsap = A0; 
int sensorAsapValue = 0;

static uint8_t mac[6] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x24};   // this just needs to be unique for your network, 
                                                                // so unless you have more than one of these boards
                                                                // connected, you should be fine with this value.
                                                           
static uint8_t ip[4] = {192, 168, 1, 179};                       // the IP address for your board. Check your home hub
                                                                // to find an IP address not in use and pick that
                                                                // this or 10.0.0.15 are likely formats for an address
                                                                // that will work.

static uint16_t port = 80;                                      // Use port 80 - the standard for HTTP

ETHER_28J60 ethernet;

void setup()
{ 
Serial.begin(9600);
pinMode (4, INPUT);
ethernet.setup(mac, ip, port);
}

void loop()
{
sensorAsapValue = analogRead(sensorAsap);
api = digitalRead(4);
Serial.println(sensorAsapValue);
if (sensorAsapValue > 260) 
Serial.println("Status Asap : YES");
if (sensorAsapValue < 260)
Serial.println("Status Asap : NO");
  
if (api == LOW) {
  Serial.println(api);
  Serial.println("Ada API");
  ethernet.print("<H3>ada api</H3>");
  }
  else {
  Serial.println("Gak ada API");
  }

  if (ethernet.serviceRequest())
  {
    ethernet.print("<H1>FIRE DETECTOR</H1>");
    ethernet.print("<H2>with</H2>");
    ethernet.print("<H1>Ethernet Shield</H1>");
    ethernet.print("<br />");  
           //ethernet.print("<a href=\"/?button1on\"\">Turn On LED</a>");
           //ethernet.print("<a href=\"/?button1off\"\">Turn Off LED</a><br />");   
                
           //ethernet.print("<br />"); 
           //ethernet.print("<a href=\"/?button2on\"\">Rotate Left</a>");
           //ethernet.print("<a href=\"/?button2off\"\">Rotate Right</a><br />"); 
           ethernet.print(api);
           ethernet.print("<br />");
           ethernet.print(sensorAsapValue);
           ethernet.print("<meta http-equiv=\"refresh\" content=\"3\">");
          
           
    ethernet.respond();
  }
   if(api== LOW){
           ethernet.print("<H3>ada api</H3>");
           }
  delay(100);
}

