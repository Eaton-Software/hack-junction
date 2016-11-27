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

 private:
  Ui::MainWindow *ui;
  cv::Mat cvimage;
  cv::Mat proc_image(cv::Mat src);
  QTimer *streamTimer;
  bool streaming;
  std::string videoStreamAddress;
};

#endif  // MAINWINDOW_H
