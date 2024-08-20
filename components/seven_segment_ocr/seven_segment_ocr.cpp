#include "seven_segment_ocr.h"
#include "esphome/core/application.h"
#include "esphome/core/hal.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"
#include "esphome/core/util.h"

#include <cstdlib>
#include <utility>

namespace esphome
{
    namespace seven_segment_ocr
    {

        static const char *TAG = "seven_segment_ocr.text_sensor";
        static const int IMAGE_REQUEST_TIMEOUT = 5000;

        SevenSegmentOCR::SevenSegmentOCR()
        {
        }

        SevenSegmentOCR::~SevenSegmentOCR()
        {
        }

        void SevenSegmentOCR::setup()
        {
            if (!esp32_camera::global_esp32_camera || esp32_camera::global_esp32_camera->is_failed())
            {
                this->mark_failed();
                return;
            }

            this->semaphore_ = xSemaphoreCreateBinary();

            esp32_camera::global_esp32_camera->add_image_callback([this](std::shared_ptr<esp32_camera::CameraImage> image)
                                                                  {
    if (this->running_ && image->was_requested_by(esp32_camera::WEB_REQUESTER)) {
      this->image_ = std::move(image);
      xSemaphoreGive(this->semaphore_);
    } });
        }

        void SevenSegmentOCR::dump_config()
        {
            ESP_LOGCONFIG(TAG, "Seven Segment OCR:");
            if (this->is_failed())
            {
                ESP_LOGE(TAG, "  Setup Failed");
            }
            else
            {
                ESP_LOGCONFIG(TAG, "  Running");
            }
        }

        float SevenSegmentOCR::get_setup_priority() const { return setup_priority::LATE; }

        void SevenSegmentOCR::loop()
        {
            if (!this->running_)
            {
                this->image_ = nullptr;
            }
        }
    } // namespace seven_segment_ocr
} // namespace esphome