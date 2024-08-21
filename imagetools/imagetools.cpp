#include "imagetools.h"
#define M_IMAGE_IMPLEMENTATION
#define M_MATH_IMPLEMENTATION
#include "m_image.h"
#include "m_math.h"
#include "m_raster.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize2.h"
#include <cstring>
#include <fstream>
#include <iostream>

namespace langdal {
namespace it {
ImageTools::ImageTools() {}

ImageTools ::~ImageTools() {}
} // namespace it
} // namespace langdal

// static struct m_image tmp_buffer = M_IMAGE_IDENTITY();
// static struct m_image tmpi = M_IMAGE_IDENTITY();

// static void clear(void) {
//   m_image_destroy(&tmp_buffer);
//   m_image_destroy(&tmpi);
// }

// static void dostuff() {
//   std::cout << "Hello World!";
//   clear();
//   struct m_image foo1 = M_IMAGE_IDENTITY();
//   struct m_image foo2 = M_IMAGE_IDENTITY();
//   int x, y;

//   m_image_create(&foo1, M_FLOAT, 256, 256, 1);
//   memset(foo1.data, 0, foo1.size * sizeof(float)); // clear to zero

//   y = 128;
//   x = 128;
//   ((float *)foo1.data)[y * foo1.width + x] = 1.0f; // set (x, y) pixel to one

//   m_image_gaussian_blur(&foo2, &foo1, 3, 3); // apply Gaussian blur

//   m_image_destroy(&foo2);
//   m_image_destroy(&foo1);
// }

void print_image_details(m_image *img) {
  std::cout << "width: " << img->width << " height: " << img->height
            << " comp: " << img->comp << " size: " << img->size << std::endl;
}

int main() {
  // Load image from file using stb_image
  int width, height, channels;
  unsigned char *data =
      stbi_load("progress-0-2009.jpg", &width, &height, &channels, 0);
  if (data == nullptr) {
    std::cerr << "Failed to load image" << std::endl;
    return 1;
  } else {
    std::cout << "Image loaded successfully x: " << width << " y: " << height
              << " channels: " << channels
              << " size: " << width * height * channels << std::endl;
  }

  size_t img_size = width * height * channels;
  int gray_channels = channels == 4 ? 2 : 1;
  size_t gray_img_size = width * height * gray_channels;
  unsigned char *gray_img = (unsigned char *)malloc(gray_img_size);
  if (gray_img == NULL) {
    printf("Unable to allocate memory for the gray image.\n");
    exit(1);
  }

  for (unsigned char *p = data, *pg = gray_img; p != data + img_size;
       p += channels, pg += gray_channels) {
    *pg = (uint8_t)((*p + *(p + 1) + *(p + 2)) / 3.0);
    if (channels == 4) {
      *(pg + 1) = *(p + 3);
    }
  }

  struct m_image img = M_IMAGE_IDENTITY();
  m_image_create(&img, M_UBYTE, width, height, channels);
  memcpy(img.data, data, img.size * sizeof(unsigned char));
  stbi_image_free(data);
  print_image_details(&img);
  m_image_ubyte_to_float(&img, &img); // convert to float

  int new_height = 500;
  // calculate new width based on aspect ratio of original image
  int new_width = (int)((float)width / (float)height * new_height);
  m_image_resize(&img, &img, new_width, new_height); // resize image
  print_image_details(&img);

  m_image_grey(&img, &img); // convert to greyscale
  print_image_details(&img);
  m_image_gaussian_blur(&img, &img, 3, 3); // apply Gaussian blur

  // m_image_sobel(&img, &img); // apply sobel filter

  if (stbi_write_jpg("test_out_gray.jpg", width, height, 1, gray_img, 100) ==
      0) {
    std::cerr << "Failed to write image" << std::endl;
    return 1;
  }
  m_image_float_to_ubyte(&img, &img); // convert back to ubyte
  if (stbi_write_jpg("test_out.jpg", img.width, img.height, img.comp, img.data,
                     100) == 0) {
    std::cerr << "Failed to write image" << std::endl;
    return 1;
  }

  return 0;
}
