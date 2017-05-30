#-------------------------------------------------
#
# Project created by QtCreator 2017-04-11T13:47:47
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PDM_2016
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myopengl.cpp \
    webcam.cpp

HEADERS  += mainwindow.h \
    myopengl.h \
    webcam.h

FORMS    += mainwindow.ui
LIBS += -lopengl32 \
    -lglu32 \
    -L$$(OPENCV_DIR)\lib \
    -lopencv_core2413 \
    -lopencv_highgui2413 \
    -lopencv_imgproc2413 \
    -lopencv_video2413 \
    -lopencv_features2d2413 \
    -lopencv_calib3d2413

INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include

RESOURCES += \
    ressources.qrc
