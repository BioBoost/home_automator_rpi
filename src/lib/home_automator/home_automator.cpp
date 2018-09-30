#include "home_automator.h"

#include <vector>
#include <bios_logger/logger.h>
#include "../factories/mqtt_message_factory.h"
#include "../factories/event_factory.h"

extern void relay_card_interrupt_handler(void);

namespace BiosHomeAutomator {

  HomeAutomator::HomeAutomator(MQTTChannel * mqttChannel) {
    this->mqttChannel = mqttChannel;
    this->mqttChannel->subscribe("home/cards/+/relays/+/set", this);
  }

  HomeAutomator::~HomeAutomator(void) {
    for (unsigned int i = 0; i < relayCards.size(); i++) {
      delete relayCards[i];
    }
    relayCards.clear();
  }

  void HomeAutomator::add_card(IORelayCard * relayCard) {
    for (unsigned int i = 0; i < relayCards.size(); i++) {
      if (relayCards[i]->get_id() == relayCard->get_id()) {
        BiosLogger::DoLog.warning("ID for expansion card already taken");
        return;
      }
    }

    relayCard->register_change_handler(this, &HomeAutomator::process_changed_inputs);
    relayCards.push_back(relayCard);
  }

  void HomeAutomator::process_changed_inputs(ExpansionCard * card) {
    BiosLogger::DoLog.debug("Processing changed inputs");
    std::vector<Input*> inputs = ((IORelayCard*)card)->get_changed_inputs();
    for (unsigned int i = 0; i < inputs.size(); i++) {
      BiosLogger::DoLog.verbose(inputs[i]->to_string());

      BiosSimpleMqttClient::MQTTMessage * message = MQTTMessageFactory::create_input_state_update(inputs[i]);
      if (message) {
        mqttChannel->publish(*message);
        delete message;
      }
    }
  }

  void HomeAutomator::handle_mqtt_message(BiosSimpleMqttClient::MQTTMessage mqttMessage) {
    Event * event = EventFactory::create_event_from_mqtt_message(mqttMessage);
    if (event) {
      process_event(event);
    }
  }

  void HomeAutomator::process_event(Event * event) {
    for (unsigned int i = 0; i < relayCards.size(); i++) {
      if (relayCards[i]->get_id() == event->get_expansion_card_id()) {
        event->apply_event_on(relayCards[i]);
        return;
      }
    }
  }

};
