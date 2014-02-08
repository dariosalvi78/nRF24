/** A simple sketch that sends data using Enanched Shockburst
 * You need two nodes, one will be the receiver, the other
 * will be the sender.
 */
#include <SPI.h>
#include <nRF24.h>

byte address[4] = {1,2,3,4};

//Comment this line to act as a sender
#define ROLE_RECEIVER


void setup(){
  Serial.begin(57600);
  nRF24.configure(9,10);
  nRF24.init();
  nRF24.setChannel(10);
  nRF24.setPayloadSize(0, 0);
  nRF24.setAddressSize(NRF24::NRF24AddressSize4Bytes);
  nRF24.setCRC(NRF24::NRF24CRC2Bytes);
  nRF24.setRF(NRF24::NRF24DataRate2Mbps, NRF24::NRF24TransmitPower0dBm);
  nRF24.setPipeAddress(0, address);
  nRF24.enablePipe(0);
  nRF24.setAutoAck(0, true);
  
  nRF24.setTransmitAddress(address);
  nRF24.setTXRetries(3,3);
}

void handlePipe0(uint8_t * pkt, uint8_t len){
  Serial.print("Received packet: ");
  Serial.println(pkt[0]);
}

void loop(){
byte pkt[1] = {1};
#ifdef ROLE_RECEIVER
  Serial.println("Waiting for packet");
  byte pipe;
  byte len;
  if(nRF24.waitAvailableTimeout(5000)){
     if(nRF24.recv(&pipe, pkt, &len)){
           Serial.print("received packet: ");
           Serial.println(pkt[0]);
        } else Serial.println("Can't get the packet");
  }else Serial.println("Receive timeout");
#else
  Serial.println("Sending");
  if(!nRF24.send(pkt, 1, false)) Serial.println("Cannot send");
  delay(2000);
#endif
}
