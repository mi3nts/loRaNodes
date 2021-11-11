#ifndef JOBS_MINTS_H
#define JOBS_MINTS_H

#include <Arduino.h>
#include "LoRaWan.h"


void initializeSerialMints();
void sensorPrintMints(String sensor,String readings[],uint8_t numOfvals);
void loraSendMints(byte sendOut[],uint8_t numOfBytes,uint8_t timeOut,uint8_t portNum);
byte minMaxFloatMints(float inVal, float min, float max);
unsigned long minMaxFloat2ULongMints(float inVal, float min, float max);
#endif