#include "cxcgl.c"

#define WIDTH 600
#define HEIGHT 600
#define CANVAS_SIZE (WIDTH * HEIGHT)

#define COLS 8
#define ROWS 8
// #define CELL_WIDTH (WIDTH / COLS)
// #define CELL_HEIGHT (HEIGHT / ROWS)

static u32 pixels[CANVAS_SIZE];

int main() {
  // cxcgl_fill(pixels, WIDTH, HEIGHT, 0x00CC000);

  // cxcgl_cfill_rect(pixels, WIDTH, HEIGHT, 76 * 2, 76 * 2, 0x000000FF);
  // cxcgl_fill_rect(pixels, WIDTH, HEIGHT, 50, 50, 50, 50, 0x00CC000);
  // cxcgl_fill_rect(pixels, WIDTH, HEIGHT, 400, 400, 75, 75, 0x00CC0AA);

  // cxcgl_fill_check_pattern(pixels, WIDTH, HEIGHT, ROWS, COLS, 0x000000ff,
  //                          0x00000000);

  cxcgl_fill_check_pattern(pixels, WIDTH, HEIGHT, 8, 8, 0x00AF0000, 0x00000000);
  cxcgl_save_to_file(pixels, WIDTH, HEIGHT, "output.ppm");

  printf("Welcome from CXCGL.\nSize of Canvas: %d", CANVAS_SIZE);

  return 0;
}