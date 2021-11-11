#ifndef LORA_MINTS_H
#define LORA_MINTS_H

#include <Arduino.h>
#include "LoRaWan.h"


void loraInitMints(char* keyIn);
void sensorPrintULongs(String sensor,unsigned long readings[],uint8_t numOfvals);
void sensorPrintFloats(String sensor,float readings[],uint8_t numOfvals);
byte sensorPrintBytes(String sensor,byte readings[],uint8_t numOfvals);
void loRaSendMints(byte sendOut[],uint8_t numOfBytes,uint8_t timeOut,uint8_t portNum);
byte minMaxFloatMints(float inVal, float min, float max);
unsigned long minMaxFloat2ULongMints(float inVal, float min, float max);

void initializeReboot(uint8_t rebootPin);
void rebootBoard(uint8_t rebootPin);
void checkReboot(uint8_t powerModeIn,uint8_t rebootPinIn);
bool readNow(bool sensorOnline,uint32_t startIn,uint32_t periodIn);
#endif