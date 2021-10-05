#include "Seeed_BME280.h"
// #include <Wire.h>

BME280 bme280;

void setup()
{

  SerialUSB.begin(9600);
  SerialUSB.println("Opening Device Port");
  // if(!bme280.init()){
  //   SerialUSB.println("Device error!");
  // }
}

void loop()
{
  // float pressure;
  SerialUSB.print("Temp: ");
  //get and print temperatures
  // SerialUSB.print("Temp: ");
  // SerialUSB.print(bme280.getTemperature());
  // SerialUSB.println("C");//The unit for  Celsius because original arduino don't support speical symbols
  
  // //get and print atmospheric pressure data
  // SerialUSB.print("Pressure: ");
  // SerialUSB.print(pressure = bme280.getPressure());
  // SerialUSB.println("Pa");

  // //get and print altitude data
  // SerialUSB.print("Altitude: ");
  // SerialUSB.print(bme280.calcAltitude(pressure));
  // SerialUSB.println("m");

  // //get and print humidity data
  // SerialUSB.print("Humidity: ");
  // SerialUSB.print(bme280.getHumidity());
  // SerialUSB.println("%");

  delay(1000);
}