
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


void readINA219DuoMintsMax(){
  uint8_t sizeIn = 8;
  uint8_t portIn = 21;
  String sensorName = "INA219Duo" ;
  float values[sizeIn]  = {
                      ina219Battery.getShuntVoltage_mV(),
                      ina219Battery.getBusVoltage_V(),
                      ina219Battery.getCurrent_mA(),
                      ina219Battery.getPower_mW(),
                      ina219Solar.getShuntVoltage_mV(),
                      ina219Solar.getBusVoltage_V(),
                      ina219Solar.getCurrent_mA(),
                      ina219Solar.getPower_mW()
                      };

  uint8_t sizeInBytes =sizeof(values);                    
  byte sendOut[sizeInBytes];
  memcpy(sendOut,&values,sizeof(values));
  sensorPrintFloats(sensorName,values,sizeIn);
  sensorPrintBytes(sensorName,sendOut,sizeInBytes);
  // loraSendMints(sendOut,sizeInBytes,5,portIn); 
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

void readBME280MintsMax()
{
  uint8_t sizeIn = 3;
  uint8_t portIn = 21;
  String sensorName = "BME280" ;
  float values[sizeIn]  = {
                      bme280.getTemperature(),
                      float(bme280.getPressure())/100,
                      bme280.getHumidity()
                      };
  uint8_t sizeInBytes =sizeof(values);                    
  byte sendOut[sizeInBytes];
  memcpy(sendOut,&values,sizeof(values));
  sensorPrintFloats(sensorName,values,sizeIn);
  sensorPrintBytes(sensorName,sendOut,sizeInBytes);
  // loraSendMints(sendOut,sizeInBytes,5,portIn); 
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
  // loraSendMints(sendOut,sizeInBytes,5,portIn); 
// }


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

void readMGS001MintsMax(){
  uint8_t sizeIn = 8;
  uint8_t portIn = 31;
  String sensorName = "MGS001" ;
  float values[sizeIn]  = {
                        gas.measure_C2H5OH(),
                        gas.measure_C3H8(),
                        gas.measure_C4H10(),
                        gas.measure_CH4(),
                        gas.measure_CO(),
                        gas.measure_H2(),
                        gas.measure_NH3(),
                        gas.measure_NO2()
                        };

  uint8_t sizeInBytes = sizeof(values);                    
  byte sendOut[sizeInBytes];
  memcpy(sendOut,&values,sizeof(values));
  sensorPrintFloats(sensorName,values,sizeIn);
  sensorPrintBytes(sensorName,sendOut,sizeInBytes);
    // loraSendMints(sendOut,sizeInBytes,5,portIn); 
}



// void readMGS001Mints(){
  
//   float values[8]  = {
//                         gas.measure_C2H5OH(),
//                         gas.measure_C3H8(),
//                         gas.measure_C4H10(),
//                         gas.measure_CH4(),
//                         gas.measure_CO(),
//                         gas.measure_H2(),
//                         gas.measure_NH3(),
//                         gas.measure_NO2()
//                         };

//   byte sendOut[8] = {
//                      minMaxFloatMints(values[0]/4+1,1,251),
//                      minMaxFloatMints(values[1]/4+1,1,251),
//                      minMaxFloatMints((values[2]-5000)/60+1,1,251),
//                      minMaxFloatMints(values[3]/40+1,1,251),
//                      minMaxFloatMints(values[4]/4+1,1,251),
//                      minMaxFloatMints(values[5]/40000,1,251),
//                      minMaxFloatMints(values[6]*5000+1,1,251),
//                      minMaxFloatMints(values[7]/12+1,1,251),
//                     };
  
//   String readings[16] = {
//                          String(values[0],2), String(sendOut[0]),
//                          String(values[1],2), String(sendOut[1]),
//                          String(values[2],2), String(sendOut[2]),
//                          String(values[3],2), String(sendOut[3]),
//                          String(values[4],2), String(sendOut[4]),
//                          String(values[5],2), String(sendOut[5]),
//                          String(values[6],2), String(sendOut[6]),
//                          String(values[7],2), String(sendOut[7]),
//                          };

//   sensorPrintMints("MGS001",readings,16);
//   loraSendMints(sendOut,8,5,31); 

// }




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

void readSCD30MintsMax(){
  uint8_t sizeIn = 3;
  uint8_t portIn = 33;
  String sensorName = "SCD30" ;
  float values[sizeIn]  = {
                      scd.getCO2(),
                      scd.getTemperature(),
                      scd.getHumidity()
                      };

  uint8_t sizeInBytes = sizeof(values);                    
  byte sendOut[sizeInBytes];
  memcpy(sendOut,&values,sizeof(values));
  sensorPrintFloats(sensorName,values,sizeIn);
  sensorPrintBytes(sensorName,sendOut,sizeInBytes);
  // loraSendMints(sendOut,sizeInBytes,5,portIn); 
}


// // IPS7100 ---------------------------------------
bool initializeIPS7100Mints(){
    // ips_sensor.begin();
    SerialUSB.println("IPS7100 Initiated");
   return true;
}

void readIPS7100Mints(){
  ips_sensor.update();
  // ips_sensor.updatePC();
  // ips_sensor.updatePM();
  uint8_t sizeIn = 6;
  uint8_t portIn = 13;
  String sensorName = "IPS7100" ;

  unsigned long valuesPC[sizeIn]  = {
                      ips_sensor.getPC01(),
                      ips_sensor.getPC03(),
                      ips_sensor.getPC05(),
                      ips_sensor.getPC10(),
                      ips_sensor.getPC25(),
                      ips_sensor.getPC100()
  };

  float valuesPM[sizeIn]  = {
                      ips_sensor.getPM01(),
                      ips_sensor.getPM03(),
                      ips_sensor.getPM05(),
                      ips_sensor.getPM10(),
                      ips_sensor.getPM25(),
                      ips_sensor.getPM100()
                      };


  uint8_t sizeInBytesPC = sizeof(valuesPC);   
  uint8_t sizeInBytesPM = sizeof(valuesPM);   
  uint8_t sizeInBytes = sizeof(valuesPC) + sizeof(valuesPM);  

  byte sendOutPC[sizeInBytesPC];
  byte sendOutPM[sizeInBytesPM];
  byte sendOut[sizeInBytes];

  memcpy(sendOutPC,&valuesPC,sizeof(valuesPC));
  memcpy(sendOutPM,&valuesPM,sizeof(valuesPM));



  memcpy(sendOut, &sendOutPC, sizeof(valuesPC));
  memcpy(sendOut + sizeInBytesPC, &sendOutPM, sizeof(valuesPC));

  sensorPrintULongs(sensorName,valuesPC,sizeIn);
        SerialUSB.println(" ");
  sensorPrintFloats(sensorName,valuesPM,sizeIn);
        SerialUSB.println(" ");
  sensorPrintBytes(sensorName,sendOutPC,sizeInBytesPC);
          SerialUSB.println(" ");
    sensorPrintBytes(sensorName,sendOutPM,sizeInBytesPM);
            SerialUSB.println(" ");                    
      sensorPrintBytes(sensorName,sendOut,sizeInBytes);
  // loraSendMints(sendOut,sizeInBytes,5,portIn);
}


