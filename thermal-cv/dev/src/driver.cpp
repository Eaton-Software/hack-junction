#include <fstream>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "driver.hpp"

const std::string GUI_NAME = "Thermal Imaging";

int main(int argc, char **argv) {

  std::vector<std::string> image_names{
      // Image paths
      "./img/ir_people_0.tif", "./img/ir_people_1_close.tif",
      "./img/ir_people_1_far.tif", "./img/ir_people_2.tif",
  };

  std::vector<std::vector<cv::Mat>> images;
  for (int i = 0; i < image_names.size(); i++) {
    std::cout << "Currently loading " << image_names[i] << "...\n";
    cv::Mat image = cv::imread(image_names[i], CV_LOAD_IMAGE_COLOR);
    std::vector<cv::Mat> loaded_images{image, image.clone()};
    if (!loaded_images[0].data || !loaded_images[1].data) {
      fprintf(stderr, "Image loading failure\n");
      return 1;
    }
    images.push_back(loaded_images);
  }

  std::vector<std::string> window_names{
      // Window names
      "No people", "One person, close", "One person, far", "Two people",
  };

  for (int i = 0; i < window_names.size(); i++) {
    std::cout << "Creating window " << window_names[i] << "...\n";
    cv::namedWindow(window_names[i], cv::WINDOW_NORMAL);
  }

  // Control Panel Setup
  cv::namedWindow("Control", CV_WINDOW_NORMAL); // create a window called "Control"
  int iLowH = 0;
  int iHighH = 10;
  int iLowS = 230;
  int iHighS = 250;
  int iLowV = 180;
  int iHighV = 226;
  int iStrel = 5;
  cvCreateTrackbar("LowH", "Control", &iLowH, 179); // Hue (0 - 179)
  cvCreateTrackbar("HighH", "Control", &iHighH, 179);
  cvCreateTrackbar("LowS", "Control", &iLowS, 255); // Saturation (0 - 255)
  cvCreateTrackbar("HighS", "Control", &iHighS, 255);
  cvCreateTrackbar("LowV", "Control", &iLowV, 255); // Value (0 - 255)
  cvCreateTrackbar("HighV", "Control", &iHighV, 255);
  cvCreateTrackbar("Strel Size", "Control", &iStrel, 30);

  bool run = true;
  while (run) {
    for (int i = 0; i < window_names.size(); i++) {
      cv::imshow(window_names[i], images[i][1]);
    }
    char c = cvWaitKey(20);
    std::vector<int> log_mask;
    switch (c) {
    case 27: // Escape
      run = false;
      break;
    case ' ': // Revert to original
      for (auto &img : images)
        img[1] = img[0].clone();
      break;
    case 'H': // RGB to HSV
      for (auto &img : images)
        cv::cvtColor(img[1], img[1], cv::COLOR_BGR2HSV);
      break;
    case 'G': // RGB to Grayscale
      for (auto &img : images)
        cv::cvtColor(img[1], img[1], cv::COLOR_BGR2GRAY);
      break;
    case 'B': // Grayscale to Binary
      for (auto &img : images)
        cv::threshold(img[1], img[1], 128.0, 255.0, cv::THRESH_BINARY);
      break;
    case 'M': // Meanshift thresholding
      for (auto &img : images)
        cv::pyrMeanShiftFiltering(img[1], img[1], 20, 45, 3);
      break;
    case 'r': // Red detection
      for (auto &img : images)
        cv::inRange(img[1], cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255),
                    img[1]);
      break;
    case 'R': // Red detection
      for (auto &img : images)
        cv::inRange(img[1], cv::Scalar(160, 100, 100),
                    cv::Scalar(179, 255, 255), img[1]);
      break;
    case 't': // thresholding
      for (auto &img : images)
        cv::inRange(
            img[1], 
            cv::Scalar(iLowH, iLowS, iLowV),
            cv::Scalar(iHighH, iHighS, iHighV), img[1]
        );
      break;
    case 'd': // Dilate
      for (auto &img : images) {
        cv::dilate(
            img[1], img[1], cv::getStructuringElement(
                cv::MORPH_ELLIPSE, cv::Size(
                    cv::getTrackbarPos("Strel Size", "Control"),
                    cv::getTrackbarPos("Strel Size", "Control")
                )
            )
        );
      }
      break;
    case 'e': // Erode
      for (auto &img : images) {
        cv::erode(
            img[1], img[1], cv::getStructuringElement(
                cv::MORPH_ELLIPSE, cv::Size(
                    cv::getTrackbarPos("Strel Size", "Control"),
                    cv::getTrackbarPos("Strel Size", "Control")
                )
            )
        );
      }
      break;
    }
  }
  cv::destroyAllWindows();
}
