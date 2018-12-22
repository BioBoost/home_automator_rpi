#include "lib/home_automator/home_automator.h"
#include <bios_logger/logger.h>
#include <bios_logger/writers/terminal_log_writer.h>
#include <bios_logger/writers/remote_rest_log_writer.h>
#include "lib/factories/mqtt_channel_factory.h"
#include "lib/factories/expansion_card_factory.h"

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

  MQTTConfig mqttConfig {
    "tcp://10.0.0.200:1883",
    "fdgt365354243543255343"
  };

  DoLog.info("MQTT Server: " + mqttConfig.server);
  DoLog.info("MQTT Client ID: " + mqttConfig.client_id);

  MQTTChannel * mqttChannel = MQTTChannelFactory::create_channel(mqttConfig);
  HomeAutomator * automator = new HomeAutomator(mqttChannel);

  IORelayCardConfig relayCardConfig {
    5,    // id
    0x20, // i2c address
    1     // isr pin
  };
  automator->add_card(ExpansionCardFactory::create_card(relayCardConfig));

  DoLog.info("All ready for action ...");

  while (true) {
    std::this_thread::sleep_for(std::chrono::minutes(1));
  }

  return 0;
}
