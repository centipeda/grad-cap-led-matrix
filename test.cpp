// for testing the SparkFun matrix
#include "led-matrix.h"

#include <signal.h>
#include <unistd.h>
using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
    interrupt_received = true;
}

static void draw(Canvas *canvas) {
  for (int y = 0; y < canvas->height(); ++y) {
     for (int x = 0; x < canvas->width(); ++x) {
        canvas->SetPixel(x, y, 255, 255, 255);
        usleep(10 * 1000);
        if(interrupt_received) return;
     }
  }
}



int main(int argc, char *argv[]) {
  RGBMatrix::Options defaults;
  defaults.rows = 32;
  defaults.chain_length = 1;
  defaults.parallel = 1;
  Canvas *canvas = rgb_matrix::CreateMatrixFromFlags(&argc, &argv, &defaults);
  if (canvas == NULL)
    return 1;
  signal(SIGTERM, InterruptHandler);
  signal(SIGINT, InterruptHandler);

  draw(canvas);

  canvas->Clear();
  delete canvas;

  return 0;
  }