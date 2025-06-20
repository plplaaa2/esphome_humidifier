#include "esphome/components/humidifier/humidifier.h"

namespace esphome {
namespace humidifier {

Humidifier::Humidifier() = default;

void Humidifier::setup() {
  // 초기화 필요시 여기에 구현
}

void Humidifier::dump_config() {
  ESP_LOGCONFIG("humidifier", "Humidifier:");
  ESP_LOGCONFIG("humidifier", "  Supported fan modes: %s", 
                enumerate_list(this->fan_modes_).c_str());
  ESP_LOGCONFIG("humidifier", "  Min humidity: %.1f", this->min_humidity_);
  ESP_LOGCONFIG("humidifier", "  Max humidity: %.1f", this->max_humidity_);
  if (this->humidity_sensor_) {
    ESP_LOGCONFIG("humidifier", "  Humidity sensor: %s", this->humidity_sensor_->get_name().c_str());
  } else {
    ESP_LOGCONFIG("humidifier", "  No humidity sensor configured");
  }
}

void Humidifier::loop() {
  // 주기적으로 습도 센서 값을 읽어 상태 업데이트
  if (this->humidity_sensor_) {
    float value = this->humidity_sensor_->state;
    if (!std::isnan(value)) {
      current_humidity_ = value;
    }
  }
}

void Humidifier::set_humidity_sensor(sensor::Sensor *sensor) {
  this->humidity_sensor_ = sensor;
}
void Humidifier::set_supported_fan_modes(const std::vector<std::string> &modes) {
  this->fan_modes_ = modes;
}
void Humidifier::set_min_humidity(float min) {
  this->min_humidity_ = min;
}
void Humidifier::set_max_humidity(float max) {
  this->max_humidity_ = max;
}

Trigger<> *Humidifier::get_turn_on_trigger() { return &on_turn_on_trigger_; }
Trigger<> *Humidifier::get_turn_off_trigger() { return &on_turn_off_trigger_; }
Trigger<std::string> *Humidifier::get_fan_mode_trigger() { return &on_fan_mode_trigger_; }
Trigger<float> *Humidifier::get_target_humidity_trigger() { return &on_target_humidity_trigger_; }

void Humidifier::set_fan_mode(const std::string &mode) {
  if (mode == current_fan_mode_) return;
  current_fan_mode_ = mode;
  on_fan_mode_trigger_.trigger(mode);
  update_fan_output_();
}

void Humidifier::set_target_humidity(float value) {
  if (value == current_target_humidity_) return;
  current_target_humidity_ = value;
  on_target_humidity_trigger_.trigger(value);
}

const std::string &Humidifier::get_fan_mode() const {
  return current_fan_mode_;
}
float Humidifier::get_target_humidity() const {
  return current_target_humidity_;
}
float Humidifier::get_current_humidity() const {
  return current_humidity_;
}

void Humidifier::update_fan_output_() {
  // 팬 모드에 따른 실제 동작 구현 필요
  // 예: GPIO 제어 등
}

}  // namespace humidifier
}  // namespace esphome
