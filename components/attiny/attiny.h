#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace attiny {

class attiny : public i2c::I2CDevice, public Component {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
};


}  // namespace attiny
}  // namespace esphome