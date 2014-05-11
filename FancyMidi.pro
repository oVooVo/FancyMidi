#-------------------------------------------------
#
# Project created by QtCreator 2014-05-11T17:11:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FancyMidi
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x


SOURCES += main.cpp\
    midiinputhandler.cpp

HEADERS  +=  midiinputhandler.h

FORMS    += mainwindow.ui
