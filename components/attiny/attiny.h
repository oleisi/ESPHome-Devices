#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/switch/switch.h"

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

};


}  // namespace attiny
}  // namespace esphome