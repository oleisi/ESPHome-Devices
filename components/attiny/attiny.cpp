#include "esphome/core/log.h"
#include "attiny.h"

namespace esphome {
namespace attiny {

static const char *TAG = "attiny.component";

void attiny::setup() {

};

void attiny::loop() {

};

void attiny::dump_config(){
    ESP_LOGCONFIG(TAG, "attiny I2C component");  
};

void attinyDeepSleep::dump_config() {
  LOG_SWITCH("", "UART Demo Switch", this);
};

void attinyDeepSleep::write_state(bool state) {
  this->parent_->write_binary(state);
  this->publish_state(state);
}

}  // namespace empty_i2c_component
}  // namespace esphome