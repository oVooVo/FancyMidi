#include <QApplication>
#include <QFile>
#include <QDebug>
#include "midiinputhandler.h"
#include "nordstage2.h"
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NordStage2* s2 = new NordStage2();
    Q_UNUSED(s2);

    MidiInputHandler::singleton()->sendMidiControlCommand(0, 99, 0);
    s2->setOrganEnabled(NordStage2::On);
    s2->sineWaveDrawbar(2, 2, 10);


    return a.exec();
}
