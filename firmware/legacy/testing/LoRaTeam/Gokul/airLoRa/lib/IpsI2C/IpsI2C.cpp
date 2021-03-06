// Code adopted and modified from https://github.com/PieraSystems/7100-I2C-example

#include "Arduino.h"
#include "Wire.h"

#include "IpsI2C.h"

// For CRC16 checksum
#define POLY 0x8408

bool ips_debug = false;

void IpsSensor::begin(int sda, int scl)
{
  Wire.begin(sda, scl);
  //Wire.setClock(100000);
}

void IpsSensor::updatePC()
{
  // Read PC data
  std::vector<uint8_t> pc_raw_values = this->read_i2c(0x11, 30, true);

  // Assemble PC values (unsigned long) from 4 bytes via bitwise
  this->pc_values[0] = pc_raw_values[3] | (pc_raw_values[2] << 8) | (pc_raw_values[1] << 16) | (pc_raw_values[0] << 24);
  this->pc_values[1] = pc_raw_values[7] | (pc_raw_values[6] << 8) | (pc_raw_values[5] << 16) | (pc_raw_values[4] << 24);
  this->pc_values[2] = pc_raw_values[11] | (pc_raw_values[10] << 8) | (pc_raw_values[9] << 16) | (pc_raw_values[8] << 24);
  this->pc_values[3] = pc_raw_values[15] | (pc_raw_values[14] << 8) | (pc_raw_values[13] << 16) | (pc_raw_values[12] << 24);
  this->pc_values[4] = pc_raw_values[19] | (pc_raw_values[18] << 8) | (pc_raw_values[17] << 16) | (pc_raw_values[16] << 24);
  this->pc_values[5] = pc_raw_values[23] | (pc_raw_values[22] << 8) | (pc_raw_values[21] << 16) | (pc_raw_values[20] << 24);
  this->pc_values[6] = pc_raw_values[27] | (pc_raw_values[26] << 8) | (pc_raw_values[25] << 16) | (pc_raw_values[24] << 24);

  // Read PM data
 
}

void IpsSensor::updatePM()
{
  std::vector<uint8_t> pm_raw_values = this->read_i2c(0x12, 32, true);

  // Assemble PM values (float) from 4 bytes via union
  for (size_t i = 0; i < 7; ++i)
  {
    bytesToPM b;
    for (size_t j = 0; j < 4; ++j)
    {
      b.byte[j] = pm_raw_values[j + (i * 4)];
    }
    this->pm_values[i] = b.f;
  } 
}


void IpsSensor::update()
{
  // Read PC data
  std::vector<uint8_t> pc_raw_values = this->read_i2c(0x11, 30, true);

  // Assemble PC values (unsigned long) from 4 bytes via bitwise
  this->pc_values[0] = pc_raw_values[3] | (pc_raw_values[2] << 8) | (pc_raw_values[1] << 16) | (pc_raw_values[0] << 24);
  this->pc_values[1] = pc_raw_values[7] | (pc_raw_values[6] << 8) | (pc_raw_values[5] << 16) | (pc_raw_values[4] << 24);
  this->pc_values[2] = pc_raw_values[11] | (pc_raw_values[10] << 8) | (pc_raw_values[9] << 16) | (pc_raw_values[8] << 24);
  this->pc_values[3] = pc_raw_values[15] | (pc_raw_values[14] << 8) | (pc_raw_values[13] << 16) | (pc_raw_values[12] << 24);
  this->pc_values[4] = pc_raw_values[19] | (pc_raw_values[18] << 8) | (pc_raw_values[17] << 16) | (pc_raw_values[16] << 24);
  this->pc_values[5] = pc_raw_values[23] | (pc_raw_values[22] << 8) | (pc_raw_values[21] << 16) | (pc_raw_values[20] << 24);
  this->pc_values[6] = pc_raw_values[27] | (pc_raw_values[26] << 8) | (pc_raw_values[25] << 16) | (pc_raw_values[24] << 24);

  // Read PM data
  // delay(100);
  std::vector<uint8_t> pm_raw_values = this->read_i2c(0x12, 32, true);

  // Assemble PM values (float) from 4 bytes via union
  for (size_t i = 0; i < 7; ++i)
  {
    bytesToPM b;
    for (size_t j = 0; j < 4; ++j)
    {
      b.byte[j] = pm_raw_values[j + (i * 4)];
    }
    this->pm_values[i] = b.f;
  }
}

