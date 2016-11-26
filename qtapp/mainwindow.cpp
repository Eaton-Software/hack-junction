#include "mainwindow.h"
#include <cpr/cpr.h>
#include <QFileDialog>
#include <QString>
#include <QTimer>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <thread>
#include "conversion.hpp"
#include "ui_mainwindow.h"

using byte = unsigned char;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      streamTimer(new QTimer(this)) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_2_clicked() {
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Open Image"), QDir::home().absolutePath(), tr("*.png *.jpg"),
      Q_NULLPTR, QFileDialog::Options(QFileDialog::DontUseNativeDialog));
  if (fileName.isNull()) return;
  cvimage = cv::imread(fileName.toStdString(), CV_LOAD_IMAGE_COLOR);
  cv::Mat greyed;
  cv::cvtColor(cvimage, greyed, CV_BGR2GRAY);
  QImage qim1 = Mat2QImage(cvimage);
  auto picbox = ui->picbox;
  picbox->setScaledContents(true);
  picbox->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  picbox->setPixmap(QPixmap::fromImage(qim1));
}

void MainWindow::on_pushButton_clicked() {
  if (cvimage.empty()) return;
}

void MainWindow::update_picbox() {
  auto picbox = ui->picbox;
  const std::string videoStreamAddress =
      "http://85.188.8.43:8000/thermaldata_stream.png";
  auto r = cpr::Get(cpr::Url{videoStreamAddress});
  if (r.status_code != 200) return;
  auto bstring = r.text;
  if (bstring.empty()) return;
  std::vector<byte> vectordata{bstring.begin(), bstring.end()};
  cv::Mat data_mat(vectordata, true);
  cv::Mat image(cv::imdecode(data_mat, cv::IMREAD_GRAYSCALE));
  cv::Mat processed;
  processed = proc_image(image);
  QImage qim1 = QImage((uchar *)processed.data, processed.cols, processed.rows, processed.step,
                       QImage::Format_Grayscale8);
  picbox->setScaledContents(true);
  picbox->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  picbox->setPixmap(QPixmap::fromImage(qim1));
  picbox->update();
}

cv::Mat MainWindow::proc_image(cv::Mat src) {
  cv::Mat gray_cont, bin, dst;

  src.convertTo(gray_cont, -1, 2, 1);
  cv::threshold(gray_cont, bin, 128, 255, 3);
  cv::medianBlur(bin, dst, 3);
  return dst;
}

void MainWindow::on_checkBox_4_toggled(bool checked) {
  if (checked) {
    connect(streamTimer, SIGNAL(timeout()), this, SLOT(update_picbox()));
    streamTimer->start(40);
  } else {
    streamTimer->stop();
  }
}
