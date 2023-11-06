#pragma once

#include <utility>
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/automation.h"
#include "esphome/core/component.h"
#include "switch/light.h"

// based on https://github.com/m5stack/M5Unit-MiniEncoderC/blob/main/src/Unit_MiniEncoderC.cpp
// https://docs.m5stack.com/en/hat/MiniEncoderC%20Hat

namespace esphome {
namespace ads {

class ads : public i2c::I2CDevice, public Component {
 public:
  void setup() override;
  void loop() override;
  float get_setup_priority() const override;
  void set_button(binary_sensor::BinarySensor* button) {
    this->button_ = button;
  }
 protected:
  binary_sensor::BinarySensor* button_{nullptr};
};





}  // namespace miniencoderc
}  // namespace esphome