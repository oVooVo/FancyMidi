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
    Domain/domain.cpp \
    Domain/discretedomain.cpp \
    Domain/integerdomain.cpp \
    Domain/doubledomain.cpp \
    Domain/domains.cpp

HEADERS  +=  midiinputhandler.h \
    keyboard.h \
    nordstage2.h \
    domain.h \
    Domain/discretedomain.h \
    Domain/continousdomain.h \
    Domain/integerdomain.h \
    Domain/doubledomain.h \
    Domain/domains.h

