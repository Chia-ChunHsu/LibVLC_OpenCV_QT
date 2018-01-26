#ifndef VLCOPENCV_H
#define VLCOPENCV_H
#include <QDebug>
#include <QMetaType>
#include <QMutex>
#include <QMutexLocker>
#include <QObject>
#include <vlc/vlc.h>
#include <opencv.hpp>
#include <highgui.hpp>
#include <QThread>

class TCallBackParam
{
public:
    TCallBackParam(){}
    QMutex mutex;
    uchar *pixels;
    //VlcOpenCV *vlc;
    cv::Mat* mat;
};

class VlcOpenCV: public QThread
{
    Q_OBJECT
protected:
    void run();
public:
    VlcOpenCV();
    VlcOpenCV(const char *url);
    ~VlcOpenCV();
    void Start();
    void Stop();
    cv::Mat frame(){ return mat;}
    QMutex mutex;
    uchar *pixels;
    cv::Mat* _mat;

signals:
    void sendMat(cv::Mat);

private:
    TCallBackParam* param;
    libvlc_instance_t *vlcInstance;
    libvlc_media_player_t *mp = 0;
    libvlc_media_t *media;


    cv::Mat mat;
    const char *url;
};

#endif // VLCOPENCV_H
