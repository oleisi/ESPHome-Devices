#include "esphome/core/log.h"
#include "attiny.h"
#include "esphome.h"
#include "driver/rtc_io.h"
#include "esphome/core/time.h"

namespace esphome {
namespace attiny {

static const char *TAG = "attiny";

void attiny::setup() {
  write_I2C_sleep(false);
  read_I2C(true);
  write_I2C_setup();
  
};

void attiny::loop() {

}
void attiny::update() {

  //read_I2C(true);
  time_t timestamp = time.timestamp;
  delay(1000);
  uint8_t time = timestamp - time.timestamp;
  ESP_LOGE(TAG, "Zeit: %d", time);
    
}
void attiny::dump_config(){
    ESP_LOGCONFIG(TAG, "attiny I2C component");  
}

void attiny::write_binary(bool state) {
      if (this->sensor_ != nullptr) {
        this->sensor_->publish_state(state);
      };
}

void attiny::read_I2C(bool initial) {
    // read 0x05 to 0x07
  for (uint8_t i = 5; i<=7; i++){
    uint8_t failures =0;
    while (this->read_register(i,&I2C_Data[i], 1) != i2c::ERROR_OK){
      failures++;
      ESP_LOGE(TAG, "Failed to Read I2C Register: %d, attempt: %d", i, failures);
      delay(failures+50);
      if(failures>20){
        this->mark_failed();
        }
      }
    ESP_LOGD(TAG, "Read I2C Register: %d, Value: %d", i , I2C_Data[i] );
    delay(50);
  }
  
   // Publish Voltage
  uint16_t Voltage_new = I2C_Data[5] | (I2C_Data[6] << 8);
  if (initial || (Voltage != Voltage_new)) {
    Voltage = Voltage_new;
    if (this->voltage_ != nullptr){
      this->voltage_->publish_state(Voltage/1000.0);
      };
  }

  // Publish Status Pin Enable
  bool Enable_new = (I2C_Data[7]& 0x01) == 0x01;
  if (initial || Enable != Enable_new) {
    Enable = Enable_new;
    if (this->enabled_ != nullptr) {
      this->enabled_->publish_state(Enable);
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

void attiny::write_I2C_setup(){
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
  uint8_t failures =0;
  while (this->write_register(0x00, I2C_Data, 5) != i2c::ERROR_OK) {
    failures++;
    ESP_LOGE(TAG, "Failed to Write I2C Setup Register, attempt: %d", failures);
    delay(failures+50);
    if(failures>20){
      this->mark_failed();
      }
    };
  delay(50);
}

void attiny::write_I2C_sleep(bool state) {
  if (state == true){
    I2C_Data[8]= I2C_Data[8] | 1;
  } else{
    I2C_Data[8]= I2C_Data[8] & 0xfe;
  };
  ESP_LOGE(TAG, "Sleep: %d", I2C_Data[8]);
  uint8_t failures =0;
  while (this->write_register(0x08, &I2C_Data[8], 1) != i2c::ERROR_OK) {
    failures++;
    ESP_LOGE(TAG, "Failed to Write I2C Sleep Register, attempt: %d", failures);
    delay(failures+50);
    if(failures>20){
      this->mark_failed();
      }
    };
    if (state)
    {
      esp_err_t result = esp_sleep_enable_timer_wakeup((SleepTime) * 1000 * 1000);
    if (result != ESP_OK) {
      ESP_LOGE(TAG, "Failed to enable timer wakeup: %d", result);
      return;
      }
      delay(50); // Allow last messages to be sent over MQTT
      App.run_safe_shutdown_hooks();
      ESP_LOGE(TAG, "Going too deepsleep");
      esp_deep_sleep_start();
    };
    
    
}
void attinyDeepSleep::dump_config() {
  LOG_SWITCH("", "UART Demo Switch", this);
}

void attinyDeepSleep::write_state(bool state) {
  this->publish_state(state);
  this->parent_->write_I2C_sleep(state);
}

}  // namespace empty_i2c_component
}  // namespace esphome