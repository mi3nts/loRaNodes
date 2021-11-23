
#include "jobsMints.h"
#include "devicesMints.h"
#include "LoRaWan.h"


bool BME280Online;
BME280 bme280; // I2C

bool SCD30Online;
SCD30 scd;


bool IPS7100Online;
IpsSensor ips_sensor;

bool MGS001Online;

bool INS219DuoOnline;
Adafruit_INA219 ina219Battery(0x40);
Adafruit_INA219 ina219Solar(0x41);


uint16_t sensingPeriod = 2417;
uint16_t initPeriod = 1500;

// char lk[256];
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
  SCD30Online =  initializeSCD30Mints();

  delay(initPeriod);
  IPS7100Online =  initializeIPS7100Mints();
  
  delay(initPeriod);
  INS219DuoOnline =  initializeINA219DuoMints();

  // loraInitMints();
  
}

void loop()
{


    delay(sensingPeriod);
      SerialUSB.println("+===========================+");
    if(BME280Online)
      { 
           SerialUSB.println("READING BME");
           readBME280Mints();
           SerialUSB.println(" ");
           SerialUSB.println("BME Read");
    }

    delay(sensingPeriod);
    if(MGS001Online)
    SerialUSB.println("+===========================+");
    {SerialUSB.println("READING MGS");
      readMGS001Mints();
            SerialUSB.println(" ");
           SerialUSB.println("MGS Read");
    }
    // // //
    delay(sensingPeriod);
    SerialUSB.println("+===========================+");
    if(SCD30Online)
    { SerialUSB.println("READING ");
      readSCD30Mints();
            SerialUSB.println(" ");
        SerialUSB.println("SCD Read");
    }

    delay(sensingPeriod);
    SerialUSB.println("+===========================+");

    if(IPS7100Online)
    { SerialUSB.println("READING IPS");
      readIPS7100Mints();
      SerialUSB.println(" ");
      SerialUSB.println("IPS Read");
    }
    delay(sensingPeriod);
    SerialUSB.println("+===========================+");

    if(INS219DuoOnline)
    { SerialUSB.println("READING INS219Duo");
      readINA219DuoMints();
      SerialUSB.println(" ");
      SerialUSB.println("IPS Read");
    }


}