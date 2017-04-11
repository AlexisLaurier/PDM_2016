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
    terrain.cpp \
    myopengl.cpp

HEADERS  += mainwindow.h \
    terrain.h \
    myopengl.h

FORMS    += mainwindow.ui
LIBS += -lopengl32 -lglu32
