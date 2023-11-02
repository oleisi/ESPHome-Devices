#pragma once

#include <utility>
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/automation.h"
#include "esphome/core/component.h"



namespace esphome {
namespace ads{

class ads : public i2c::I2CDevice, public Component {
 public:
  void setup() override;
  void loop() override;

  void set_number(uint8_t number) { number_ = number; }
  void set_min_value(int32_t min_value) { this->min_value_ = min_value; }
  void set_max_value(int32_t max_value) { this->max_value_ = max_value; }

  float get_setup_priority() const override;

 
  void set_Enable(binary_sensor::BinarySensor* Enable) {
    this->Enable_ = Enable;
  }
  void set_Int(binary_sensor::BinarySensor* Int) {
    this->Int_ = Int;
  }


 protected:
  uint8_t number_{0};
  int32_t value_{0};


  sensor::Sensor* voltage_value_{nullptr};
  binary_sensor::BinarySensor* Enable_{nullptr};
  binary_sensor::BinarySensor* Int_{nullptr};
  void setSetupValue(int16_t Value);
  void setSleepValue(int16_t Value);
  void setWakeValue(int16_t Value);
  
};


}  // namespace miniencoderc
}  // namespace esphome