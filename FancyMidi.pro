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
    Domain/domains.cpp \
    mainwindow.cpp \
    Model/node.cpp \
    Model/port.cpp \
    Model/inputport.cpp \
    Model/outputport.cpp \
    Model/graphscene.cpp \
    Model/packet.cpp \
    View/graphview.cpp \
    View/nodeitem.cpp \
    Model/abstractgraphscene.cpp \
    Model/output.cpp \
    Model/queuednode.cpp \
    Settings/setting.cpp \
    SettingWidgets/settingwidget.cpp \
    View/temporaryconnection.cpp \
    View/connectionitem.cpp \
    View/portitem.cpp \
    Model/queueinputport.cpp \
    Model/project.cpp \
    Model/Nodes/keyboardnode.cpp \
    Model/simpleinputport.cpp

HEADERS  +=  midiinputhandler.h \
    keyboard.h \
    nordstage2.h \
    domain.h \
    Domain/discretedomain.h \
    Domain/continousdomain.h \
    Domain/integerdomain.h \
    Domain/doubledomain.h \
    Domain/domains.h \
    mainwindow.h \
    Model/node.h \
    Model/port.h \
    Model/inputport.h \
    Model/outputport.h \
    Model/graphscene.h \
    Model/packet.h \
    View/graphview.h \
    View/nodeitem.h \
    Model/abstractgraphscene.h \
    Model/output.h \
    Model/queuednode.h \
    Settings/setting.h \
    SettingWidgets/settingwidget.h \
    View/temporaryconnection.h \
    View/connectionitem.h \
    View/portitem.h \
    View/queueinputport.h \
    Model/project.h \
    Model/Nodes/keyboardnode.h \
    Model/simpleinputport.h

FORMS += \
    mainwindow.ui

