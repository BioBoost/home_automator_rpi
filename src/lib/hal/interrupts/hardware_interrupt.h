#pragma once

#include <bios_logger/logger.h>
#include <functional>

namespace HAL {
  class HardwareInterrupt {
    public:
      enum Edge { FALLING=1, RISING=2, BOTH=3 };

    public:
      template<typename C>
      HardwareInterrupt(int pin, Edge edge, C *object, void(C::*method)(void)) {
        if (setup_wiring_pi(pin, edge)) {
          pins.push_back(pin);
          callbacks.push_back(std::bind(method, object));
        }
      }
    
    private:
      bool setup_wiring_pi(int pin, Edge edge);

    public:
      // General static handler for wiring pi that 
      static void wiring_pi_handler(int pin);

    private:
      static std::vector<std::function<void(void)>> callbacks;
      static std::vector<int> pins;
  };

}