

// #include <Wire.h>
// #include <Arduino.h>

// #include <IpsI2C.h>

// IpsSensor ips_sensor;

// int success_count;
// int fail_count;

// void setup()
// {
//   // Wait on IPS bootloader
//   delay(3500);

//   // Initiate I2C connection SDA 21, SCL 22 by default
//   // Set different pins by using:
//   // ips_sensor.begin(SDA_PIN, SCL_PIN)
//   ips_sensor.begin();
//   //ips_sensor.begin();

//   // Initiate USB serial at 115200 baud
//   SerialUSB.begin(115200);
//   SerialUSB.println("\nI2C Test");
// }

// void loop()
// {
// SerialUSB.println("Test");
//   // Get new IPS sensor readings
//   // Not meant to run more than once per second
//   ips_sensor.update();

//   //Enable debugging
//   // ips_sensor.setDebug(true);

//   // Print PC0.1 via USB serial
//     SerialUSB.println(ips_sensor.getPC01());

//   // Print PM1.0 via USB serial
//   // SerialUSB.print("PM1.0: ");
//   // SerialUSB.print(ips_sensor.getPM10());
//   // SerialUSB.print("\n");

//   // // Print PM2.5 via USB serial
//   // SerialUSB.print("PM2.5: ");
//   // SerialUSB.print(ips_sensor.getPM25());
//   // SerialUSB.print("\n");

//   // // Print PM10 via USB serial
//   // SerialUSB.print("PM10: ");
//   // SerialUSB.print(ips_sensor.getPM100());
//   // SerialUSB.print("\n");

//   // Print sensor status
//   // int status = ips_sensor.getStatus();
//   // SerialUSB.println(status);

//   // Print Vref value
//   // int vref = ips_sensor.getVref();
//   // SerialUSB.println(vref);

//   // Testing I2C accuracy
//   // if (vref == 1800) {
//   //   success_count++;
//   // } else {
//   //   fail_count++;
//   // }
//   // if (status == 1) {
//   //   success_count++;
//   // } else {
//   //   fail_count++;
//   // }
//   // SerialUSB.print("Success_count: ");
//   // SerialUSB.print(success_count);
//   // SerialUSB.print(" Fail_count: ");
//   // SerialUSB.print(fail_count);
//   // SerialUSB.print("\n");

//   delay(1000);
// }










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
  SCD30Online =  initializeSCD30Mints();

  delay(initPeriod);
  IPS7100Online =  initializeIPS7100Mints();
  
  // // Lora Begin
  // delay(initPeriod);
  // lora.init();
  // lora.setDeviceReset();
  // lora.setDeviceDefault();

  // SerialUSB.println("Get Module Version");
  // memset(buffer, 0, 256);
  // lora.getVersion(buffer, 256, 1);
  // SerialUSB.println("Version");
  // SerialUSB.print(buffer);

  // SerialUSB.println("Get Lora Credentials");
  // memset(buffer, 0, 256);
  // lora.getId(buffer, 256, 1);
  // SerialUSB.println("LoRa ID");
  // SerialUSB.print(buffer);


  // // SerialUSB.println("Setting Keys");
  // lora.setKey(NULL, NULL, "312F851628AED2A6ABF7159999CF4F3C");
  // // SerialUSB.println("Setting LWOTAA Mode");
  // lora.setDeciveMode(LWOTAA);
  // lora.setDataRate(DR3, US915);
  
  // // Lora End



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

  // lora.setJoinDutyCycle(false);

  // // SerialUSB.println("Setting Power");
  // lora.setPower(14);  //###
  // lora.setPort(1);
  // lora.setClassType(CLASS_A);

  // SerialUSB.println("Starting Join");
  // // while(!lora.setOTAAJoin(JOIN, 10));


  SerialUSB.println("Setup Complete");

}

void loop()
{


    delay(sensingPeriod);
      SerialUSB.println("+===========================+");
    if(BME280Online)
      { SerialUSB.println("READING BME");
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


  delay(5000);
}