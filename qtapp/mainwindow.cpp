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
    : QMainWindow(parent), ui(new Ui::MainWindow) {
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
  QImage qim1 = QImage((uchar *)image.data, image.cols, image.rows, image.step,
                       QImage::Format_Grayscale8);
  picbox->setScaledContents(true);
  picbox->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  picbox->setPixmap(QPixmap::fromImage(qim1));
  picbox->update();
}

void MainWindow::on_pushButton_4_clicked() {
  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update_picbox()));
  timer->start(40);
}
