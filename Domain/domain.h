#ifndef DOMAIN_H
#define DOMAIN_H

#include <QString>

#include "midihandler.h"

class Keyboard;
class Domain
{
public:
    enum Type { Integer, Double, Discrete };

public:
    Domain(MidiKey midiKey, QString name, Keyboard* keyboard = 0);
    virtual ~Domain() {}
    virtual Type type() const = 0;
    virtual Domain* copy(Keyboard* keyboard) const = 0;
    virtual quint8 encode() const = 0;
    bool liveUpdate = true;

    QString name() const { return _name; }
    Keyboard* keyboard() const { return _keyboard; }
    MidiKey midiKey() const { return _midiKey; }

private:
    Keyboard* _keyboard;
    MidiKey _midiKey;
    QString _name;


};

#endif // DOMAIN_H
