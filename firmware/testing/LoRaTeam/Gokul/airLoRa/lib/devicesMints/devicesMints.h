#ifndef DEVICES_MINTS_H
#define DEVICES_MINTS_H

#include "jobsMints.h"

#include "Adafruit_INA219.h"
#include "Seeed_BME280.h"
#include "SparkFun_SCD30_Arduino_Library.h"
#include "MutichannelGasSensor.h"
#include "LoRaWan.h"
#include <IpsI2C.h>


void loraInitMints();




extern Adafruit_INA219 ina219Battery;
extern Adafruit_INA219 ina219Solar;
bool initializeINA219DuoMints();
void readINA219DuoMints();

extern BME280 bme280;
bool initializeBME280Mints();
void readBME280Mints();
//
bool initializeMGS001Mints();
void readMGS001Mints();
//
extern SCD30 scd;
bool initializeSCD30Mints();
void readSCD30Mints();

extern IpsSensor ips_sensor;
bool initializeIPS7100Mints();
void readIPS7100Mints();

#endif