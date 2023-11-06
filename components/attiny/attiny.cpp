#include "attiny.h"
#include "esphome/core/log.h"

namespace esphome {
namespace attiny {

static const char *TAG = "attiny";

void attiny::setup() {
}

void attiny::loop() {

}



void attiny::write_binary(bool state) {
  this->write_str(ONOFF(state));
}



void attiny::write_float(float state) {
  
}

void attinyBOutput::dump_config() {
  LOG_BINARY_OUTPUT(this);
}

void attinyBOutput::write_state(bool state) {
  this->parent_->write_binary(state);
}

void attinyFOutput::dump_config() {
  LOG_FLOAT_OUTPUT(this);
}

void attinyFOutput::write_state(float state) {
  this->parent_->write_float(state);
}

void attinySwitch::dump_config() {
  LOG_SWITCH("", "UART Demo Switch", this);
}

void attinySwitch::write_state(bool state) {
  this->parent_->write_binary(state);
  this->publish_state(state);
}



}  // namespace attiny
}  // namespace esphome