/** An examples that shows how to handle packets in the ISR.
 * You need two nodes to run this example, one will be the
 * receiver, the other will be the sender.
 */
#include <SPI.h>
#include <nRF24.h>

byte address[4] = {1,2,3,4};

//Comment this line to act as a sender
#define ROLE_RECEIVER

void setup(){
  Serial.begin(57600);
  //CE on pin 9, CS on pin 10 and IRQ on pin 2
  nRF24.configure(9,10,2);
  nRF24.init();
  nRF24.setChannel(10);
  nRF24.setPayloadSize(0, 0);
  nRF24.setAddressSize(NRF24::NRF24AddressSize4Bytes);
  nRF24.setCRC(NRF24::NRF24CRC2Bytes);
  nRF24.setRF(NRF24::NRF24DataRate2Mbps, NRF24::NRF24TransmitPower0dBm);
  nRF24.setPipeAddress(0, address);
  nRF24.enablePipe(0);
  nRF24.setAutoAck(0, true);
  
#ifdef ROLE_RECEIVER
  nRF24.enableReceiveISR();
  nRF24.setReceivedPacketHandler(0, handlePipe0);
#else
  nRF24.setTransmitAddress(address);
  nRF24.setTXRetries(3,3);
#endif
}

void handlePipe0(uint8_t * pkt, uint8_t len){
  //You shouldn't do any Serial in the ISR !!!
  //But here it is done just to show the functionality
  //hopefully it'll work
  Serial.print("Received packet: ");
  Serial.println(pkt[0]);
}

void loop(){

#ifdef ROLE_RECEIVER
  Serial.println("Just waiting...");
  delay(5000);
#else
  byte pkt[1] = {1};
  Serial.println("Sending");
  if(!nRF24.send(pkt, 1, false)) Serial.println("Cannot send");
  delay(2000);
#endif
}
