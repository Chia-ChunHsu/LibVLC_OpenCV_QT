#-------------------------------------------------
#
# Project created by QtCreator 2017-02-07T17:04:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = libvlcOpenCV
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$quote(D:\opencv310_x64_vs2015\include)\
               $$quote(D:\opencv310_x64_vs2015\include\opencv2)\
               $$quote(D:\Program\Lib\vlc-3.0.0-gitN\sdk\include)

OPENCVLIB += $$quote(D:\opencv310_x64_vs2015\x64\vc14\lib)

LIBS+= $$quote(D:\Program\Lib\vlc-3.0.0-gitN\sdk\lib\libvlc.lib)\
       $$quote(D:\Program\Lib\vlc-3.0.0-gitN\sdk\lib\libvlccore.lib)

CONFIG(debug, debug|release){
DEFINES += DEBUGMODE
LIBS+= $$OPENCVLIB/opencv_core310d.lib\
       $$OPENCVLIB/opencv_highgui310d.lib\
       $$OPENCVLIB/opencv_imgcodecs310d.lib\
       $$OPENCVLIB/opencv_imgproc310d.lib\
       $$OPENCVLIB/opencv_videoio310d.lib\
}

CONFIG(release, debug|release){
DEFINES += RELEASEMODE
LIBS+= $$OPENCVLIB/opencv_core310.lib\
       $$OPENCVLIB/opencv_highgui310.lib\
       $$OPENCVLIB/opencv_imgcodecs310.lib\
       $$OPENCVLIB/opencv_imgproc310.lib\
       $$OPENCVLIB/opencv_videoio310.lib\
}

