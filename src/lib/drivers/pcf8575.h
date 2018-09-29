#pragma once

#include "../hal/i2c/i2c_endpoint.h"

namespace IOExpansion {

  class PCF8575 {
    public:
      const static unsigned int ALL_INPUTS = 0xFFFF;

    private:
      HAL::I2cEndpoint i2cEndpoint;
      unsigned int directionMask;    // Outputs are 0, Inputs are 1

    public:
      PCF8575(unsigned int address, std::string filename);

    public:
      void set_port_direction(unsigned int mask);
      unsigned int read_port(void);
      void write_port(unsigned int data);

    private:
      void set_all_as_inputs(void);

  };

};
