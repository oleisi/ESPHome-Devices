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

  */ 
    I2C_Data[0] = 0;
    if (SleepI2C) {I2C_Data[0] = I2C_Data[0] + 1;};
    I2C_Data[0] = I2C_Data[0] << 1;
    if (SleepClock) {I2C_Data[0] = I2C_Data[0] + 1;};
    I2C_Data[0] = I2C_Data[0] << 1;
    if (WakeUpClock) {I2C_Data[0] = I2C_Data[0] + 1;};
    I2C_Data[0] = I2C_Data[0] << 1;
    if (WakeUpFalling) {I2C_Data[0] = I2C_Data[0] + 1;};
    I2C_Data[0] = I2C_Data[0] << 1;
    if (WakeUpRising) {I2C_Data[0] = I2C_Data[0] + 1;};
    I2C_Data[1] = SleepTime & 0xff;
    I2C_Data[2] = (SleepTime >> 8) & 0xff;
    I2C_Data[3] = WakeTime & 0xff;
    I2C_Data[4] = (WakeTime >> 8) & 0xff;
    if (this->write_register(0x00, I2C_Data, 5) != i2c::ERROR_OK) {
      ESP_LOGE(TAG, "Attiny write Setup Failed");
      this->mark_failed();
      };
};

void attiny::loop() {

}
void attiny::update() {
read_I2C();
/*
  if (this->read_register(0x02, DataReciev, 2) != i2c::ERROR_OK) {
    ESP_LOGE(TAG, "Attiny read Setup Failed");
    //this->mark_failed();
  }
    ESP_LOGD(TAG, "DataReciev[5]: %d", DataReciev[0]);
    */
}
void attiny::dump_config(){
    ESP_LOGCONFIG(TAG, "attiny I2C component");  
}

void attiny::write_binary(bool state) {
      if (this->sensor_ != nullptr) {
        this->sensor_->publish_state(state);
    }
}
void attiny::deep_sleep() {

}
void attiny::read_I2C() {
  if (this->read_register(0x05, I2C_Data, 3) != i2c::ERROR_OK) {
    ESP_LOGE(TAG, "Attiny read Setup Failed");
    //this->mark_failed();
  };
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