#-------------------------------------------------
#
# Project created by QtCreator 2014-10-18T23:50:28
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mes
TEMPLATE = app


SOURCES += main.cpp\
        vk.cpp

HEADERS  += vk.h

FORMS    += vk.ui

QMAKE_INCDIR += /usr/include/c++/6.1.1/x86_64-pc-linux-gnu

QMAKE_LIBS += -ljsoncpp
