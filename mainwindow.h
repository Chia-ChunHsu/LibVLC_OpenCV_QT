#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QLabel>
#include <QInputDialog>
#include <QPixmap>
#include <QMetaType>
#include <QObject>
#include <vlcopencv.h>
#include <opencv.hpp>
#include <highgui.hpp>
#include <QDateTime>
#include <QCameraInfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_openURLButton_clicked();

    void ShowMat(cv::Mat mat);

    void on_recordButton_clicked();

private:
    Ui::MainWindow *ui;
    VlcOpenCV *vlCV;
    bool record;
    cv::VideoCapture cap;
    cv::VideoWriter writer;
};
Q_DECLARE_METATYPE(cv::Mat)

#endif // MAINWINDOW_H
