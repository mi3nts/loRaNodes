
#include "devicesMints.h"

// BME280  ---------------------------------------
//
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

void readBME280Mints(){

  float temperature    = bme280.getTemperature();
  float pressure       = bme280.getPressure();
  float humidity       = bme280.getHumidity();
  float altitude       = bme280.calcAltitude(pressure);

  String readings[4] = { String(temperature,2) , String(pressure,2), String(humidity,2) , String(altitude,2) };
  sensorPrintMints("BME280",readings,4);
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

  float nh3     = gas.measure_NH3();
  float co      = gas.measure_CO();
  float no2     = gas.measure_NO2();
  float c3h8    = gas.measure_C3H8();
  float c4h10   = gas.measure_C4H10();
  float ch4     = gas.measure_CH4();
  float h2      = gas.measure_H2();
  float c2h5oh  = gas.measure_C2H5OH();


  String readings[8] = { String(nh3,2) , String(co,2), String(no2,2) , String(c3h8,2), String(c4h10,2) , String(ch4,2), String(h2,2) , String(c2h5oh,2) };
  sensorPrintMints("MGS001",readings,8);
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
   SerialUSB.println("+--------------------------+");
   SerialUSB.println("Setting Debug to true");
   ips_sensor.setDebug(true);
   delay(1100);

// //  Print sensor status
   SerialUSB.println("+--------------------------+");
  SerialUSB.println("Reading Status");
  SerialUSB.print("Status: ");
  int status = ips_sensor.getStatus();
  SerialUSB.println(status);

  delay(1100);
   SerialUSB.println("+--------------------------+");
  SerialUSB.println("Reading VREF");
  int vref = ips_sensor.getVref();
  SerialUSB.print("VREF: ");
  SerialUSB.println(vref);
  delay(1100);

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


