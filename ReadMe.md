
## Setting Requirement
This Project is built on the **Qt 5.7 + OpenCV 3.1 + MSVC 2015 x64**
Before you using this project, make sure you has already installed the VLC library.
I use the version **vlc-3.0.0 20170207** from the [VLC media player Win64 nightly builds](https://nightlies.videolan.org/build/win64/), it supports the 64 bit **Nightly** version.
You can try to using the latest version of VLC Library

## How to Use
You can copy the vlcopencv.cpp and vlocopencv.h into your project, and Remember to qmake it before you include or use it.
**_This VlcOpenCV class is based on Qt, so it can not be used without Qt._**
This Class is a QObject Type class, and inherited from QThread.
You can input the url of your streaming video, and you can get the returning image by using **cv::Mat frame()** function or using Signals and Slots to connect the signals of **sendMat(cv::Mat mat)**;
