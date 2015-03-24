#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#include <Wire.h> 

void setup(){
  Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"serv1"); 
  Mirf.payload = sizeof(unsigned long); 
  Mirf.config();
}

void loop(){
  byte data[Mirf.payload];   
  if(!Mirf.isSending() && Mirf.dataReady()){
    Serial.println("Got packet");
    Mirf.getData(data);
    Serial.println(char (data[0]));
  }
}