// Get CRC16 checksum
uint16_t IpsSensor::get_checksum(uint8_t *byte, int len)
{
  int i, j;
  uint16_t data = 0;
  uint16_t crc = 0xffff;
  for (j = 0; j < len; j++)
  {
    data = (uint16_t)0xff & byte[j];
    for (i = 0; i < 8; i++, data >>= 1)
    {
      if ((crc & 0x0001) ^ (data & 0x0001))
        crc = (crc >> 1) ^ POLY;
      else
        crc >>= 1;
    }
  }
  crc = ~crc;
  data = crc;
  crc = (crc << 8) | (data >> 8 & 0xff);
  return crc;
}

std::vector<uint8_t> IpsSensor::read_i2c(unsigned char command, int reply_size, bool checksum)
{
  bool checksum_pass = false;
  std::vector<uint8_t> received_bytes;
  while (!checksum_pass)
  {
    received_bytes.clear();
    Wire.beginTransmission(0x4B);
    Wire.write(command);
    Wire.endTransmission();
    Wire.requestFrom(0x4B, reply_size);
    for (int n = 1; n <= reply_size; n++)
    {
      received_bytes.push_back(Wire.read());
    }

    // Debug raw bytes
    if (ips_debug)
    {
      SerialUSB.print("[ ");
      for (auto &single_byte : received_bytes)
      {
        SerialUSB.print(single_byte);
        SerialUSB.print(" ");
      }
      SerialUSB.print("]\n");
    }

    if (!checksum)
    {
      break;
    }
    uint16_t message_checksum = this->get_checksum(received_bytes.data(), reply_size - 2);
    uint16_t received_checksum = (received_bytes[received_bytes.size() - 2] * 256) + received_bytes[received_bytes.size() - 1];
    if (ips_debug)
    {
      SerialUSB.print("Expected checksum: ");
      SerialUSB.print(message_checksum);
      SerialUSB.print(" Received checksum: ");
      SerialUSB.print(received_checksum);
      SerialUSB.print("\n");
    }
    if (message_checksum == received_checksum)
    {
      checksum_pass = true;
      SerialUSB.println("Checksum Success.");
    }
    else
    {
      // Checksum failed;
      if (ips_debug)
      {
        SerialUSB.println("Checksum Failed.");
        checksum_pass = true;
      }
      delay(100);
    }
  }
  return received_bytes;
}

unsigned long *IpsSensor::getPC()
{
  return this->pc_values;
};

unsigned long IpsSensor::getPC01()
{
  return this->pc_values[0];
};
unsigned long IpsSensor::getPC03()
{
  return this->pc_values[1];
};
unsigned long IpsSensor::getPC05()
{
  return this->pc_values[2];
};
unsigned long IpsSensor::getPC10()
{
  return this->pc_values[3];
};
unsigned long IpsSensor::getPC25()
{
  return this->pc_values[4];
};
unsigned long IpsSensor::getPC50()
{
  return this->pc_values[5];
};
unsigned long IpsSensor::getPC100()
{
  return this->pc_values[6];
};

float *IpsSensor::getPM()
{
  return this->pm_values;
};

float IpsSensor::getPM01()
{
  return this->pm_values[0];
}
float IpsSensor::getPM03()
{
  return this->pm_values[1];
}
float IpsSensor::getPM05()
{
  return this->pm_values[2];
}
float IpsSensor::getPM10()
{
  return this->pm_values[3];
}
float IpsSensor::getPM25()
{
  return this->pm_values[4];
}
float IpsSensor::getPM50()
{
  return this->pm_values[5];
}
float IpsSensor::getPM100()
{
  return this->pm_values[6];
}

int IpsSensor::getVref()
{
  // Read Vref
  std::vector<uint8_t> message = this->read_i2c(0x69, 4, true);
  unsigned short int vref;
  vref = message[1] | (message[0] << 8);
  return vref;
}

int IpsSensor::getStatus()
{
  // Read Status
  std::vector<uint8_t> message = this->read_i2c(0x6A, 3, true);
  unsigned short int status;
  status = message[0];
  return status;
}

void IpsSensor::setDebug(bool debug_setting)
{
  ips_debug = debug_setting;
}