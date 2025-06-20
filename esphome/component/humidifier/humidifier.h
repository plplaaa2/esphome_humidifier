#pragma once

#include "esphome/components/climate/climate.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/component.h"
#include "esphome/core/automation.h"

namespace esphome {
namespace humidifier {

class Humidifier : public climate::Climate, public Component {
 public:
  void setup() override;
  void dump_config() override;
  void loop() override;
  climate::ClimateTraits traits() override;
  void control(const climate::ClimateCall &call) override;

  void set_humidity_sensor(sensor::Sensor *sensor) { humidity_sensor_ = sensor; }
  void set_supported_fan_modes(const std::vector<std::string> &modes) { fan_modes_ = modes; }
  void set_min_humidity(float min) { min_humidity_ = min; }
  void set_max_humidity(float max) { max_humidity_ = max; }

  // Triggers for automations
  Trigger<> *get_turn_on_trigger() { return &on_turn_on_trigger_; }
  Trigger<> *get_turn_off_trigger() { return &on_turn_off_trigger_; }
  Trigger<std::string> *get_fan_mode_trigger() { return &on_fan_mode_trigger_; }
  Trigger<float> *get_target_humidity_trigger() { return &on_target_humidity_trigger_; }

  void set_fan_mode(const std::string &mode);
  void set_target_humidity(float value);

 protected:
  sensor::Sensor *humidity_sensor_{nullptr};
  std::vector<std::string> fan_modes_ = {"OFF", "LOW", "MEDIUM", "HIGH"};
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

  void update_fan_output_();
};


// 액션: 팬 모드 변경
template<typename... Ts>
class HumidifierSetFanModeAction : public Action<Ts...> {
 public:
  explicit HumidifierSetFanModeAction(Humidifier *parent) : parent_(parent) {}
  TEMPLATABLE_VALUE
