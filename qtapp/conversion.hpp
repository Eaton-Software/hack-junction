// http://stackoverflow.com/questions/17127762/cvmat-to-qimage-and-back
#ifndef CONVERSION_HPP
#define CONVERSION_HPP
#include <opencv2/imgproc/imgproc.hpp>

QImage Mat2QImage(cv::Mat const& src) {
  cv::Mat temp;  // make the same cv::Mat
  if (src.channels()==3) {
    cv::cvtColor(src, temp,
                 CV_BGR2RGB);  // cvtColor Makes a copt, that what i need
  } else {
    cv::cvtColor(src, temp, CV_GRAY2RGB);
  }
  QImage dest((const uchar*)temp.data, temp.cols, temp.rows, temp.step,
              QImage::Format_RGB888);
  dest.bits();  // enforce deep copy, see documentation
  // of QImage::QImage ( const uchar * data, int width, int height, Format
  // format )
  temp.release();
  return dest;
}

cv::Mat QImage2Mat(QImage const& src) {
  cv::Mat tmp(src.height(), src.width(), CV_8UC3, (uchar*)src.bits(),
              src.bytesPerLine());
  cv::Mat result;  // deep copy just in case (my lack of knowledge with open cv)
  cv::cvtColor(tmp, result, CV_BGR2RGB);
  return result;
}

#endif  // CONVERSION_HPP
