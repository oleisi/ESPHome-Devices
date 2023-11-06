#pragma once

#include "esphome/core/component.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/output/binary_output.h"
#include "esphome/components/output/float_output.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/switch/switch.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace attiny {

class attiny : public Component,  public uart::UARTDevice {
 public:
  float get_setup_priority() const override { return setup_priority::LATE; }
  void setup() override;
  void loop() override;
  void dump_config() override;

  void set_the_text(text_sensor::TextSensor *text_sensor) { the_text_ = text_sensor; }
  void set_the_sensor(sensor::Sensor *sensor) { the_sensor_ = sensor; }
  void set_the_binsensor(binary_sensor::BinarySensor *sensor) { the_binsensor_ = sensor; }

  void write_binary(bool value);
  void write_float(float value);
  void ping();
 protected:
  text_sensor::TextSensor *the_text_{nullptr};
  sensor::Sensor *the_sensor_{nullptr};
  binary_sensor::BinarySensor *the_binsensor_{nullptr};

  void handle_char_(uint8_t c);
  std::vector<uint8_t> rx_message_;
};

class attinyBOutput : public Component, public output::BinaryOutput {
 public:
  void dump_config() override;
  void set_parent(attiny *parent) { this->parent_ = parent; }
 protected:
  void write_state(bool state) override;
  attiny *parent_;
};

class attinyFOutput : public Component, public output::FloatOutput {
 public:
  void dump_config() override;
  void set_parent(attiny *parent) { this->parent_ = parent; }
 protected:
  void write_state(float state) override;
  attiny *parent_;
};

class attinySwitch : public Component, public switch_::Switch {
 public:
  void dump_config() override;
  void set_parent(attiny *parent) { this->parent_ = parent; }
 protected:
  void write_state(bool state) override;
  attiny *parent_;
};

class attinyButton : public Component, public button::Button {
 public:
  void dump_config() override;
  void set_parent(attiny *parent) { this->parent_ = parent; }
 protected:
  void press_action() override;
  attiny *parent_;
};

}  // namespace attiny
}  // namespace esphome
