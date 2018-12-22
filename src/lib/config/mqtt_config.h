#pragma once

#include <string>

namespace BiosHomeAutomator {

  namespace Configuration {

    struct MQTTConfig {

      public:
        std::string server;
        std::string client_id;

    };

  };

};