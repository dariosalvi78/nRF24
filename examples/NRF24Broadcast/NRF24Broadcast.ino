/** A simple sketch that sends packets in broadcast.
 * You need at least 2 nodes to run it, for each node change
 * the ME value, this value will be sent by the node to the others.
 */
#include <SPI.h>
#include <nRF24.h>

#define ME 1

byte address[4] = {1,2,3,4};

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
  nRF24.setAutoAck(0, false);
}

void loop(){
  byte pkt[1] = {ME};
  
  nRF24.setTransmitAddress(address);
  Serial.print("Sending broadcast ");
  Serial.println(ME);
  if(!nRF24.send(pkt, 1, true)) Serial.println("Cannot send");
  //delay(1000);
  
  Serial.println("Waiting for packet");
  byte pipe;
  byte len;
  if(nRF24.waitAvailableTimeout(5000)){
     if(nRF24.recv(&pipe, pkt, &len)){
           Serial.print("received packet from ");
           Serial.println(pkt[0]);
        } else Serial.println("Can't get the packet");
  }else Serial.println("Receive timeout");
  
}
