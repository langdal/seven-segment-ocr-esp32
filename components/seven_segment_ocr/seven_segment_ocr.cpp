#ifdef USE_ESP32

#include "seven_segment_ocr.h"
#include "esphome/core/application.h"
#include "esphome/core/log.h"

#undef EPS // specreg.h defines EPS which interfere with opencv
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#define EPS 192

#include <cstdlib>
#include <utility>

using namespace std;
using namespace cv;

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
            esp32_camera::global_esp32_camera->start_stream(esphome::esp32_camera::WEB_REQUESTER);

            esp32_camera::global_esp32_camera->add_image_callback([this](std::shared_ptr<esp32_camera::CameraImage> image)
                                                                  {
                                                                      ESP_LOGD(TAG, "Image received len=%d", image->get_data_length());
                                                                      if (image->was_requested_by(esp32_camera::WEB_REQUESTER))
                                                                      {
                                                                          ESP_LOGD(TAG, "My image len=%d", image->get_data_length());
                                                                      }

                                                                      camera_fb_t *data = image->get_raw_buffer();
                                                                      if (data->format == PIXFORMAT_JPEG)
                                                                      {

                                                                          ESP_LOGD(TAG, "Image format JPG");
                                                                          // load image into opencv mat
                                                                          cv::Mat mat(data->height, data->width, CV_8UC3, data->buf);
                                                                          // convert to grayscale
                                                                          cv::Mat gray;
                                                                          cv::cvtColor(mat, gray, cv::COLOR_BGR2GRAY);
                                                                          // print image size
                                                                          ESP_LOGD(TAG, "Image size: %d x %d", gray.cols, gray.rows);
                                                                      }
                                                                      else
                                                                      {
                                                                          ESP_LOGD(TAG, "Image format not JPG");
                                                                      }
                                                                      //   this->image_ = std::move(image);
                                                                  });
        }

        void SevenSegmentOCR::dump_config()
        {
            ESP_LOGCONFIG(TAG, "Seven segment OCR:");
            Mat blueImage(512, 512, CV_8UC1, Scalar(0, 0, 255));

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