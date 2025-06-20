#pragma once

#include "esphome/components/sensor/sensor.h"
#include "esphome/core/component.h"
#include "esphome/core/automation.h"

namespace esphome {
namespace humidifier {

// 팬모드 고정
static const std::vector<std::string> DEFAULT_FAN_MODES = {"OFF", "LOW", "MEDIUM", "HIGH"};

class Humidifier : public Component {
 public:
  void setup() override {}
  void dump_config() override {}
  void loop() override {}

  void set_humidity_sensor(sensor::Sensor *sensor) { humidity_sensor_ = sensor; }
  void set_supported_fan_modes(const std::vector<std::string> &modes) { fan_modes_ = modes; }
  void set_min_humidity(float min) { min_humidity_ = min; }
  void set_max_humidity(float max) { max_humidity_ = max; }

  // Triggers for automations
  Trigger<> *get_turn_on_trigger() { return &on_turn_on_trigger_; }
  Trigger<> *get_turn_off_trigger() { return &on_turn_off_trigger_; }
  Trigger<std::string> *get_fan_mode_trigger() { return &on_fan_mode_trigger_; }
  Trigger<float> *get_target_humidity_trigger() { return &on_target_humidity_trigger_; }

  void set_fan_mode(const std::string &mode) {
    current_fan_mode_ = mode;
    on_fan_mode_trigger_.trigger(mode);
    update_fan_output_();
  }
  void set_target_humidity(float value) {
    current_target_humidity_ = value;
    on_target_humidity_trigger_.trigger(value);
  }

  // 상태 조회용 getter
  const std::string &get_fan_mode() const { return current_fan_mode_; }
  float get_target_humidity() const { return current_target_humidity_; }
  float get_current_humidity() const { return current_humidity_; }

 protected:
  sensor::Sensor *humidity_sensor_{nullptr};
  std::vector<std::string> fan_modes_ = DEFAULT_FAN_MODES;
  float min_humidity_{30};
  float max_humidity_{80};

  // Triggers
  Trigger<> on_turn_on_trigger_;
  Trigger<> on_turn_off_trigger_;
  Trigger<std::string> on_fan_mode_trigger_;
  Trigger<float> on_target_humidity_trigger_;

  // States
  std::string current_fan_mode_ = "OFF";
  float current_humidity_{NAN};
  float current_target_humidity_{50};

  void update_fan_output_() {
    // 팬 모드에 따른 실제 동작 구현 필요
  }
};

// 액션: 팬 모드 변경
template<typename... Ts>
class HumidifierSetFanModeAction : public Action<Ts...> {
 public:
  explicit HumidifierSetFanModeAction(Humidifier *parent) : parent_(parent) {}
  TEMPLATABLE_VALUE(std::string, fan_mode)
  void play(Ts... x) override { parent_->set_fan_mode(this->fan_mode_.value(x...)); }
 protected:
  Humidifier *parent_;
};

// 액션: 타겟 습도 변경
template<typename... Ts>
class HumidifierSetTargetHumidityAction : public Action<Ts...> {
 public:
  explicit HumidifierSetTargetHumidityAction(Humidifier *parent) : parent_(parent) {}
  TEMPLATABLE_VALUE(float, target_humidity)
  void play(Ts... x) override { parent_->set_target_humidity(this->target_humidity_.value(x...)); }
 protected:
  Humidifier *parent_;
};

}  // namespace humidifier
}  // namespace esphome
