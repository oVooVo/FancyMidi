#include "keyboard.h"
#include <QDebug>

Keyboard::Keyboard(quint8 channel, QObject *parent) : QObject(parent)
{
    midi = MidiInputHandler::singleton();
}

void Keyboard::setChannel(quint8 channel)
{
    if (channel > 15) {
        qWarning() << "expected channel to be between 0 and 15 but was " << channel;
        channel = 0;
    }
    _channel = channel;
}

void Keyboard::sendMidiControlCommand(quint8 data1, quint8 data2)
{
    midi->sendMidiCommand(MidiInputHandler::ControlChange, channel(), data1, data2);
}
