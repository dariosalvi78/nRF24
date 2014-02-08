/** A sketch that controls a RGB LED remotely.
 * One node acts as the controller and another as the LED.
 * You can control the light in the controller by sending
 * 3 numbers on the Serial line, with 3 digits each (e.g. 010 055 200)
 * or, if you press 's', by using 3 potentiometers.
 */
#include <nRF24.h>
#include <SPI.h>

//Comment this line to act as a controller
#define ROLE_LED

#ifdef ROLE_LED
//LED pins
int pinB = 3;
int pinG = 5;
int pinR = 6;
#else
boolean readSensors = false;
const int POTR = A0;
const int POTG = A1;
const int POTB = A2;
#endif


void setup()
{
  Serial.begin(57600);
  Serial.println("NRF24 RGB LED remote");
  Serial.print("ROLE: ");
#ifdef ROLE_LED
  Serial.println("LED");
  //Turn LED OFF
  setRGBLED(0, 0, 0);
#else
  Serial.println("Remote Control");
  Serial.println("Control mode: read values from serial");
  Serial.println("Sensor mode: read values from analog inputs");
  Serial.println("Press s to switch to sensor mode, anything else to quit");
#endif

  nRF24.configure(9, 10);
  nRF24.init();
  nRF24.setChannel(10);
  nRF24.setPayloadSize(1, 3);
  nRF24.setAddressSize(NRF24::NRF24AddressSize4Bytes);   
  nRF24.setCRC(NRF24::NRF24CRC1Byte);
  nRF24.setRF(NRF24::NRF24DataRate2Mbps, NRF24::NRF24TransmitPower0dBm);

#ifdef ROLE_LED
  //receive on pipe 1
  nRF24.setPipeAddress(1, (uint8_t*)"ledr");
  nRF24.enablePipe(1);
  nRF24.setAutoAck(1, true);
  nRF24.powerUpRx();
  
#else //ROLE_CONTROL
  nRF24.setTXRetries(3, 3);
  nRF24.setTransmitAddress((uint8_t*)"ledr");
  nRF24.powerUpTx();
#endif
  Serial.println("NRF24 initialised!");
}

#ifndef ROLE_LED //ROLE_CONTROL
void send(uint8_t * RGB){
  if (!nRF24.send(RGB, 3))
    Serial.print("Could not send: ");
  else
    Serial.print("Sent: ");

  Serial.print(RGB[0]);
  Serial.print(" ");
  Serial.print(RGB[1]);
  Serial.print(" ");
  Serial.println(RGB[2]);
}
#endif

void loop()
{

#ifdef ROLE_LED
  //Receive 3 values and set the color
  Serial.println(digitalRead(2));
  Serial.println("waiting");
  uint8_t len = 3;
  uint8_t pipe = 0;
  uint8_t RGB[3];
  nRF24.waitAvailable();
  Serial.println(digitalRead(2));
  if (!nRF24.recv(&pipe, RGB, &len))
    Serial.println("read failed");

  Serial.print("Got data on pipe ");
  Serial.print(pipe);
  Serial.print(" : ");
  Serial.print(RGB[0]);
  Serial.print(" ");
  Serial.print(RGB[1]);
  Serial.print(" ");
  Serial.println(RGB[2]);
  
  setRGBLED(RGB[0], RGB[1], RGB[2]);
#else //ROLE_CONTROL
  uint8_t RGB[3];
  if(Serial.available()){
    String s = Serial.readStringUntil('\n');
    if(s.length() == 1){
      if(s.startsWith("s")){
        readSensors = true;
        Serial.println("Set to sensor mode");
      }
      else{
        readSensors = false;
        Serial.println("Set to command mode");
      }
    }
    else if(s.length() == 11){
      RGB[0]= s.substring(0,3).toInt();
      RGB[1]= s.substring(4,7).toInt();
      RGB[2]= s.substring(8,11).toInt();
      send(RGB);
    }
  }
  if(readSensors){
    boolean changed = false;
    int potr = map(analogRead(POTR), 0, 1024, 0, 255);
    if(potr != RGB[0]){
      RGB[0] = potr;
      changed = true;
    }
    int potg = map(analogRead(POTG), 0, 1024, 0, 255);
    if(potg != RGB[1]){
      RGB[1] = potg;
      changed = true;
    }
    int potb = map(analogRead(POTB), 0, 1024, 0, 255);
    if(potb != RGB[2]){
      RGB[2] = potb;
      changed = true;
    }
    if(changed)
      send(RGB);
  }
#endif
}



#ifdef ROLE_LED
void setRGBLED(int r, int g, int b){
  if(r==0)
    digitalWrite(pinR, HIGH);
  else
    analogWrite(pinR, 255-r);
  if(g==0)
    digitalWrite(pinG, HIGH);
  else
    analogWrite(pinG, 255-g);
  if(b==0)
    digitalWrite(pinB, HIGH);
  else
    analogWrite(pinB, 255-b);
}
#endif



