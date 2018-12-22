#pragma once

#include "../mqtt/mqtt_channel.h"
#include "../config/mqtt_config.h"

namespace BiosHomeAutomator {

  namespace Factories {

    class MQTTChannelFactory {

      public:
        static MQTTChannel * create_channel(Configuration::MQTTConfig config) {
          return new MQTTChannel(config.server, config.client_id);
        }

    };

  };

};