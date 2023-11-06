#include "esphome/core/log.h"
#include "attiny.h"

namespace esphome {
namespace attiny {

static const char *TAG = "attiny.component";

void attiny::setup() {

}

void attiny::loop() {

}

void attiny::dump_config(){
    ESP_LOGCONFIG(TAG, "attiny I2C component");  
}


}  // namespace empty_i2c_component
}  // namespace esphome