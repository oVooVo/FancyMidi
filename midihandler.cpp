#include "midihandler.h"
#include <QIODevice>
#include <QDebug>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <QTimer>
#include "logger.h"

//#define PHANTOM       // does not really sends midi commands thus no need for connection to midi device.

MidiHandler* MidiHandler::_singleton = 0;

MidiHandler::MidiHandler()
{
    connectMidiDevice_Private();
}

bool MidiHandler::connectMidiDevice_Private()
{
#ifdef PHANTOM
    return true;
#endif

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

bool MidiHandler::disconnectMidiDevice_Private()
{
#ifdef PHNATOM
    return true;
#endif
    if (_notifier) {
        close(_notifier->socket());
        delete _notifier;
        _notifier = 0;
        _valid = false;
        return true;
    } else {
        return false;
    }
}

void MidiHandler::readyRead()
{
#ifdef PHNATOM
    return;
#endif

    quint8 buffer[3] = {0,0,0};
    read(_notifier->socket(), &buffer, 3);

    Logger::log(  QString("== RECV ==========\n"    \
                          "type = %1 (%2)\n"        \
                          "channel = %3\n"          \
                          "data1 = %4\n"            \
                          "data2 = %5\n"            \
                          "==================\n")
            .arg(getType(buffer[0])).arg(typeToString(getType(buffer[0])))
            .arg(getChannel(buffer[0])).arg(buffer[1]).arg(buffer[2])
            );
    if (buffer[0] & 0x80)
        emit receivedMidiCommand(MidiKey(getType(buffer[0]), buffer[1]), getChannel(buffer[0]), buffer[2]);
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

MidiKey::MidiType MidiHandler::getType(quint8 code)
{
    switch ((code & 0x70) >> 4) {
    case 0:
        return MidiKey::NoteOff;
    case 1:
        return MidiKey::NoteOn;
    case 3:
        return MidiKey::ControlChange;
    case 4:
        return MidiKey::ProgramChange;
    case 5:
        return MidiKey::Aftertouch;
    case 6:
        return MidiKey::PitchBend;
    }
    return MidiKey::Unknown;
}

int MidiHandler::getChannel(quint8 code)
{
    return code & 0x0F;
}

quint8 MidiHandler::statusByte(MidiKey::MidiType type, quint8 channel)
{
    quint8 code;
    switch (type) {
    case MidiKey::NoteOff:
        code = 0x00;
        break;
    case MidiKey::NoteOn:
        code = 0x10;
        break;
    case MidiKey::ControlChange:
        code = 0x30;
        break;
    case MidiKey::ProgramChange:
        code = 0x40;
        break;
    case MidiKey::Aftertouch:
        code = 0x50;
        break;
    case MidiKey::PitchBend:
        code = 0x60;
        break;
    case MidiKey::Unknown:
    default:
        code = 0x70;
    }
    code |= channel;
    code |= 0x80;
    return code;
}

const MidiHandler* MidiHandler::singleton()
{
    if (!_singleton) _singleton = new MidiHandler();
    return _singleton;
}

void MidiHandler::sendMidiCommand(MidiKey key, quint8 channel, quint8 data2) const
{
#ifdef PHANTOM
    if (true) {
#else
    if (_valid) {
#endif
        quint8 buffer[3] = { statusByte(key.type(), channel), key.code(), data2 };
#ifndef PHANTOM
            write(_notifier->socket(), &buffer, 3);
#endif
    Logger::log(  QString("== SEND ==========\n"    \
                          "type = %1 (%2)\n"        \
                          "channel = %3\n"          \
                          "data1 = %4\n"            \
                          "data2 = %5\n"            \
                          "==================\n")
            .arg(getType(buffer[0])).arg(typeToString(getType(buffer[0])))
            .arg(getChannel(buffer[0])).arg(buffer[1]).arg(buffer[2])
            );
    } else {
        qWarning() << "cannot send data to unconnected midi device.";
    }
}

QString MidiHandler::typeToString(MidiKey::MidiType type)
{
    switch(type) {
    case MidiKey::NoteOff:
        return "note off";
    case MidiKey::NoteOn:
        return "note on";
    case MidiKey::ControlChange:
        return "control change";
    case MidiKey::ProgramChange:
        return "program change";
    case MidiKey::Aftertouch:
        return "aftertouch";
    case MidiKey::PitchBend:
        return "pitch bend";
    case MidiKey::Unknown:
    default:
        return "unkown";
    }
}
