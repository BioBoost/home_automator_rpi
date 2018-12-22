#pragma once

#include <fstream>
#include <json.hpp>
#include "mqtt_config.h"

namespace BiosHomeAutomator {

  namespace Configuration {

    class JsonConfigParser {

      public:
        JsonConfigParser(std::string file) {
          std::ifstream inputFile(file);
          inputFile >> json;
        }

        MQTTConfig mqtt(void) {
          return MQTTConfig {
            json["mqtt"]["server"],
            json["mqtt"]["client_id"]
          };
        }

        std::vector<IORelayCardConfig> io_relay_cards(void) {
          std::vector<IORelayCardConfig> cards;

          for (auto& card : json["cards"]) {
            if (card["type"] == "iorelay") {
              cards.push_back(IORelayCardConfig{
                card["id"], card["i2c"]["address"], card["pins"][0]["input_changed_isr"]
              });
            }
          }

          return cards;
        }

      private:
        nlohmann::json json;

    };

  };

};