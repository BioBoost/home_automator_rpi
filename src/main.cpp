#include <bios_logger/logger.h>
#include "lib/home_automator/home_automator.h"
#include <bios_logger/writers/terminal_log_writer.h>
#include <bios_logger/writers/remote_rest_log_writer.h>
#include "lib/factories/mqtt_channel_factory.h"
#include "lib/factories/expansion_card_factory.h"
#include "lib/config/json_config_parser.h"

using namespace BiosHomeAutomator;
using namespace BiosLogger;
using namespace BiosHomeAutomator::Factories;
using namespace BiosHomeAutomator::Configuration;

const std::string REST_LOGGER_HOST		  { "10.0.0.100" };
const int REST_LOGGER_PORT              = 3000;
const std::string REST_LOGGER_AUTH_KEY  { "rwfdh4e2" };
const std::string VERSION               { "version 1.1.1" };

int main(void) {
  // DoLog.register_log_writer(new RemoteRestLogWriter(REST_LOGGER_AUTH_KEY, "/messages.json", REST_LOGGER_HOST, REST_LOGGER_PORT, logVERBOSE));
  DoLog.register_log_writer(new TerminalLogWriter(logVERBOSE));
  DoLog.info("Starting Home Automator ...");
  DoLog.info("Current version: " + VERSION);

  JsonConfigParser parser("config.json");
  MQTTConfig mqttConfig = parser.mqtt();

  MQTTChannel * mqttChannel = MQTTChannelFactory::create_channel(parser.mqtt());
  HomeAutomator * automator = new HomeAutomator(mqttChannel);

  // This is not yet as it should be. Here we need to know what types exist!
  for (IORelayCardConfig cardConfig : parser.io_relay_cards()) {
    automator->add_card(ExpansionCardFactory::create_card(cardConfig));
  }

  DoLog.info("All ready for action ...");

  while (true) {
    std::this_thread::sleep_for(std::chrono::minutes(1));
  }

  return 0;
}
