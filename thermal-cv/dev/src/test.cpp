#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

#define odd(x) (x%2==0) ? x+1 : x

using namespace cv;

int threshold_value = 108;
int blur_value = 3;

Mat bin_thresh(Mat img);

int main(int argc, char **argv) {
  Mat src, src_gray, gray_cont, bin, dst;
  src = imread(argv[1], 1);
  cvtColor(src, src_gray, CV_BGR2GRAY);

  namedWindow("Test", CV_WINDOW_NORMAL);
  createTrackbar("Value", "Test",&threshold_value, 255);
  createTrackbar("Blur", "Test", &blur_value, 15);

  bool run = true;
  while(run) {
    src_gray.convertTo(gray_cont, -1, 2, 1);
    bin = bin_thresh(gray_cont);
    medianBlur(bin, dst, odd(blur_value));
    imshow("Test", dst);
    char c;
    c = waitKey(20);
    switch (c) {
      case 27:
        run = false;
        break;
    }
  }
}

Mat bin_thresh(Mat src) {
  Mat dst;
  threshold(src, dst, threshold_value, 255, 3);
  return dst;
}
