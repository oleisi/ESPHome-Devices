#include "ads.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ads {

static const char* const TAG = "mini_encoder_c";

static const uint8_t MINI_ADS_C_FIRMWARE = 0x01;
static const uint8_t MINI_ADS_C_Setup = 0x02;
static const uint8_t MINI_ADS_C_Sleep = 0x03;
static const uint8_t MINI_ADS_C_Wake = 0x05;
static const uint8_t MINI_ADS_C_Voltage = 0x07;
static const uint8_t MINI_ADS_C_Status = 0x09;
static const uint8_t MINI_ADS_C_Control = 0x0A;

float ads::get_setup_priority() const {
  return setup_priority::IO;
}

void ads::setup() {
  ESP_LOGI(TAG, "Setting up ads...");
  uint8_t firmware;
  if (this->read_register(MINI_ADS_C_FIRMWARE, &firmware, 1) !=
      i2c::ERROR_OK) {
    ESP_LOGE(TAG, "ads Setup Failed");
    this->mark_failed();
    return;
  }
  setSetupValue(5);
  setSleepValue(10);
  setWakeValue(10);
  ESP_LOGI(TAG, "ads Firmware: %d", firmware);
}
void ads::setSetupValue(int8_t value) {
  uint8_t data;

  data = value & 0xff;

  if (this->write_register(MINI_ADS_C_Sleep, value, 2) != i2c::ERROR_OK) {
    ESP_LOGE(TAG, "ads sleep setup failed");
    this->mark_failed();
  }
}
void ads::setSleepValue(int16_t value) {
  uint8_t data[2];

  data[0] = value & 0xff;
  data[1] = (value >> 8) & 0xff;

  if (this->write_register(MINI_ADS_C_Sleep, data, 2) != i2c::ERROR_OK) {
    ESP_LOGE(TAG, "ads sleep setup failed");
    this->mark_failed();
  }
}
void ads::setWakeValue(int16_t value) {
  uint8_t data[2];

  data[0] = value & 0xff;
  data[1] = (value >> 8) & 0xff;

  if (this->write_register(MINI_ADS_C_ENCODER, data, 2) != i2c::ERROR_OK) {
    ESP_LOGE(TAG, "ads wake setup failed");
    this->mark_failed();
  }
}
void ads::loop() {
  uint8_t data[2];  
  if (this->read_register(MINI_ADS_C_Voltage, data, 2) != i2c::ERROR_OK) {
    ESP_LOGE(TAG, "unable to read Voltage level");
    this->mark_failed();
    return;
  }
  int32_t voltage_value = data[0] | (data[1] << 8);

  if (this->voltage_value_ != nullptr) {
    if (!this->voltage_value_->has_state() ||
        (this->voltage_value_->state != voltage_value)) {
        ESP_LOGD(TAG, "Voltage value: %d ", voltage_value);
        this->encoder_value_->publish_state(voltage_value);
    }
  }
    if (this->read_register(MINI_ADS_C_Status, data, 1) != i2c::ERROR_OK) {
    ESP_LOGE(TAG, "unable to read Status");
    this->mark_failed();
    return;
  }
  bool Enable_state = data[0] & 0x01 == 0x01;
  if (this->Enable_ != nullptr) {
    if (!this->Enable_->has_state() || (this->Enable_->state != Enable_state)) {
      ESP_LOGD(TAG, "ads Enable: %d", Enable_state);
      this->Enable_->publish_state(Enable_state);
    }
  }
  bool Int_state = data[0] & 0x02 == 0x02;
  if (this->Int_ != nullptr) {
    if (!this->Int_->has_state() || (this->Int_->state != Int_state)) {
      ESP_LOGD(TAG, "ads Int: %d", Int_state);
      this->Int_->publish_state(Int_state);
    }
  }
}

}  // namespace ads
}  // namespace esphome