#pragma once

#include "esphome/core/component.h"
#include "esphome/components/tuya/tuya.h"
#include "esphome/components/fan/fan.h"

namespace esphome::tuya {

class TuyaFan final : public Component, public fan::Fan {
 public:
  TuyaFan(Tuya *parent, int speed_count) : parent_(parent), speed_count_(speed_count) {}
  void setup() override;
  void dump_config() override;
  void set_speed_id(uint8_t speed_id) { this->speed_id_ = speed_id; }
  void set_switch_id(uint8_t switch_id) { this->switch_id_ = switch_id; }
  void set_oscillation_id(uint8_t oscillation_id) { this->oscillation_id_ = oscillation_id; }
  void set_direction_id(uint8_t direction_id) { this->direction_id_ = direction_id; }
  void set_direction_inverted(bool direction_inverted) { this->direction_inverted_ = direction_inverted; }

  fan::FanTraits get_traits() override;

 protected:
  void control(const fan::FanCall &call) override;
  bool get_actual_direction_(const bool direction) { return direction ^ this->direction_inverted_; }

  Tuya *parent_;
  optional<uint8_t> speed_id_{};
  optional<uint8_t> switch_id_{};
  optional<uint8_t> oscillation_id_{};
  optional<uint8_t> direction_id_{};
  bool direction_inverted_{};
  int speed_count_{};
  TuyaDatapointType speed_type_{};
  TuyaDatapointType oscillation_type_{};
};

}  // namespace esphome::tuya
