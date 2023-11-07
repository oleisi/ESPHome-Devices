#include "esphome/core/log.h"
#include "attiny.h"

namespace esphome {
namespace attiny {

static const char *TAG = "attiny";

void attiny::setup() {
    // Tests
    /*
    this->enabled_->publish_state(true);
        if (this->voltage_ != nullptr){
    this->voltage_->publish_state(get_SleepTime/1000.0);
    };
    get_SleepTime = get_SleepTime+10;
    
    
  bool WakeUpRising;
  bool WakeUpFalling;
  bool WakeUpClock;
  bool SleepI2C;
  bool SleepClock;
  */ 
     
    uint8_t DataSetup;
    if (SleepI2C) {DataSetup = DataSetup + 1};
    DataSetup = DataSetup << 1;
    if (SleepClock) {DataSetup = DataSetup + 1};
    DataSetup = DataSetup << 1;
    if (WakeUpClock) {DataSetup = DataSetup + 1};
    DataSetup = DataSetup << 1;
    if (WakeUpFalling) {DataSetup = DataSetup + 1};
    DataSetup = DataSetup << 1;
    if (WakeUpRising) {DataSetup = DataSetup + 1};
    ESP_LOGD(TAG, "Datasetup: ");
    ESP_LOGD(TAG, DataSetup);
};

void attiny::loop() {

}
void attiny::update() {

     
}
void attiny::dump_config(){
    ESP_LOGCONFIG(TAG, "attiny I2C component");  
}

void attiny::write_binary(bool state) {
      if (this->sensor_ != nullptr) {
        this->sensor_->publish_state(state);
    }
}


void attinyDeepSleep::dump_config() {
  LOG_SWITCH("", "UART Demo Switch", this);
}

void attinyDeepSleep::write_state(bool state) {
  this->parent_->write_binary(state);
  this->publish_state(state);

}

}  // namespace empty_i2c_component
}  // namespace esphome