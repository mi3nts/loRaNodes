
#include "jobsMints.h"
#include "devicesMints.h"
#include "loRaMints.h"
#include "LoRaWan.h"

// ADD LORA APP KEY HERE 
char* keyIn = "BA2C989028ABC216FBB7159909CE3F34";

uint8_t numOfTries = 20; 

bool GPGGALROnline;
TinyGPSPlus gpggalr;


bool BME280Online;
BME280 bme280; // I2C

bool SCD30Online;
SCD30 scd;
uint16_t SCD30ReadTime = 30;


bool IPS7100Online;
IpsSensor ips_sensor;
uint32_t IPS7100ResetTime = 30;

bool MGS001Online;

bool INA219DuoOnline;

Adafruit_INA219 ina219Battery(0x40);
Adafruit_INA219 ina219Solar(0x41);

uint8_t rebootPin = 9; 
uint8_t powerMode ;

uint32_t BME280Time    = 0;
uint32_t SCD30Time     = 0;
uint32_t MGS001Time    = 0;
uint32_t IPS7100Time   = 0;
uint32_t GPGGALRTime   = 0;
uint32_t INA219DuoTime = 0;


uint32_t BME280Period    ;
uint32_t SCD30Period     ;
uint32_t MGS001Period    ;
uint32_t IPS7100Period   ;
uint32_t GPGGALRPeriod   ;
uint32_t INA219DuoPeriod ;


void setup()
{ 
  initializeSerialMints();
  initializeReboot(rebootPin);
  delay(10000);
  INA219DuoOnline =  initializeINA219DuoMints();
  powerMode       =  getPowerMode(rebootPin);

  INA219DuoPeriod  = getPeriod(powerMode, "INA219Duo");

  loraInitMints(keyIn);

  GPGGALROnline  = initializeGPGGALRMints();
  GPGGALRPeriod  = getPeriod(powerMode, "GPGGALR");
  SerialUSB.print("GPGGALR Period: ");
  SerialUSB.println(GPGGALRPeriod);


  BME280Online  = initializeBME280Mints();
  BME280Period  = getPeriod(powerMode, "BME280");
  SerialUSB.print("BME Period: ");
  SerialUSB.println(BME280Period);

  SCD30Online   =  initializeSCD30Mints(SCD30ReadTime);
  SCD30Period  = getPeriod(powerMode, "SCD30");
  SerialUSB.print("SCD Period: ");
  SerialUSB.println(SCD30Period);

  MGS001Online  =  initializeMGS001Mints();
  MGS001Period  = getPeriod(powerMode, "MGS001");
  SerialUSB.print("MGS Period: ");
  SerialUSB.println(MGS001Period);

  IPS7100Online =  initializeIPS7100Mints();
  IPS7100Period  = getPeriod(powerMode, "IPS7100");
  SerialUSB.print("IPS Period: ");
  SerialUSB.println(IPS7100Period);

  SerialUSB.print("Power Mode: ");
  SerialUSB.println(powerMode);

  resetIPS7100Mints(IPS7100ResetTime);
  resetLoRaMints(numOfTries,powerMode);
}

void loop()
{
      //  if(readNow(INA219DuoOnline,INA219DuoTime,INA219DuoPeriod))
     if(INA219DuoOnline){ 
        readINA219DuoMintsMax();
        INA219DuoTime  = millis();
        // delay(2500); 
       }


      // if(readNow(IPS7100Online,IPS7100Time,IPS7100Period))
      if(IPS7100Online){
        readIPS7100MintsMax();
        IPS7100Time  = millis();
      }


    // if(readNow(BME280Online,BME280Time,BME280Period))
    //   { 
      if(BME280Online){
        readBME280MintsMax();
        BME280Time  = millis();
      
       }
      

      // if(readNow(SCD30Online,SCD30Time,SCD30Period))
      // { 
        if(SCD30Online){
        readSCD30MintsMax();
        SCD30Time  = millis();
        
         }
      

      // if(readNow(IPS7100Online,IPS7100Time,IPS7100Period))
      // {
        if(IPS7100Online){
        readIPS7100MintsMax();
        IPS7100Time  = millis();
        }
        // delay(2500);
      // }


      // if(readNow(BME280Online,BME280Time,BME280Period))
      // { 
        if(BME280Online){
          readBME280MintsMax();
          BME280Time  = millis();
        }
        // delay(2500);
      // }
      
      if(readNow(MGS001Online,MGS001Time,MGS001Period))
      { 
        readMGS001MintsMax();
        MGS001Time  = millis();
        // delay(2500); 
      }

      if(readNow(GPGGALROnline,GPGGALRTime,GPGGALRPeriod))
      { 
        readGPGGALRMintsMax();
        GPGGALRTime  = millis();
        // delay(2500); 
      }


  // checkReboot(powerMode,rebootPin);

}


  // lora.setDeviceLowPower();    // bring the LoRaWAN module to sleep mode

