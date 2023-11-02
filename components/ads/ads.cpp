#include "ads.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ads {

static const char* const TAG = "ads";

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
  if (this->read_register(MINI_ENCODER_C_FIRMWARE, &firmware, 1) !=
      i2c::ERROR_OK) {
    ESP_LOGE(TAG, "ads Setup Failed");
    this->mark_failed();
    return;
  }
  ESP_LOGI(TAG, "ads Firmware: %d", firmware);
}

void ads::setSetupValue(int8_t value) {
  uint8_t data;

  data = value & 0xff;

  if (this->write_register(MINI_ADS_C_Setup, value, 2) != i2c::ERROR_OK) {
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

  if (this->write_register(MINI_ADS_C_Wake, data, 2) != i2c::ERROR_OK) {
    ESP_LOGE(TAG, "ads wake setup failed");
    this->mark_failed();
  }
}

void ads::loop() {
  uint8_t data[2];
  if (this->read_register(MINI_ADS_C_Status, data, 1) != i2c::ERROR_OK) {
    ESP_LOGE(TAG, "unable to read button level");
    this->mark_failed();
    return;
  }
  bool button_state = data[0] == 0x01;
  if (this->button_ != nullptr) {
    if (!this->button_->has_state() || (this->button_->state != button_state)) {
      ESP_LOGD(TAG, "ads button: %d", button_state);
      this->button_->publish_state(button_state);
    }
  }
}

}  // namespace ads
}  // namespace esphome