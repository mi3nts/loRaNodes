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

// void initializeLora(){
//     SerialUSB.println("LORAWAN MINTS");
//     SerialUSB.println("System booting...");
//     SerialUSB.println("Initiating LoRa");
//     lora.init();
//     SerialUSB.println("Resetting Devices");
//     lora.setDeviceReset();

//     char buffer[256];
//     char id[10];
//     SerialUSB.println("Setting Lora Credentials");
//     memset(buffer, 0, 256);
//     lora.getId(buffer, 256, 1);
//     SerialUSB.print(buffer);
//     readID(id, buffer);
//     lora.setKey("312F851628AED2A6ABF7159999CF4F3C", "312F851628AED2A6ABF7159999CF4F3C","312F851628AED2A6ABF7159999CF4F3C");
//     lora.setDeciveMode(LWOTAA);
//     lora.setDataRate(DR3, US915HYBRID);
//     lora.setChannel(0, 902.3);
//     lora.setChannel(1, 902.5);
//     lora.setChannel(2, 902.7);
//     lora.setReceiceWindowFirst(0, 902.3);
//     lora.setReceiceWindowSecond(923.3, DR3);
//     lora.setAdaptiveDataRate(false);
//     lora.setDutyCycle(false);
//     lora.setJoinDutyCycle(false);
//     lora.setPower(14);

//     SerialUSB.println("System booted!");
//     while(!lora.setOTAAJoin(JOIN));



// }
