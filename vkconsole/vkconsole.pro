#-------------------------------------------------
#
# Project created by QtCreator 2014-10-18T23:50:28
#
#-------------------------------------------------

QT       += core network
QT       -= gui

TARGET = vkconsole

SOURCES += main.cpp\
        vk.cpp

HEADERS  += vk.h

QMAKE_INCDIR += /usr/include/jsoncpp/
QMAKE_LIBS += -ljsoncpp
QMAKE_CXXFLAGS += -std=c++11
