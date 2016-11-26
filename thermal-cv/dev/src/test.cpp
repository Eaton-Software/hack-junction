#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

int threshold_value = 108;
Mat src, src_gray, dst;

void bin_thresh();

int main(int argc, char **argv) {
  src = imread(argv[1], 1);
  cvtColor(src, src_gray, CV_BGR2GRAY);
  namedWindow("Test", CV_WINDOW_NORMAL);
  createTrackbar("Value", "Test",&threshold_value, 255);

  bool run = true;
  while(run) {
    bin_thresh();
    char c;
    c = waitKey(20);
    switch (c) {
      case '27':
        run = false;
        break;
    }
  }
}

void bin_thresh() {
  threshold(src_gray, dst, threshold_value, 255, 3);
  imshow("Test", dst );
}
