/** A simple test that sets a series of properties
 * on the nRF24+ and checks that they are well set.
 */

#include <nRF24.h>
#include <SPI.h>

void setup()
{
    Serial.begin(57600);
    Serial.println("nRF24 test");
    nRF24.configure(9,10);
    nRF24.init();
    Serial.println("initialized");
    delay(500);
    Serial.print("powered up? ");
    boolean result = nRF24.isPoweredUp();
    Serial.println(result);
    
    Serial.print("set address size? ");
    result = nRF24.setAddressSize(NRF24::NRF24AddressSize4Bytes);
    Serial.println(result);
    Serial.print("address size: ");
    int sz = nRF24.getAddressSize()+2;
    Serial.println(sz);
    
    Serial.print("set CRC? ");
    result = nRF24.setCRC(NRF24::NRF24CRC2Bytes);
    Serial.println(result);
    
    Serial.print("set pipe 1 address? ");
    result = nRF24.setPipeAddress(1,(uint8_t*)"abcd");
    Serial.println(result);
    uint8_t address[sz];
    nRF24.getPipeAddress(1, address);
    printAdddress(address, sz);
    
    Serial.print("set pipe 2 address? ");
    result = nRF24.setPipeAddress(2,(uint8_t*)"abce");
    Serial.println(result);
    nRF24.getPipeAddress(2, address);
    printAdddress(address, sz);
    
    Serial.print("enable pipe 2? ");
    result = nRF24.enablePipe(2);
    Serial.println(result);
    
    Serial.print("enable auto ack on 2? ");
    result = nRF24.setAutoAck(2, true);
    Serial.println(result);
    
    Serial.print("set channel??");
    result = nRF24.setChannel(10);
    Serial.println(result);
    
    Serial.print("set trans address? ");
    result = nRF24.setTransmitAddress((uint8_t*)"efgh");
    Serial.println(result);
    nRF24.getTransmitAddress(address);
    printAdddress(address, sz);
    
    Serial.print("set payload dyn size? ");
    result = nRF24.setPayloadSize(2, 0);
    Serial.println(result);
    
    Serial.print("set payload fixed size? ");
    result = nRF24.setPayloadSize(2, 3);
    Serial.println(result);
    
    Serial.print("RPD: ");
    result = nRF24.getRPD();
    Serial.println(result);
    
    Serial.print("RSSI: ");
    uint8_t rssi = nRF24.getRPD();
    Serial.println(rssi);
}

void printAdddress(uint8_t * address, int len){
  for(int i=0; i< len-1; i++){
    Serial.print(address[i]);
    Serial.print(".");
    }
  Serial.println(address[len-1]);
 }

void loop()
{

}

