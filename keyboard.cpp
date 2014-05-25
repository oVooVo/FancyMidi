#include "keyboard.h"
#include <QDebug>

Keyboard::Keyboard(quint8 channel, QObject *parent) : QObject(parent)
{
    setChannel(channel);
    midi = MidiHandler::singleton();
}

void Keyboard::setChannel(quint8 channel)
{
    if (channel >= NUM_MIDI_CHANNELS) {
        qWarning() << "expected channel to be between 0 and" << NUM_MIDI_CHANNELS - 1 << "but was " << channel;
        channel = 0;
    }
    _channel = channel;
}

void Keyboard::sendMidiCommand(MidiKey key, quint8 data)
{
    MidiHandler::singleton()->sendMidiCommand(key, channel(), data);
}

