#include "esphome/core/log.h"
#include "ads.h"

namespace esphome {
namespace empty_switch {

static const char *TAG = "ads.switch";

void ads::setup() {

}

void ads::write_state(bool state) {

}

void ads::dump_config(){
    ESP_LOGCONFIG(TAG, "ads custom switch");
}

} //namespace empty_switch
} //namespace esphome