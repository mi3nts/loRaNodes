#ifndef DEVICES_MINTS_H
#define DEVICES_MINTS_H
//
// #include <Arduino.h>
#include "jobsMints.h"


#include "Seeed_BME280.h"
#include "SparkFun_SCD30_Arduino_Library.h"
#include "MutichannelGasSensor.h"
#include <IpsI2C.h>

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