#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QLabel>
#include <QInputDialog>
#include <QPixmap>
#include <QMutex>
#include <QMutexLocker>
#include <QTimer>
#include <vlc/vlc.h>
#include <opencv.hpp>
#include <highgui.hpp>


//typedef struct TCallbackParam
//{
//    QMutex mutex;
//    QLabel *video;
//    uchar *pixels;
//    cv::Mat* mat;
//}TCallbackParam;

class TCallBackParam
{
public:
    TCallBackParam(){}
    QMutex mutex;
    QLabel *video;
    uchar *pixels;
    cv::Mat* mat;
};


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

private:
    cv::Mat mat;
    Ui::MainWindow *ui;
    TCallBackParam* param;
    libvlc_instance_t *vlcInstance;
    libvlc_media_player_t *mp = 0;
    libvlc_media_t *media;

    static void *lock(void *op, void **plane);
    static void unlock(void *op, void *pic, void *const *plane);
};


#endif // MAINWINDOW_H
