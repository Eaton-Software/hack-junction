#include "mainwindow.h"
#include <QFileDialog>
#include <cstdlib>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "conversion.hpp"
#include "expandpath.hpp"
#include "ui_mainwindow.h"

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
