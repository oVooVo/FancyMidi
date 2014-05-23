#include "midikey.h"

MidiKey::MidiKey()
{
    _isValid = false;
}

MidiKey::MidiKey(MidiType type, quint8 code)
{
    _type = type;
    _code = code;
}


bool operator ==(MidiKey a, MidiKey b)
{
    return a.type() == b.type() && a.code() == b.code();
}

bool operator <(MidiKey a, MidiKey b)
{
    if (a.type() == b.type())
        return a.code() < b.code();
    return a.type() < b.type();
}
