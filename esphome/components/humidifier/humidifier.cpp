#include "humidifier.h"
#include "esphome/core/log.h"

namespace esphome {
namespace humidifier {

static const char *const TAG = "humidifier";

void Humidifier::setup() {
  ESP_LOGCONFIG(TAG, "Setting up Humidifier...");
  // (Optional) Initial hardware setup
}

void Humidifier::dump_config() {
  ESP_LOGCONFIG(TAG, "Humidifier:");
  LOG_COMPONENT("", "  ", this);
  if (this->humidity_sensor_ != nullptr)
    ESP_LOGCONFIG(TAG, "  Linked humidity sensor: %p", this->humidity_sensor_);
  else
    ESP_LOGCONFIG(TAG, "  No humidity sensor linked.");
  ESP_LOGCONFIG(TAG, "  Supported fan modes: %s", vector_to_string(this->fan_modes_).c_str());
  ESP_LOGCONFIG(TAG, "  Min humidity: %.1f", this->min_humidity_);
  ESP_LOGCONFIG(TAG, "  Max humidity: %.1f", this->max_humidity_);
}

void Humidifier::loop() {
  // Poll humidity sensor and update state
  if (humidity_sensor_ != nullptr && humidity_sensor_->has_state()) {
    float humidity = humidity_sensor_->state;
    if (this->current_humidity_ != humidity) {
      this->current_humidity_ = humidity;
      this->current_humidity = humidity;
      this->publish_state();
    }
  }
}

climate::ClimateTraits Humidifier::traits() {
  auto traits = climate::ClimateTraits();
  traits.set_supports_current_humidity(true);
  traits.set_supports_target_humidity(true);
  traits.set_supported_fan_modes(this->fan_modes_);
  traits.set_supported_modes({
    climate::CLIMATE_MODE_OFF,
    climate::CLIMATE_MODE_AUTO,   // 자동
    climate::CLIMATE_MODE_MANUAL  // 수동
  });
  traits.set_min_humidity(this->min_humidity_);
  traits.set_max_humidity(this->max_humidity_);
  return traits;
}

void Humidifier::control(const climate::ClimateCall &call) {
  // 목표 습도 설정
  if (call.get_target_humidity().has_value()) {
    float value = *call.get_target_humidity();
    this->target_humidity = value;
    on_target_humidity_trigger_.trigger(value);
  }

  // 팬 모드 설정
  if (call.get_fan_mode().has_value()) {
    this->set_fan_mode(*call.get_fan_mode());
  }

  // 운전 모드 처리
  if (call.get_mode().has_value()) {
    if (*call.get_mode() == climate::CLIMATE_MODE_OFF) {
      on_turn_off_trigger_.trigger();
      // 팬 꺼짐 등 실제 동작 추가 가능
    } else if (*call.get_mode() == climate::CLIMATE_MODE_AUTO) {
      on_turn_on_trigger_.trigger();
      // 자동 운전(목표 습도/현재 습도 비교) 구현 가능
    } else if (*call.get_mode() == climate::CLIMATE_MODE_MANUAL) {
      on_turn_on_trigger_.trigger();
      // 수동 운전(팬/습도 명령만 반영) 구현 가능
    }
  }
  this->publish_state();
}

void Humidifier::set_fan_mode(const std::string &mode) {
  if (this->current_fan_mode_ != mode) {
    this->current_fan_mode_ = mode;
    this->fan_mode = mode;
    on_fan_mode_trigger_.trigger(mode);
    update_fan_output_();
  }
}

void Humidifier::set_target_humidity(float value) {
  this->target_humidity = value;
  on_target_humidity_trigger_.trigger(value);
  this->publish_state();
}

void Humidifier::update_fan_output_() {
  // 실제 팬 제어 로직 (릴레이, PWM 등)
  if (current_fan_mode_ == "OFF") {
    // turn fan off
  } else if (current_fan_mode_ == "LOW") {
    // set fan to low speed
  } else if (current_fan_mode_ == "MEDIUM") {
    // set fan to medium speed
  } else if (current_fan_mode_ == "HIGH") {
    // set fan to high speed
  }
}

}  // namespace humidifier
}  // namespace esphome
