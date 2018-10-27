#include <unistd.h>   // For sleep
#include "lib/home_automator/home_automator.h"
#include <bios_logger/logger.h>
#include <bios_logger/writers/terminal_log_writer.h>
#include <bios_logger/writers/remote_rest_log_writer.h>

using namespace std;
using namespace BiosHomeAutomator;
using namespace BiosLogger;

const std::string MQTT_SERVER_ADDRESS 	{ "tcp://10.0.0.100:1883" };
const std::string MQTT_CLIENT_ID		    { "sdfasdt54654hg4fh5334543" };
const std::string REST_LOGGER_HOST		  { "10.0.0.100" };
const int REST_LOGGER_PORT              = 3000;
const std::string REST_LOGGER_AUTH_KEY  { "rwfdh4e2" };
const std::string VERSION               { "version 1.1.1" };

int main(void) {
  DoLog.register_log_writer(new RemoteRestLogWriter(REST_LOGGER_AUTH_KEY, "/messages.json", REST_LOGGER_HOST, REST_LOGGER_PORT, logVERBOSE));
  DoLog.register_log_writer(new TerminalLogWriter(logVERBOSE));
  DoLog.info("Starting Home Automator ...");
  DoLog.info("Current version: " + VERSION);

  MQTTChannel * mqttChannel = new MQTTChannel(MQTT_SERVER_ADDRESS, MQTT_CLIENT_ID);
  HomeAutomator * automator = new HomeAutomator(mqttChannel);
  automator->add_card(new IORelayCard(0x20, 0, 1));   // 0 = id, 1 = isr pin

  DoLog.info("All ready for action ...");

  while (true) {
    sleep(1);
  }

  return 0;
}
