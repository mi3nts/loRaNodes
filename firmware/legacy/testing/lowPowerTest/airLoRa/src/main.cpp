




#include  <ZeroPowerManager.h>
// #include "jobsMints.h"
// #include "devicesMints.h"

void setup()
{    
    zpmRTCInit();   
    
    /*
     * To get to datasheet power levels the I/O must be disabled
     */
    zpmPortDisableDigital();
    zpmPortDisableSPI();
    zpmPortDisableUSB();
}


void loop()
{    
    /*
     * Stay in each power state for about a second.
     */
    zpmCPUClk48M();
    delay(1000);
  
    zpmCPUClk8M();    
    delay(1000/6);
    
    zpmCPUClk32K();
    delay(1);
    
    /* 
     * There is no interrupt handler (callback = NULL). Execution will
     * resume from the sleep instruction.
     */ 
    unsigned int now = zpmRTCGetClock();
    zpmRTCInterruptAt(now + 1000, NULL);
    zpmSleep();
}















// #include "jobsMints.h"
// #include "devicesMints.h"
// #include "LoRaWan.h"


// bool BME280Online;
// BME280 bme280; // I2C

// bool SCD30Online;
// SCD30 scd;


// bool IPS7100Online;
// IpsSensor ips_sensor;

// bool MGS001Online;

// bool INA219DuoOnline;

// Adafruit_INA219 ina219Battery(0x40);
// Adafruit_INA219 ina219Solar(0x41);


// uint16_t sensingPeriod = 2417;
// uint16_t initPeriod = 1500;

// void setup()
// {

//   delay(initPeriod);
//   initializeSerialMints();

//   delay(initPeriod);
//   BME280Online = initializeBME280Mints();
  
//   delay(initPeriod);
//   MGS001Online =  initializeMGS001Mints();
   
//   delay(initPeriod);
//   SCD30Online =  initializeSCD30Mints();

//   delay(initPeriod);
//   IPS7100Online =  initializeIPS7100Mints();
  
//   delay(initPeriod);
//   INA219DuoOnline =  initializeINA219DuoMints();

//   loraInitMints();
  
// }

// void loop()
// {

//     // delay(sensingPeriod);
//     // if(INS219DuoOnline)
//     // { 
//     //   readINA219DuoMintsMax();
//     //   SerialUSB.println(" ");

//     // }

//     delay(sensingPeriod);
//     if(BME280Online)
//       { 
//         readBME280MintsMax();
//         SerialUSB.println(" ");
//     }

//     delay(sensingPeriod);
//     if(MGS001Online)
//     {
//       readMGS001MintsMax();
//       SerialUSB.println(" ");
//     }
  
//     delay(sensingPeriod);
//     if(SCD30Online)
//     {
//       readSCD30MintsMax();
//       SerialUSB.println(" ");
//     }

//     delay(sensingPeriod);

//     if(IPS7100Online)
//     { 
//       readIPS7100Mints();
//       SerialUSB.println(" ");
//     }
// }