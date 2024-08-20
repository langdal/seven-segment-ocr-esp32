#pragma once

#ifdef USE_ESP32

#include <cinttypes>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

#include "esphome/components/esp32_camera/esp32_camera.h"
#include "esphome/core/component.h"
#include "esphome/core/helpers.h"
#include "esphome/core/preferences.h"

namespace esphome
{
  namespace seven_segment_ocr
  {

    class SevenSegmentOCR : public Component
    {
    public:
      SevenSegmentOCR();
      ~SevenSegmentOCR();

      void setup() override;
      void dump_config() override;
      float get_setup_priority() const override;
      void loop() override;

    protected:
      std::shared_ptr<esphome::esp32_camera::CameraImage> image_;
    };

  } // namespace seven_segment_ocr
} // namespace esphome

#endif // USE_ESP32