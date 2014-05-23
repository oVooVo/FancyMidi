#include "domain.h"
#include <QObject>
#include "discretedomain.h"



//TODO Piano dynamic is now integer domain from Dynamic0 to Dynamic3

Domain::Domain(MidiKey midiKey, QString name, Keyboard *keyboard)
{
    _keyboard = keyboard;
    _name = name;
    _midiKey = midiKey;
}
