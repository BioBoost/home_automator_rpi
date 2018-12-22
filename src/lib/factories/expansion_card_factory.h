#pragma once

#include "../cards/io_relay_card.h"
#include "../config/io_relay_card_config.h"

namespace BiosHomeAutomator {

  namespace Factories {

    class ExpansionCardFactory {

      public:
        static IORelayCard * create_card(Configuration::IORelayCardConfig config) {
          return new IORelayCard(config.i2c_address, config.id, config.input_change_isr);
        }

    };

  };

};