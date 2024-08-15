#pragma once

#include "esphome/core/component.h"
#include "esphome/components/text_sensor/text_sensor.h"

namespace esphome {
namespace seven_segment_ocr {

class SevenSegmentOCR : public text_sensor::TextSensor, public Component {
 public:
  void setup() override;
  void dump_config() override;
};

}  // namespace seven_segment_ocr
}  // namespace esphome