#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
        url = "rtsp://10.11.10.25:554/onvif1";
    vlCV = new VlcOpenCV(url);

    connect(vlCV,SIGNAL(sendMat(cv::Mat)),this,SLOT(ShowMat(cv::Mat)));
    vlCV->Start();
    vlCV->start();
}

void MainWindow::ShowMat(cv::Mat mat)
{
    cv::imshow("test",mat);
}



