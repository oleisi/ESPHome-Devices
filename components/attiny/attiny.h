#pragma once

#include "esphome/core/component.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/button/button.h"
#include "esphome/components/output/binary_output.h"
#include "esphome/components/output/float_output.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/switch/switch.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/i2c/i2c.h"


namespace esphome {
namespace attiny {

class attiny : public i2c::I2CDevice, public Component {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;

  void set_voltage(sensor::Sensor *sensor) { voltage_ = sensor; }
  void set_sensor(binary_sensor::BinarySensor *sensor) { sensor_ = sensor; }
  void set_enabled(binary_sensor::BinarySensor *sensor) { enabled_ = sensor; }
  
  void write_binary(bool value);
  void set_WakeUpRising(bool state){ this->get_WakeUpRising = state;}
  void set_WakeUpFalling(bool state){ this->get_WakeUpFalling = state;}
  void set_WakeUpClock(bool state){ this->get_WakeUpClock = state;}
  void set_SleepI2C(bool state){ this->get_SleepI2C = state; }
  void set_SleepClock(bool state){ this->get_SleepClock = state; }
  void set_SleepTime(uint16_t value){ this->get_SleepTime = value; }
  void set_WakeTime(uint16_t value){ this->get_WakeTime = value; }
  
 protected:
  sensor::Sensor *voltage_{nullptr};
  binary_sensor::BinarySensor *sensor_{nullptr};
  binary_sensor::BinarySensor *enabled_{nullptr};
  bool get_WakeUpRising;
  bool get_WakeUpFalling;
  bool get_WakeUpClock;
  bool get_SleepI2C;
  bool get_SleepClock;
  uint16_t get_SleepTime;
  uint16_t get_WakeTime;

};

class attinyDeepSleep : public Component, public switch_::Switch {
 public:
  void dump_config() override;
  void set_parent(attiny *parent) { this->parent_ = parent; }
 protected:
  void write_state(bool state) override;
  attiny *parent_;
};

}  // namespace attiny
}  // namespace esphome