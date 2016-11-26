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
  void on_pushButton_2_clicked();

  void on_pushButton_clicked();

  void update_picbox();

  void on_checkBox_4_toggled(bool checked);

 private:
  Ui::MainWindow *ui;
  cv::Mat cvimage;
  QTimer *streamTimer;
};

#endif  // MAINWINDOW_H
