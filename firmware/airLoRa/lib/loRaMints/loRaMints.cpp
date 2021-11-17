#include "loRaMints.h"



void loraInitMints(char* keyIn)
{
  char buffer[256];
  SerialUSB.println("LoRa Init");
  lora.init();
  lora.setDeviceReset();
  lora.setDeviceDefault();

  SerialUSB.println("Get Module Version");
  memset(buffer, 0, 256);
  lora.getVersion(buffer, 256, 1);
  SerialUSB.println("Version");
  SerialUSB.print(buffer);

  SerialUSB.println("Get Lora Credentials");
  memset(buffer, 0, 256);
  lora.getId(buffer, 256, 1);
  SerialUSB.println("LoRa ID");
  SerialUSB.print(buffer);

  SerialUSB.println("Setting Keys");
  // char* keyIn = "312F851628AED2A6ABF7159999CF4F3C";
  lora.setKey(NULL, NULL, keyIn);
 
  SerialUSB.println("Setting LWOTAA Mode");
  lora.setDeciveMode(LWOTAA);
  lora.setDataRate(DR3, US915);
  
  lora.setChannel(0, 913.5);
  lora.setChannel(1, 913.7);
  lora.setChannel(2, 913.9);
  lora.setChannel(3, 914.1);
  lora.setChannel(4, 914.3);
  lora.setChannel(5, 914.5);
  lora.setChannel(6, 914.7);
  lora.setChannel(7, 914.9);
  lora.setReceiceWindowFirst(0,  927.5);
  lora.setReceiceWindowSecond(927.5, DR8);


  lora.setJoinDutyCycle(false);

  // SerialUSB.println("Setting Power");
  lora.setPower(14);  //###
  lora.setPort(1);
  lora.setClassType(CLASS_A);
  SerialUSB.println("Starting Join");
 
  for (uint8_t i = 1; i <= 10; i++) {{
     if(lora.setOTAAJoin(JOIN, 10)){
      SerialUSB.println("Setup Complete");
      return;
  }}}
    SerialUSB.println("No gateway found 1");
    SerialUSB.println("Delay 1: 1 Minute");
    delay (60000);
  for (uint8_t i = 1; i <= 10; i++) {{
     if(lora.setOTAAJoin(JOIN, 10)){
      SerialUSB.println("Setup Complete");
      return;
  }}} 
    SerialUSB.println("No gateway found 2");
    SerialUSB.println("Delay 2: 2 Minute");
    delay (120000);
  for (uint8_t i = 1; i <= 10; i++) {{
     if(lora.setOTAAJoin(JOIN, 10)){
      SerialUSB.println("Setup Complete");
      return;
  }}} 
  SerialUSB.println("No gateway found 2");
  SerialUSB.println("Sleeping");
  rebootBoard(rebootPin);
  delay (120000);
}

void resetLoRaMints(uint8_t numOfTrysIn,uint8_t powerMode){
  byte sendOut[1];
  uint8_t portIn = 2;
  lora.setPort(portIn);
  memcpy(sendOut,&powerMode,1);
  for (uint16_t  cT = 1 ;cT<numOfTrysIn ; cT++){
     if(lora.transferPacketCheck(sendOut,2,5)){
        SerialUSB.println("Gateway Contacted");
       break;
     }
    // delay(1000);
  } 
}


void loRaSendMints(byte sendOut[], uint8_t numOfBytes, uint8_t timeOut, uint8_t portNum){
  SerialUSB.println("");
  lora.setPort(portNum);
  lora.transferPacket(sendOut,numOfBytes,timeOut);
}



byte sensorPrintBytes(String sensor,byte readings[],uint8_t numOfvals){

  SerialUSB.print("#mintsB!");SerialUSB.print(sensor);SerialUSB.print(">");
  for (int i = 0; i < numOfvals; ++i)
      {
        SerialUSB.print(readings[i]);SerialUSB.print(":");
      }
      SerialUSB.print("~");
}


void sensorPrintFloats(String sensor,float readings[],uint8_t numOfvals){
  SerialUSB.print("#mintsF!");SerialUSB.print(sensor);SerialUSB.print(">");
  for (int i = 0; i < numOfvals; ++i)
      {
        SerialUSB.print(String(readings[i]));SerialUSB.print(":");
      }
      SerialUSB.print("~");
}

void sensorPrintULongs(String sensor,unsigned long readings[],uint8_t numOfvals){
  SerialUSB.print("#mintsUL!");SerialUSB.print(sensor);SerialUSB.print(">");
  for (int i = 0; i < numOfvals; ++i)
      {
        SerialUSB.print(String(readings[i]));SerialUSB.print(":");
      }
      SerialUSB.print("~");
}


byte minMaxFloatMints(float inVal, float min, float max){
  if (inVal<min) {
    return 0;
  }else if (inVal>max){
    return 255;
  }else {
  return round(inVal);
  }

}

unsigned long minMaxFloat2ULongMints(float inVal, float min, float max){
  if (inVal<min) {
    return 1022;
  }else if (inVal>max){
    return 1023;
  }else {
  return round(inVal);
  }

}

//  Booting Menu 

void initializeReboot(uint8_t rebootPin){
  pinMode(rebootPin, OUTPUT); 
}

void rebootBoard(uint8_t rebootPin){
    SerialUSB.println();
    SerialUSB.println("Rebooting Board");
    digitalWrite(rebootPin, HIGH);
    delay(1);
    digitalWrite(rebootPin, LOW);
    delay(1);
}

bool readNow(bool sensorOnline,uint32_t startIn,uint32_t periodIn){
    return ((((millis() - startIn)> periodIn)&& sensorOnline));
}

void checkReboot(uint8_t powerModeIn,uint8_t rebootPinIn){
  if((powerModeIn == 1) && (millis() > 450000) ){
    rebootBoard(rebootPinIn); // Halt the board in the day after 7.5 minutes
    delay(1000000);
  }
  if((powerModeIn == 2) && (millis() > 360000) ){
    rebootBoard(rebootPinIn); // Halt the board in the day after 6 minutes
    delay(1000000);
  }

}