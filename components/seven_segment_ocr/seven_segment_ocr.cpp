#include "esphome/core/log.h"
#include "seven_segment_ocr.h"

namespace esphome {
namespace seven_segment_ocr {

static const char *TAG = "seven_segment_ocr.text_sensor";

void SevenSegmentOCR::setup() {
  
}

void SevenSegmentOCR::dump_config() { 
    ESP_LOGCONFIG(TAG, "Seven Segment OCR:");
}

}  // namespace seven_segment_ocr
}  // namespace esphome