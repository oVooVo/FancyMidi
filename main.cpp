#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QDebug>
#include "midiinputhandler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QObject::connect(MidiInputHandler::singleton(),
                     &MidiInputHandler::receivedMidiCommand,
                     [](MidiInputHandler::MidiType type, quint8 channel, quint8 data1, quint8 data2) {
       qDebug() << "type = " << type;
       qDebug() << "channel = " << channel;
       qDebug() << "data1 = " << data1;
       qDebug() << "data2 = " << data2;
       qDebug() << "==================";
    });

    return a.exec();
}
