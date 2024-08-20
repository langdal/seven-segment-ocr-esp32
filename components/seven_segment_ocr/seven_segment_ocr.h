#pragma once

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

    class SevenSegmentOCR : public text_sensor::TextSensor, public Component
    {
    public:
      SevenSegmentOCR();
      ~SevenSegmentOCR();
      void setup() override;
      void dump_config() override;
      void loop() override;

    protected:
      std::shared_ptr<esphome::esp32_camera::CameraImage> wait_for_image_();
      esp_err_t handler_(struct httpd_req *req);
      esp_err_t streaming_handler_(struct httpd_req *req);
      esp_err_t snapshot_handler_(struct httpd_req *req);

      SemaphoreHandle_t semaphore_;
      std::shared_ptr<esphome::esp32_camera::CameraImage> image_;
      bool running_{false};
    };

  } // namespace seven_segment_ocr
} // namespace esphome