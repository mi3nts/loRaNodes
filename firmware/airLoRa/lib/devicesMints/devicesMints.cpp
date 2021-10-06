
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



