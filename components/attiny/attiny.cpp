#include "attiny.h"
#include "esphome/core/log.h"

namespace esphome {
namespace attiny {

static const char *TAG = "attiny";

void attiny::setup() {
}

void attiny::loop() {
  while (this->available()) {
    uint8_t c;
    this->read_byte(&c);
    this->handle_char_(c);
  }
}

void attiny::handle_char_(uint8_t c) {
  if (c == '\r')
    return;
  if (c == '\n') {
    std::string s(this->rx_message_.begin(), this->rx_message_.end());
    if (this->the_text_ != nullptr)
      this->the_text_->publish_state(s);
    if (this->the_sensor_ != nullptr)
      this->the_sensor_->publish_state(parse_number<float>(s).value_or(0));
    if (this->the_binsensor_ != nullptr)
      this->the_binsensor_->publish_state(s == "ON");
    this->rx_message_.clear();
    return;
  }
  this->rx_message_.push_back(c);
}

void attiny::dump_config() {
  LOG_TEXT_SENSOR("", "The Text Sensor", this->the_text_);
  LOG_SENSOR("", "The Sensor", this->the_sensor_);
}

void attiny::write_binary(bool state) {
  this->write_str(ONOFF(state));
}

void attiny::ping() {
  this->write_str("PING");
}

void attiny::write_float(float state) {
  this->write_str(to_string(state).c_str());
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

void attinyButton::dump_config() {
  LOG_BUTTON("", "UART Demo Button", this);
}

void attinyButton::press_action() {
  this->parent_->ping();
}

}  // namespace attiny
}  // namespace esphome