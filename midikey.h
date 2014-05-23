#ifndef MIDIKEY_H
#define MIDIKEY_H

#include <Qt>

class MidiKey
{
public:
    enum MidiType { NoteOn, NoteOff, ControlChange, ProgramChange, PitchBend, Aftertouch, Unknown};

    MidiKey(MidiType type, quint8 code);
    MidiKey();

    quint8 code() const { return _code; }
    MidiType type() const { return _type; }
    bool valid() const { return _isValid; }

private:
    MidiType _type;
    quint8 _code;
    bool _isValid = true;
};

bool operator==(MidiKey a, MidiKey b);
bool operator<(MidiKey a, MidiKey b);

#endif // MIDIKEY_H
