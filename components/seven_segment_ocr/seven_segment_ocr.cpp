#ifdef USE_ESP32

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
        static const char *const TAG = "seven_segment_ocr";

        SevenSegmentOCR::SevenSegmentOCR() {}

        SevenSegmentOCR::~SevenSegmentOCR() {}

        void SevenSegmentOCR::setup()
        {
            if (!esp32_camera::global_esp32_camera || esp32_camera::global_esp32_camera->is_failed())
            {
                this->mark_failed();
                return;
            }

            esp32_camera::global_esp32_camera->add_image_callback([this](std::shared_ptr<esp32_camera::CameraImage> image)
                                                                  {
                                                                      ESP_LOGD(TAG, "Image received len=%d", image->get_data_length());
                                                                      // this->image_ = std::move(image);
                                                                  });
        }

        void SevenSegmentOCR::dump_config()
        {
            ESP_LOGCONFIG(TAG, "Seven segment OCR:");

            if (this->is_failed())
            {
                ESP_LOGE(TAG, "  Setup Failed");
            }
        }

        float SevenSegmentOCR::get_setup_priority() const { return setup_priority::LATE; }

        void SevenSegmentOCR::loop()
        {
        }
    } // namespace seven_segment_ocr
} // namespace esphome

#endif // USE_ESP32