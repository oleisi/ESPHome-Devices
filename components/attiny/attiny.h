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

class attiny : public i2c::I2CDevice, public PollingComponent {
 public:
  attiny() : PollingComponent(1000) {}
  float get_setup_priority() const override { return setup_priority::HARDWARE; }
  void setup() override;
  void loop() override;
  void update() override;
  void dump_config() override;

  void set_voltage(sensor::Sensor *sensor) { voltage_ = sensor; }
  void set_sensor(binary_sensor::BinarySensor *sensor) { sensor_ = sensor; }
  void set_enabled(binary_sensor::BinarySensor *sensor) { enabled_ = sensor; }
  
  void deep_sleep();
  void read_I2C(uint8_t a_register, uint8_t *data, size_t len);
  void write_I2C_(uint8_t a_register, const uint8_t *data, size_t len);
  void write_binary(bool value);
  void set_WakeUpRising(bool state){ this->WakeUpRising = state;}
  void set_WakeUpFalling(bool state){ this->WakeUpFalling = state;}
  void set_WakeUpClock(bool state){ this->WakeUpClock = state;}
  void set_SleepI2C(bool state){ this->SleepI2C = state; }
  void set_SleepClock(bool state){ this->SleepClock = state; }
  void set_SleepTime(uint16_t value){ this->SleepTime = value; }
  void set_WakeTime(uint16_t value){ this->WakeTime = value; }
  
 protected:
  sensor::Sensor *voltage_{nullptr};
  binary_sensor::BinarySensor *sensor_{nullptr};
  binary_sensor::BinarySensor *enabled_{nullptr};
  bool WakeUpRising;
  bool WakeUpFalling;
  bool WakeUpClock;
  bool SleepI2C;
  bool SleepClock;
  bool LastSleep;
  bool Enable;
  bool Enable_old;
  bool Sensor;
  bool Sensor_old;
  bool DeepSleep;
  uint16_t SleepTime;
  uint16_t WakeTime;
  uint16_t voltage;
  uint16_t voltage_old;
  uint8_t I2C_Data[9];


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