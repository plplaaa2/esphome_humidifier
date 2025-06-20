#pragma once

#include "esphome/components/climate/climate.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/component.h"

namespace esphome {
namespace humidifier {

class Humidifier : public climate::Climate, public Component {
 public:
  void setup() override;
  void control(const climate::ClimateCall &call) override;
  climate::ClimateTraits traits() override;

  void set_humidity_sensor(sensor::Sensor *sensor) { humidity_sensor_ = sensor; }
  void set_supported_fan_modes(const std::vector<std::string> &modes);

  // 트리거 getter
  Trigger<> *get_turn_on_trigger();
  Trigger<> *get_turn_off_trigger();
  Trigger<std::string> *get_fan_mode_trigger();
  Trigger<float> *get_target_humidity_trigger();

 protected:
  sensor::Sensor *humidity_sensor_{nullptr};
  void update_fan_mode_(const std::string &fan_mode);
  void update_target_humidity_(float humidity);
  void update(); // 센서 polling용
};

}  // namespace humidifier
}  // namespace esphome
