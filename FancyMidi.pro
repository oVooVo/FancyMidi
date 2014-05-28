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
    keyboard.cpp \
    nordstage2.cpp \
    Domain/domain.cpp \
    Domain/discretedomain.cpp \
    Domain/integerdomain.cpp \
    Domain/doubledomain.cpp \
    Domain/domains.cpp \
    mainwindow.cpp \
    Model/Nodes/node.cpp \
    Model/port.cpp \
    Model/inputport.cpp \
    Model/outputport.cpp \
    Model/graphscene.cpp \
    Model/packet.cpp \
    View/graphview.cpp \
    View/nodeitem.cpp \
    Model/abstractgraphscene.cpp \
    Settings/setting.cpp \
    SettingWidgets/settingwidget.cpp \
    View/temporaryconnection.cpp \
    View/connectionitem.cpp \
    View/portitem.cpp \
    Model/project.cpp \
    Settings/selectsetting.cpp \
    SettingWidgets/selectsettingwidget.cpp \
    Settings/midicommandselectsetting.cpp \
    SettingWidgets/midicommandselectsettingwidget.cpp \
    Settings/integersetting.cpp \
    SettingWidgets/integersettingwidget.cpp \
    View/nodetree.cpp \
    Settings/doublesetting.cpp \
    SettingWidgets/doublesettingwidget.cpp \
    Model/Nodes/nordstage2input.cpp \
    SettingWidgets/midifiltersettingwidget.cpp \
    Settings/midifiltersetting.cpp \
    midihandler.cpp \
    midikey.cpp \
    Model/Nodes/nordstage2controlout.cpp \
    Model/Nodes/nordstage2noteout.cpp \
    Model/Nodes/midichannelnode.cpp \
    Model/Nodes/enableablenode.cpp \
    Settings/boolsetting.cpp \
    SettingWidgets/boolsettingwidget.cpp \
    Settings/scalarsetting.cpp \
    Model/Nodes/delaynode.cpp \
    Model/Nodes/mathnode.cpp \
    Model/Nodes/nordstage2noteinput.cpp \
    Model/Nodes/timernode.cpp \
    Model/Nodes/pitchbendinput.cpp \
    Model/Nodes/tointegernode.cpp \
    Model/Nodes/pitchbendoutput.cpp \
    Model/Nodes/memorymapnode.cpp \
    Model/Nodes/memorynode.cpp \
    Model/Nodes/conditionnode.cpp \
    logger.cpp \
    Model/minimapgraphscene.cpp \
    View/minimapview.cpp \
    View/nodewidget.cpp \
    View/graphicsproxywidget.cpp \
    numbered.cpp \
    Settings/sequencesetting.cpp \
    Model/Nodes/sequencenode.cpp \
    SettingWidgets/sequencesettingwidget.cpp \
    Model/Nodes/switch.cpp

HEADERS  +=  \
    keyboard.h \
    nordstage2.h \
    domain.h \
    Domain/discretedomain.h \
    Domain/continousdomain.h \
    Domain/integerdomain.h \
    Domain/doubledomain.h \
    Domain/domains.h \
    mainwindow.h \
    Model/Nodes/node.h \
    Model/port.h \
    Model/inputport.h \
    Model/outputport.h \
    Model/graphscene.h \
    Model/packet.h \
    View/graphview.h \
    View/nodeitem.h \
    Model/abstractgraphscene.h \
    Settings/setting.h \
    SettingWidgets/settingwidget.h \
    View/temporaryconnection.h \
    View/connectionitem.h \
    View/portitem.h \
    View/queueinputport.h \
    Model/project.h \
    Settings/selectsetting.h \
    SettingWidgets/selectsettingwidget.h \
    Settings/midicommandselectsetting.h \
    SettingWidgets/midicommandselectsettingwidget.h \
    Settings/integersetting.h \
    SettingWidgets/integersettingwidget.h \
    View/nodetree.h \
    Settings/doublesetting.h \
    SettingWidgets/doublesettingwidget.h \
    Model/Nodes/nordstage2input.h \
    Settings/midifiltersetting.h \
    SettingWidgets/midifiltersettingwidget.h \
    midihandler.h \
    midikey.h \
    Model/Nodes/nordstage2controlout.h \
    Model/Nodes/nordstage2noteout.h \
    Model/Nodes/midichannelnode.h \
    Model/Nodes/enableablenode.h \
    Settings/boolsetting.h \
    SettingWidgets/boolsettingwidget.h \
    Settings/scalarsetting.h \
    Model/Nodes/delaynode.h \
    Model/Nodes/mathnode.h \
    Model/Nodes/nordstage2noteinput.h \
    Model/Nodes/timernode.h \
    Model/Nodes/pitchbendinput.h \
    Model/Nodes/tointegernode.h \
    Model/Nodes/pitchbendoutput.h \
    Model/Nodes/memorymapnode.h \
    Model/Nodes/memorynode.h \
    Model/Nodes/conditionnode.h \
    logger.h \
    Model/minimapgraphscene.h \
    View/minimapview.h \
    View/nodewidget.h \
    View/graphicsproxywidget.h \
    numbered.h \
    Settings/sequencesetting.h \
    Model/Nodes/sequencenode.h \
    SettingWidgets/sequencesettingwidget.h \
    Model/Nodes/switch.h

FORMS += \
    mainwindow.ui \
    SettingWidgets/selectsettingwidget.ui \
    SettingWidgets/midicommandselectsettingwidget.ui \
    SettingWidgets/integersettingwidget.ui \
    SettingWidgets/doublesettingwidget.ui \
    SettingWidgets/midifiltersettingwidget.ui \
    SettingWidgets/boolsettingwidget.ui \



