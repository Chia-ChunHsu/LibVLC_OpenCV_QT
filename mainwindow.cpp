#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    record = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openURLButton_clicked()
{

    QString urlString = QInputDialog::getText(this, tr("Open Url"), tr("Enter the URL you want to play"));
    const char *url;

    if(!urlString.isEmpty())
    {
        QByteArray byteArray = urlString.toLatin1();
        url = byteArray.data();
    }
    else
        url = "rtsp://10.11.10.63:554/onvif1";//"rtsp://172.20.10.4:554/onvif1";//"rtsp://10.11.10.25:554/onvif1";
    vlCV = new VlcOpenCV(url);

    connect(vlCV,SIGNAL(sendMat(cv::Mat)),this,SLOT(ShowMat(cv::Mat)));
    vlCV->Start();
    vlCV->start();
}

void MainWindow::ShowMat(cv::Mat mat)
{
    cv::imshow("test",mat);
    if(record == true)
    {
        writer.write(mat);
    }
}

void MainWindow::on_recordButton_clicked()
{
    if(record == true)
    {
        record = false;
        writer.release();
    }
    else
    {
        record = true;
        QDateTime dt = QDateTime::currentDateTime();
        QString fileName = "video"+dt.toString("yyyy-MM-dd-hhmmss")+".avi";
        writer.open(fileName.toStdString(),CV_FOURCC('M','J','P','G'),20,cv::Size(640,480));
    }
}
