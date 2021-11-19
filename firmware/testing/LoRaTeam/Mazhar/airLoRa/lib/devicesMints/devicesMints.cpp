
#include "devicesMints.h"

void loraInitMints()
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
  lora.setKey(NULL, NULL, "312F851628AED2A6ABF7159999CF4F3C");
 
  SerialUSB.println("Setting LWOTAA Mode");
  lora.setDeciveMode(LWOTAA);
  lora.setDataRate(DR3, US915);
  lora.setJoinDutyCycle(false);

  // SerialUSB.println("Setting Power");
  lora.setPower(20);  //###
  lora.setPort(1);
  lora.setClassType(CLASS_A);

  SerialUSB.println("Starting Join");
  while(!lora.setOTAAJoin(JOIN, 10));


  SerialUSB.println("Setup Complete");


}




//  INA 219 
bool initializeINA219DuoMints()
{

  if (ina219Battery.begin()&ina219Solar.begin()) 
  {
        SerialUSB.println("INA219s Initiated");
        delay(1);
        return true;
  }
      else
      {
      SerialUSB.println("INA219s not found");
      delay(1);

      return false;
      }
}



void readINA219DuoMints(){

  float shuntVoltageBat  = ina219Battery.getShuntVoltage_mV();
  float busVoltageBat    = ina219Battery.getBusVoltage_V();
  float currentMaBat     = ina219Battery.getCurrent_mA();
  float powerMwBat       = ina219Battery.getPower_mW();
  
  float shuntVoltageSol  = ina219Solar.getShuntVoltage_mV();
  float busVoltageSol    = ina219Solar.getBusVoltage_V();
  float currentMaSol     = ina219Solar.getCurrent_mA();
  float powerMwSol       = ina219Solar.getPower_mW();

  String readings[8] = { String(shuntVoltageBat,2) , String( busVoltageBat,2), String(currentMaBat ,2) , String(powerMwBat,2) ,
   String(shuntVoltageSol,2) , String( busVoltageSol,2), String(currentMaSol ,2) , String(powerMwSol,2)};
  sensorPrintMints("INA219Duo",readings,8);
}

//  BME280

bool initializeBME280Mints(){
      if (bme280.init()) {
        SerialUSB.println("BME280 Initiated");
        delay(1);
        return true;
      }
      else
      {
      SerialUSB.println("BME280 not found");
      delay(1);

      return false;
      }

}


// void readBME280Mints(){
//   float values[3]  = {
//                       bme280.getTemperature(),
//                       bme280.getPressure()/100,
//                       bme280.getHumidity()
//                       };
  
//   unsigned long final = minMaxFloat2ULongMints(10*values[0]+40,0,1000) << 20 | 
//                         minMaxFloat2ULongMints(10*values[1]+40,0,1000) << 10 | 
//                         minMaxFloat2ULongMints(10*values[2],0,1000) ;
  
//   String readings[4] = {
//                          String(values[0],2) ,
//                          String(values[1],2) ,
//                          String(values[2],2) ,
//                          String(final,2)
//                          };
//   // byte sendOut[4] = { 
//   //                     minMaxFloatMints(2*values[0]+ 81,1,241),
//   //                     minMaxFloatMints((values[1]-96000)/24 +1,1,251),
//   //                     minMaxFloatMints(2*values[2]+1,1,201)
//   //                     };
  


//   sensorPrintMints("BME280",readings,4);
//   // loraSendMints(sendOut,4,5,21); 
// }

void readBME280Mints(){
  float values[3]  = {
                      bme280.getTemperature(),
                      bme280.getPressure(),
                      bme280.getHumidity()
                      };
  
  byte sendOut[3] = { 
                      minMaxFloatMints(2*values[0]+ 81,1,241),
                      minMaxFloatMints((values[1]-96000)/24 +1,1,251),
                      minMaxFloatMints(2*values[2]+1,1,201)
                      };
  
  String readings[6] = {
                         String(values[0],2) , String(sendOut[0]) ,
                         String(values[1],2) , String(sendOut[1]), 
                         String(values[2],2) , String(sendOut[2])
                         };

  sensorPrintMints("BME280",readings,6);
  // loraSendMints(sendOut,3,5,21); 
}

// // MGS001  ---------------------------------------

bool initializeMGS001Mints(){

  gas.begin(0x04);//the default I2C address of the slave is 0x04
  gas.powerOn();
  SerialUSB.println("MGS001 Initiated");
  SerialUSB.print("MGS001 Firmware Version = ");
  SerialUSB.println(gas.getVersion());
  delay(1);

return true;
}

