#include "vlcopencv.h"

void *lock(void *op, void **plane)
{
    TCallBackParam *p = (TCallBackParam *)op;
    p->mutex.lock();
    *plane = p->pixels;
    return NULL;
}

void unlock(void *op, void *pic, void * const *plane)
{
    TCallBackParam *p = (TCallBackParam *)op;
    p->mutex.unlock();
}

void VlcOpenCV::run()
{
    while(1)
    {
        cv::Mat temp,img;
        param->mutex.lock();
        param->mat->copyTo(temp);
        param->mutex.unlock();
        cv::cvtColor(temp,img,CV_RGB2BGR);
        emit sendMat(img);
    }
}
VlcOpenCV::VlcOpenCV()
{

}

VlcOpenCV::VlcOpenCV(const char *url)
{
    this->url = url;
    param = new TCallBackParam;
    vlcInstance = libvlc_new(0,NULL);

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

    mat = *param->mat;
    //imshow("test", mat);

    libvlc_video_set_callbacks(mp,&lock,&unlock,NULL,param);

    const char *chroma ="RV24";
    unsigned width = 640;
    unsigned height = 480;
    unsigned pitch = 640*24/8;

    libvlc_video_set_format(mp,chroma,width,height,pitch);
}

VlcOpenCV::~VlcOpenCV()
{
    if(mp)
        libvlc_media_player_release(mp);
    libvlc_release(vlcInstance);
    delete param;
}

void VlcOpenCV::Start()
{
    libvlc_media_player_play(mp);
}

void VlcOpenCV::Stop()
{

}


