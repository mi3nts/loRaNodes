// Code adopted and modified from https://github.com/PieraSystems/7100-I2C-example


#pragma once

#include<vector>

union bytesToPM
{
  float f;
  unsigned char byte[4];
};

class IpsSensor
{
public:
    unsigned long pc_values[7] = {0, 0, 0, 0, 0, 0, 0};
    float pm_values[7] = {0, 0, 0, 0, 0, 0, 0};
    void begin(int sda = 21, int scl = 22);
    void update();
    void updatePC();
    void updatePM();
    unsigned long *getPC();
    unsigned long getPC01();
    unsigned long getPC03();
    unsigned long getPC05();
    unsigned long getPC10();
    unsigned long getPC25();
    unsigned long getPC50();
    unsigned long getPC100();
    float *getPM();
    float getPM01();
    float getPM03();
    float getPM05();
    float getPM10();
    float getPM25();
    float getPM50();
    float getPM100();
    int getVref();
    int getStatus();
    std::vector<uint8_t> read_i2c(unsigned char, int, bool checksum = false);
    uint16_t get_checksum(uint8_t *byte, int);
    void setDebug(bool);
};