#include "midiinputhandler.h"
#include <QIODevice>
#include <QDebug>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

MidiInputHandler* MidiInputHandler::_singleton = 0;

MidiInputHandler::MidiInputHandler()
{
    int fd = -1;

    auto openfailed = [&fd] (const char* filename) {
        fd = open(filename, O_NONBLOCK);
        if (fd <= 0) return true;
        else return false;
    };
    if (openfailed("/dev/midi0") && openfailed("/dev/midi1")) {
        qDebug() << "Cannot find midi-device. Make sure this device is not used by any other program.";
        return;
    }

    _notifier = new QSocketNotifier(fd, QSocketNotifier::Read, this);
    _notifier->setEnabled(true);
    connect(_notifier, SIGNAL(activated(int)), this, SLOT(readyRead()));
    _valid = true;
}

void MidiInputHandler::readyRead()
{
    char buffer[3] = {0,0,0};
    read(_notifier->socket(), &buffer, 3);
    emit receivedMidiCommand(getType(buffer[0]), getChannel(buffer[0]), buffer[1], buffer[2]);
}

MidiInputHandler::MidiType MidiInputHandler::getType(quint8 code)
{

    // data1 = xxxx xxxx
    //         |\ / \ /
    //         | |   +-- channel
    //         | |
    //         | +-- type
    //         +-- always 1 (control byte)

    switch ((code & 0x70) >> 4) {
    case 0:
        return NoteOff;
    case 1:
        return NoteOn;
    case 3:
        return ControlChange;
    case 4:
        return ProgramChange;
    case 5:
        return Aftertouch;
    case 6:
        return PitchBend;
    }
    return Unknown;
}

quint8 MidiInputHandler::getChannel(quint8 code)
{
    return code & 0x0F;
}

const MidiInputHandler* MidiInputHandler::singleton()
{
    if (!_singleton) _singleton = new MidiInputHandler();
    return _singleton;
}
