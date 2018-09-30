#include "hardware_interrupt.h"
#include <wiringPi.h>

std::vector<int> HAL::HardwareInterrupt::pins;
std::vector<std::function<void(void)>> HAL::HardwareInterrupt::callbacks;

namespace HAL {

  bool HardwareInterrupt::setup_wiring_pi(int pin, Edge edge) {
    // Could there be a problem if this is called twice ?
    if (wiringPiSetup () < 0) {
      // Should throw exception
      BiosLogger::DoLog.error("Unable to setup wiringPi");
      return false;
    }

    // Register our internal static handler which distributes the events
    // to registered callbacks
    if (wiringPiISR (pin, (int)edge, wiring_pi_handler) < 0) {
      BiosLogger::DoLog.error("Unable to setup ISR");
      return false;
    }

    return true;
  }

  void HardwareInterrupt::wiring_pi_handler(int pin) {
    BiosLogger::DoLog.info("Inside static hardware interrupt handler, pin = " + std::to_string(pin));
    for (unsigned int i = 0; i < pins.size(); i++) {
      // By not breaking after match we allow multiple callbacks
      if (pins[i] == pin) {
        callbacks[i]();
      }
    }
  }

}
