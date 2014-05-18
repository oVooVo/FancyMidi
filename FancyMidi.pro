#-------------------------------------------------
#
# Project created by QtCreator 2014-05-11T17:11:48
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FancyMidi
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x


SOURCES += main.cpp\
    midiinputhandler.cpp \
    keyboard.cpp \
    nordstage2.cpp \
    nordstage2_organ.cpp \
    nordstage2_effects.cpp \
    nordstage2_piano.cpp \
    nordstage2_synth.cpp \
    nordstage2_special_effects.cpp

HEADERS  +=  midiinputhandler.h \
    keyboard.h \
    nordstage2.h