void readMGS001Mints(){
  
  float values[8]  = {
                        gas.measure_C2H5OH(),
                        gas.measure_C3H8(),
                        gas.measure_C4H10(),
                        gas.measure_CH4(),
                        gas.measure_CO(),
                        gas.measure_H2(),
                        gas.measure_NH3(),
                        gas.measure_NO2()
                        };

  byte sendOut[8] = {
                     minMaxFloatMints(values[0]/4+1,1,251),
                     minMaxFloatMints(values[1]/4+1,1,251),
                     minMaxFloatMints((values[2]-5000)/60+1,1,251),
                     minMaxFloatMints(values[3]/40+1,1,251),
                     minMaxFloatMints(values[4]/4+1,1,251),
                     minMaxFloatMints(values[5]/40000,1,251),
                     minMaxFloatMints(values[6]*5000+1,1,251),
                     minMaxFloatMints(values[7]/12+1,1,251),
                    };
  
  String readings[16] = {
                         String(values[0],2), String(sendOut[0]),
                         String(values[1],2), String(sendOut[1]),
                         String(values[2],2), String(sendOut[2]),
                         String(values[3],2), String(sendOut[3]),
                         String(values[4],2), String(sendOut[4]),
                         String(values[5],2), String(sendOut[5]),
                         String(values[6],2), String(sendOut[6]),
                         String(values[7],2), String(sendOut[7]),
                         };

  sensorPrintMints("MGS001",readings,16);
  // loraSendMints(sendOut,8,5,31); 

}




// SCD30 ---------------------------------------
bool initializeSCD30Mints(){
  if (scd.begin()) {
    SerialUSB.println("SCD30 Initiated");
    delay(1);
    return true;
  }else{
    SerialUSB.println("SCD30 not found");
    delay(1);
    return false;
  }

  delay(2000);
}

void readSCD30Mints(){

  uint16_t co2         = scd.getCO2();
  uint16_t temperature = scd.getTemperature();
  uint16_t humidity    = scd.getHumidity();

  String readings[3] = { String(co2), String(temperature) , String(humidity) };
  sensorPrintMints("SCD30",readings,3);

}


// // IPS7100 ---------------------------------------
bool initializeIPS7100Mints(){
    // ips_sensor.begin();
    SerialUSB.println("IPS7100 Initiated");
   return true;
}

void readIPS7100Mints(){

delay(1000);
  // Enable debugging
  //  SerialUSB.println("+--------------------------+");
  //  SerialUSB.println("Setting Debug to true");
  //  ips_sensor.setDebug(true);
  //  delay(1100);

// //  Print sensor status
  //  SerialUSB.println("+--------------------------+");
  // SerialUSB.println("Reading Status");
  // SerialUSB.print("Status: ");
  // int status = ips_sensor.getStatus();
  // SerialUSB.println(status);

  // delay(1100);
  //  SerialUSB.println("+--------------------------+");
  // SerialUSB.println("Reading VREF");
  // int vref = ips_sensor.getVref();
  // SerialUSB.print("VREF: ");
  // SerialUSB.println(vref);
  // delay(1100);

   SerialUSB.println("+--------------------------+");
  SerialUSB.println("Running Update PM Command");
  ips_sensor.updatePM();


  // Print PM1.0 via USB serial
  SerialUSB.print("PM 0.1: ");
  SerialUSB.println(ips_sensor.getPM01());
  // Print PM1.0 via USB serial
  SerialUSB.print("PM 0.3: ");
  SerialUSB.println(ips_sensor.getPM03());
  // Print PM1.0 via USB serial
  SerialUSB.print("PM 0.5: ");
  SerialUSB.println(ips_sensor.getPM05());
  // Print PM1.0 via USB serial
  SerialUSB.print("PM 1.0: ");
  SerialUSB.println(ips_sensor.getPM10());
  // Print PM2.5 via USB serial
  SerialUSB.print("PM 2.5: ");
  SerialUSB.println(ips_sensor.getPM25());
  // Print PM10 via USB serial
  SerialUSB.print("PM 10: ");
  SerialUSB.println(ips_sensor.getPM100());
 
  delay(1100);
   SerialUSB.println("+--------------------------+");
  SerialUSB.println("Running Update PC Command");
  ips_sensor.updatePC();

  // Print PM1.0 via USB serial
  SerialUSB.print("PC 0.1: ");
  SerialUSB.println(ips_sensor.getPC01());
  // Print PM1.0 via USB serial
  SerialUSB.print("PC 0.3: ");
  SerialUSB.println(ips_sensor.getPC03());
  // Print PM1.0 via USB serial
  SerialUSB.print("PC 0.5: ");
  SerialUSB.println(ips_sensor.getPC05());
  // Print PM1.0 via USB serial
  SerialUSB.print("PC 1.0: ");
  SerialUSB.println(ips_sensor.getPC10());
  // Print PM2.5 via USB serial
  SerialUSB.print("PC 2.5: ");
  SerialUSB.println(ips_sensor.getPC25());
  // Print PM10 via USB serial
  SerialUSB.print("PC 10: ");
  SerialUSB.println(ips_sensor.getPC100());
 


}


