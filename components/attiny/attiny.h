#pragma once

#include "esphome/core/component.h"
#include "esphome/core/time.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/button/button.h"
#include "esphome/components/output/binary_output.h"
#include "esphome/components/output/float_output.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/switch/switch.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome.h"
#include "driver/rtc_io.h"
#include "esphome/esphome/components/time/real_time_clock.h"

namespace esphome {
namespace attiny {

class attiny : public i2c::I2CDevice, public PollingComponent {
 public:
  attiny() : PollingComponent(2000) {}
  float get_setup_priority() const override { return setup_priority::HARDWARE; }
  void setup() override;
  void loop() override;
  void update() override;
  void dump_config() override;

  void set_voltage(sensor::Sensor *sensor) { voltage_ = sensor; }
  void set_sensor(binary_sensor::BinarySensor *sensor) { sensor_ = sensor; }
  void set_enabled(binary_sensor::BinarySensor *sensor) { enabled_ = sensor; }
  
 
  
  void write_I2C_setup();
  void write_I2C_sleep(bool state);
  void read_I2C(bool initial);
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
  bool Sensor;
  bool DeepSleep;
  uint16_t SleepTime;
  uint16_t WakeTime;
  uint16_t Voltage;
  uint8_t I2C_Data[9] = {0,0,0,0,0,0,0,0,0};


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