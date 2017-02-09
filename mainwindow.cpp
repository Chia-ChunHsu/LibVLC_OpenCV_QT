#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    param = new TCallBackParam;
    vlcInstance = libvlc_new(0,NULL);
}

MainWindow::~MainWindow()
{
    if(mp)
        libvlc_media_player_release(mp);
    libvlc_release(vlcInstance);

    delete ui;
    delete param;

}
void *MainWindow::lock(void *op, void **plane)
{
    TCallBackParam *p = (TCallBackParam *)op;
    p->mutex.lock();
    *plane = p->pixels;
    return NULL;
}

void MainWindow::unlock(void *op, void *pic, void *const *plane)
{
    TCallBackParam *p = (TCallBackParam *)op;
    uchar *data = (uchar *)*plane;

    QImage image(data,640,480,QImage::Format_RGB888);
    p->video->setPixmap(QPixmap::fromImage(image).scaled(p->video->size(),Qt::KeepAspectRatio));
    p->mutex.unlock();

    cv::Mat img;// = *p->mat;
    cv::cvtColor(*p->mat,img,CV_RGB2BGR);

    imshow("test", img);
}

void MainWindow::on_openURLButton_clicked()
{

    const char *url = "rtsp://10.11.10.25:554/onvif1";
    media = libvlc_media_new_location(vlcInstance,url);

    if(media == NULL)
    {
        qDebug()<<"Stream can not be connected";
        return;
    }
    mp = libvlc_media_player_new_from_media(media);

    libvlc_media_release(media);

    param->mat  = new cv::Mat( 480, 640, CV_8UC3 );

    param->pixels = (unsigned char *)param->mat->data;
    param->video = ui->video;


    mat = *param->mat;
    imshow("test", mat);

    libvlc_video_set_callbacks(mp,&lock,&unlock,NULL,param);

    const char *chroma ="RV24";
    unsigned width = 640;
    unsigned height = 480;
    unsigned pitch = 640*24/8;

    libvlc_video_set_format(mp,chroma,width,height,pitch);

    libvlc_media_player_play(mp);
}



