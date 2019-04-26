#include "led-matrix.h"
#include "graphics.h"

#include "unistd.h"
using namespace rgb_matrix;


// interrupt handling...
volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
  interrupt_received = true;
}

static void draw(Canvas *canvas) {
  Font font;
  font.LoadFont("fonts/10x20.bdf");
  Color text_color(128, 128, 128);
  DrawText(canvas, font, 0, 0, text_color, NULL, "NO");
  usleep (5000 * 1000);

}

int main (int argc, char *argv[]) {
  // create the matrix with options
  RGBMatrix::Options defaults;
  Canvas *canvas = CreateMatrixFromFlags(&argc, &argv, &defaults);
    if (canvas == NULL) return 1;
  
  // interrupt handling
  signal(SIGTERM, InterruptHandler);
  signal(SIGINT, InterruptHandler);

  draw(canvas);
  
  // cleanup
  canvas->Clear();
  delete canvas;

  return 0;
}