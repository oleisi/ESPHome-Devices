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
   uint16_t SleepTime;
  uint16_t WakeTime;
      uint8_t DataSetup;
    if (SleepI2C) {DataSetup = DataSetup + 1;};
    DataSetup = DataSetup << 1;
    if (SleepClock) {DataSetup = DataSetup + 1;};
    DataSetup = DataSetup << 1;
    if (WakeUpClock) {DataSetup = DataSetup + 1;};
    DataSetup = DataSetup << 1;
    if (WakeUpFalling) {DataSetup = DataSetup + 1;};
    DataSetup = DataSetup << 1;
    if (WakeUpRising) {DataSetup = DataSetup + 1;};
   
    ESP_LOGD(TAG, "Datasetup: %d", DataSetup);
  */ 
    DataSend[0] = 0;
    if (SleepI2C) {DataSend[0] = DataSend[0] + 1;};
    DataSend[0] = DataSend[0] << 1;
    if (SleepClock) {DataSend[0] = DataSend[0] + 1;};
    DataSend[0] = DataSend[0] << 1;
    if (WakeUpClock) {DataSend[0] = DataSend[0] + 1;};
    DataSend[0] = DataSend[0] << 1;
    if (WakeUpFalling) {DataSend[0] = DataSend[0] + 1;};
    DataSend[0] = DataSend[0] << 1;
    if (WakeUpRising) {DataSend[0] = DataSend[0] + 1;};
    DataSend[1] = SleepTime & 0xff;
    DataSend[2] = (SleepTime >> 8) & 0xff;
    DataSend[3] = WakeTime & 0xff;
    DataSend[4] = (WakeTime >> 8) & 0xff;
    DataSend[5] = 0;

};

void attiny::loop() {

}
void attiny::update() {

    ESP_LOGD(TAG, "DataSend[0]: %d", DataSend[0]);
    ESP_LOGD(TAG, "DataSend[1]: %d", DataSend[1]);
    ESP_LOGD(TAG, "DataSend[2]: %d", DataSend[2]);
    ESP_LOGD(TAG, "DataSend[3]: %d", DataSend[3]);
    ESP_LOGD(TAG, "DataSend[4]: %d", DataSend[4]);
    ESP_LOGD(TAG, "DataSend[5]: %d", DataSend[5]);
    if ( DataSend[5] == 0){
      DataSend[5] = 1;
    } else {
      DataSend[5] = 0;

    };
  if (this->write_register(0x00, DataSend, 5) != i2c::ERROR_OK) {
    ESP_LOGE(TAG, "Attiny Setup Failed");
    //this->mark_failed();
  }
    
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