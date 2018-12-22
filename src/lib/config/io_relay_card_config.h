#pragma once

namespace BiosHomeAutomator {

  namespace Configuration {

    struct IORelayCardConfig {

      public:
        int id;
        int i2c_address;
        int input_change_isr;

    };

  };

};