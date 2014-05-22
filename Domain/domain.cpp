#include "domain.h"
#include <QObject>
#include "discretedomain.h"



//TODO Piano dynamic is now integer domain from Dynamic0 to Dynamic3

Domain::Domain(quint8 midicode, QString name, Keyboard *keyboard)
{
    _keyboard = keyboard;
    _name = name;
    _midicode = midicode;
}
