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
   /*
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
    */
    read_I2C(true);


};

void attiny::loop() {

}
void attiny::update() {
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
      };
}
void attiny::deep_sleep() {

}
void attiny::read_I2C(bool initial) {
    // read 0x05    Voltage [mV] lsb uint16_t
  if (this->read_register(0x05, &Data[1], 1) != i2c::ERROR_OK) {
    ESP_LOGE(TAG, "Attiny I2C Failed");
    this->mark_failed();
    }:
  // read 0x06    Voltage [mV] msb uint16_t
  if (this->read_register(0x06, &I2C_Data[2], 1) != i2c::ERROR_OK) {
    ESP_LOGE(TAG, "Attiny I2C Failed");
    this->mark_failed();
    };
  //read 0x07 Pin Status
  if (this->read_register(0x07, &I2C_Data[7], 1) != i2c::ERROR_OK) {
    ESP_LOGE(TAG, "Attiny I2C Failed");
    this->mark_failed();
    };

  // Publish Voltage
  uint16_t Voltage_new = I2C_Data[5] | (I2C_Data[6] << 8);
  if (initial || (Voltage != Voltage_new)) {
    Voltage = Voltage_new;
    if (this->voltage_ != nullptr){
      this->voltage_->publish_state(voltage/1000.0);
      };
  }:

  // Publish Status Pin Enable
  bool Enable_new = (I2C_Data[7]& 0x01) == 0x01;
  if (initial || Enable != Enable_new) {
    Enable = Enable_new;
    if (this->enabled_ != nullptr) {
      this->enable_->publish_state(Enable);
    };
  }
  // Publish Status Pin Sensor
  bool Sensor_new = (I2C_Data[7]& 0x02) == 0x02;
  if (initial || Sensor != Sensor_new) {
    Sensor = Sensor_new;
    if (this->sensor_ != nullptr) {
      this->sensor_->publish_state(Sensor);
    };
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