#include "midiinputhandler.h"
#include <QIODevice>
#include <QDebug>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <QTimer>

MidiInputHandler* MidiInputHandler::_singleton = 0;

MidiInputHandler::MidiInputHandler()
{
    connectMidiDevice_Private();
}

bool MidiInputHandler::connectMidiDevice_Private()
{
    if (_phantom) return true;

    if (_notifier) delete _notifier;

    int fd = -1;

    auto openfailed = [&fd] (const char* filename) {
        fd = open(filename, O_NONBLOCK | O_RDWR);
        if (fd <= 0) return true;
        else return false;
    };
    if (openfailed("/dev/midi0") && openfailed("/dev/midi1")) {
        qDebug() << "Cannot find midi-device. Make sure this device is not used by any other program.";
        return false;
    }

    _notifier = new QSocketNotifier(fd, QSocketNotifier::Read, this);
    _notifier->setEnabled(true);
    connect(_notifier, SIGNAL(activated(int)), this, SLOT(readyRead()));
    _valid = true;
    return true;
}

bool MidiInputHandler::disconnectMidiDevice_Private()
{
    if (_phantom) return true;
    if (_notifier) {
        close(_notifier->socket());
        delete _notifier;
        _notifier = 0;
        return true;
    } else {
        return false;
    }
}

void MidiInputHandler::readyRead()
{
    if (_phantom) return;
    quint8 buffer[3] = {0,0,0};
    read(_notifier->socket(), &buffer, 3);
    if (_verbose) {
        qDebug() << "== RECV ==========";
        qDebug() << "type = " << getType(buffer[0]) << "(" << typeToString(getType(buffer[0])) << ")";
        qDebug() << "channel = " << getChannel(buffer[0]);
        qDebug() << "data1 = " << buffer[1];
        qDebug() << "data2 = " << buffer[2];
        qDebug() << "==================";
    }
    if (buffer[0] & 0x80)
        emit receivedMidiCommand(getType(buffer[0]), getChannel(buffer[0]), buffer[1], buffer[2]);
    else {
        qWarning() << "synchronization lost. disconnected device.";
        disconnectMidiDevice_Private();
    }
}

    // data1 = xxxx xxxx
    //         |\ / \ /
    //         | |   +-- channel
    //         | |
    //         | +-- type
    //         +-- always 1 (control byte)

MidiInputHandler::MidiType MidiInputHandler::getType(quint8 code)
{
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

quint8 MidiInputHandler::statusByte(MidiInputHandler::MidiType type, quint8 channel)
{
    quint8 code;
    switch (type) {
    case NoteOff:
        code = 0x00;
        break;
    case NoteOn:
        code = 0x10;
        break;
    case ControlChange:
        code = 0x30;
        break;
    case ProgramChange:
        code = 0x40;
        break;
    case Aftertouch:
        code = 0x50;
        break;
    case PitchBend:
        code = 0x60;
        break;
    case Unknown:
    default:
        code = 0x70;
    }
    code |= channel;
    code |= 0x80;
    return code;
}

const MidiInputHandler* MidiInputHandler::singleton()
{
    if (!_singleton) _singleton = new MidiInputHandler();
    return _singleton;
}

void MidiInputHandler::sendMidiCommand(MidiType type, quint8 channel, quint8 data1, quint8 data2) const
{
    if (_valid || _phantom) {
        quint8 buffer[3] = { statusByte(type, channel), data1, data2 };
        if (!_phantom)
            write(_notifier->socket(), &buffer, 3);
        if (_verbose) {
            qDebug() << "== SEND ==========";
            qDebug() << "type = " << getType(buffer[0]) << "(" << typeToString(getType(buffer[0])) << ")";
            qDebug() << "channel = " << getChannel(buffer[0]);
            qDebug() << "data1 = " << buffer[1];
            qDebug() << "data2 = " << buffer[2];
            qDebug() << "==================";
        }
    } else {
        qWarning() << "cannot send data to unconnected midi device.";
    }
}

void MidiInputHandler::sendMidiControlCommand(quint8 channel, quint8 data1, quint8 data2) const
{
    sendMidiCommand(ControlChange, channel, data1, data2);
}

QString MidiInputHandler::typeToString(MidiType type)
{
    switch(type) {
    case NoteOff:
        return "note off";
    case NoteOn:
        return "note on";
    case ControlChange:
        return "control change";
    case ProgramChange:
        return "program change";
    case Aftertouch:
        return "aftertouch";
    case PitchBend:
        return "pitch bend";
    case Unknown:
    default:
        return "unkown";
    }
}
