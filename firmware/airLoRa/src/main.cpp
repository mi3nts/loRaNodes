#include "jobsMints.h"
#include "devicesMints.h"
#include "LoRaWan.h"


bool BME280Online;
BME280 bme280; // I2C

bool SCD30Online;
SCD30 scd;

//
bool MGS001Online;

uint16_t sensingPeriod = 2417;
uint16_t initPeriod = 1500;

char buffer[256];
char id[10];

void setup()
{

  delay(initPeriod);
  initializeSerialMints();

  delay(initPeriod);
  BME280Online = initializeBME280Mints();
  
  delay(initPeriod);
  MGS001Online =  initializeMGS001Mints();

  delay(initPeriod);
  SCD30Online = initializeSCD30Mints();


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


  // SerialUSB.println("Setting Keys");
  lora.setKey(NULL, NULL, "312F851628AED2A6ABF7159999CF4F3C");
  // SerialUSB.println("Setting LWOTAA Mode");
  lora.setDeciveMode(LWOTAA);
  lora.setDataRate(DR3, US915);

  // lora.setChannel(0, 913.5);
  // lora.setChannel(1, 913.7);
  // lora.setChannel(2, 913.9);
  // lora.setChannel(3, 914.1);
  // lora.setChannel(4, 914.3);
  // lora.setChannel(5, 914.5);
  // lora.setChannel(6, 914.7);
  // lora.setChannel(7, 914.9);
  // lora.setReceiceWindowFirst(0, 913.5);
  // lora.setReceiceWindowSecond(927.5, DR8);
  
  // lora.setAdaptiveDataRate(true);
  // lora.setDutyCycle(false);

  lora.setJoinDutyCycle(false);

  // SerialUSB.println("Setting Power");
  lora.setPower(14);  //###
  lora.setPort(1);
  lora.setClassType(CLASS_A);

  SerialUSB.println("Starting Join");
  while(!lora.setOTAAJoin(JOIN, 10));


  SerialUSB.println("Setup Complete");

}

void loop()
{
    // delay(sensingPeriod);
    // if(BME280Online)
    // {
    //   readBME280Mints();
    // }
    
    // delay(sensingPeriod);
    // if(MGS001Online)
    // {
    //   readMGS001Mints();
    // }
    // // //
    // delay(sensingPeriod);
    // if(SCD30Online)
    // {
    //   readSCD30Mints();
    // }

  delay(1000);
}