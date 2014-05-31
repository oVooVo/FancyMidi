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
#ifdef VERBOSE
        qWarning() << "expected channel to be between 0 and" << NUM_MIDI_CHANNELS - 1 << "but was " << channel;
#endif
        channel = 0;
    }
    _channel = channel;
}

void Keyboard::sendMidiCommand(MidiKey key, quint8 data)
{
    MidiHandler::singleton()->sendMidiCommand(key, channel(), data);
}

void Keyboard::allNotesOff(int channel)
{
    for (int c = 0; c < NUM_MIDI_CHANNELS; c++) {
        if (channel < 0 || channel == c) {
            for (int note = 0; note < 127; note++) {
                MidiHandler::singleton()->sendMidiCommand(MidiKey(MidiKey::NoteOff, note), c, 127);
            }
        }
    }
}

