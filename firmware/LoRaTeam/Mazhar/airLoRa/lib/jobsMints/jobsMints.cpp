#include "jobsMints.h"

void initializeSerialMints(){
    SerialUSB.begin(9600);
    SerialUSB.println("Serial Port Open");
}


void sensorPrintMints(String sensor,String readings[],uint8_t numOfvals){
  SerialUSB.print("#mintsO!");SerialUSB.print(sensor);SerialUSB.print(">");
  for (int i = 0; i < numOfvals; ++i)
      {
        SerialUSB.print(readings[i]);SerialUSB.print(":");
      }
      SerialUSB.print("~");
}


void loraSendMints(byte sendOut[], uint8_t numOfBytes, uint8_t timeOut, uint8_t portNum){
  SerialUSB.println("");
  lora.setPort(portNum);
  lora.transferPacket(sendOut,numOfBytes,timeOut);

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



