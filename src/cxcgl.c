#ifndef CXCGL_C
#define CXCGL_C

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// CONSTANTS AND MACROS

#define ARRAY_SIZE(xs) (sizeof(xs) / sizeof(xs[0]))

#define return_defer(value) \
  do {                      \
    int result = (value);   \
    goto defer;             \
  } while (0)

// TYPEDEFS

typedef int Errno;
typedef uint8_t u8;
typedef uint32_t u32;

/**   --------------FUNCTIONS--------------    **/

/**
 * @brief Fills the entire pixel buffer with a single color.
 *
 * @param pixels Pointer to the pixel buffer.
 * @param width Width of the pixel buffer.
 * @param height Height of the pixel buffer.
 * @param color Color to fill the pixel buffer with.
 */
void cxcgl_fill(u32* pixels, size_t width, size_t height, u32 color) {
  for (size_t i = 0; i < width * height; ++i) {
    pixels[i] = color;
  }
}

/**
 * @brief Fills a rectangular region in the pixel buffer with a specified color.
 *
 * @param pixels Pointer to the pixel buffer.
 * @param canvas_width Width of the canvas.
 * @param canvas_height Height of the canvas.
 * @param x0 X-coordinate of the top-left corner of the rectangle.
 * @param y0 Y-coordinate of the top-left corner of the rectangle.
 * @param width Width of the rectangle.
 * @param height Height of the rectangle.
 * @param color Color to fill the rectangle with.
 */
void cxcgl_fill_rect(u32* pixels, size_t canvas_width, size_t canvas_height,
                     int x0, int y0, size_t width, size_t height, u32 color) {
  for (size_t dy = 0; dy < height; ++dy) {
    int y = dy + y0;

    if (y >= 0 && y < canvas_height) {
      for (size_t dx = 0; dx < width; ++dx) {
        int x = x0 + dx;

        if (x >= 0 && x < canvas_width) {
          pixels[y * canvas_width + x] = color;
        }
      }
    }
  }
}

/**
 * @brief Fills a centered rectangular region in the pixel buffer with a
 * specified color.
 *
 * @param pixels Pointer to the pixel buffer.
 * @param canvas_width Width of the canvas.
 * @param canvas_height Height of the canvas.
 * @param width Width of the rectangle.
 * @param height Height of the rectangle.
 * @param color Color to fill the rectangle with.
 */
void cxcgl_cfill_rect(u32* pixels, size_t canvas_width, size_t canvas_height,
                      size_t width, size_t height, u32 color) {
  for (size_t dy = 0; dy < height; ++dy) {
    int y = (canvas_height / 2 - height / 2) + dy;

    if (y >= 0 && y < canvas_height) {
      for (size_t dx = 0; dx < width; ++dx) {
        int x = (canvas_width / 2 - width / 2) + dx;

        if (x >= 0 && x < canvas_width) {
          pixels[y * canvas_width + x] = color;
        }
      }
    }
  }
}

/**
 * @brief Fills the pixel buffer with a checkered pattern.
 *
 * @param pixels Pointer to the pixel buffer.
 * @param canvas_width Width of the canvas.
 * @param canvas_height Height of the canvas.
 * @param cols Number of columns in the grid.
 * @param rows Number of rows in the grid.
 * @param color0 Color of the cells at even indices in the grid.
 * @param color1 Color of the cells at odd indices in the grid.
 */
void cxcgl_fill_check_pattern(u32* pixels, size_t canvas_width,
                              size_t canvas_height, size_t cols, size_t rows,
                              u32 color0, u32 color1) {
  int cell_width = canvas_width / cols;
  int cell_height = canvas_height / rows;

  for (size_t y = 0; y < rows; ++y) {
    for (size_t x = 0; x < cols; ++x) {
      u32 color;
      if ((x + y) % 2 == 0) {
        color = color0;
      } else {
        color = color1;
      }

      cxcgl_fill_rect(pixels, canvas_width, canvas_height, x * cell_width,
                      y * cell_height, cell_width, cell_width, color);
    }
  }
}

/**
 * @brief Saves a pixel buffer to a binary file in PPM (Portable Pixmap)
 * format.
 *
 * @param pixels Pointer to the pixel buffer.
 * @param width Width of the pixel buffer.
 * @param height Height of the pixel buffer.
 * @param file_path Path to the output file.
 * @return 0 on success, -1 on failure.
 */
Errno cxcgl_save_to_file(u32* pixels, size_t width, size_t height,
                         const char* file_path) {
  int result = 0;
  FILE* f = NULL;

  {
    f = fopen(file_path, "wb");
    if (f == NULL) return_defer(-1);

    fprintf(f, "P6\n%zu %zu 255\n", width, height);
    if (ferror(f)) return_defer(-1);

    for (size_t i = 0; i < width * height; ++i) {
      // 0xAABBGGRR (RGB-A Format)
      u32 pixel = pixels[i];
      u8 bytes[3] = {(pixel) & 0xFF, (pixel >> 8) & 0xFF,
                     (pixel >> 8 * 2) & 0xFF};

      fwrite(bytes, sizeof(bytes), 1, f);
      if (ferror(f)) return_defer(-1);
    }
  }

defer:
  if (f) fclose(f);
  return result;
}

#endif