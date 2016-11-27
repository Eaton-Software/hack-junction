#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <opencv2/core/core.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

 private slots:
  void on_loadLocal_clicked();

  void update_picbox();

  void on_stream_toggled(bool checked);

  void on_applyURL_clicked();

  void on_thresholdSlider_valueChanged(int value);

  void on_blurSlider_valueChanged(int value);

  void on_contrastSlider_valueChanged(int value);

  void on_resetImage_clicked();

 private:
  Ui::MainWindow *ui;
  cv::Mat cvimage;
  cv::Mat original;
  QImage qim;
  QTimer *streamTimer;
  bool streaming;
  std::string videoStreamAddress;
  cv::Mat proc_image(cv::Mat src);
  void loadQim();
};

#endif  // MAINWINDOW_H
