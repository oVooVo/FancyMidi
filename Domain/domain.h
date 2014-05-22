#ifndef DOMAIN_H
#define DOMAIN_H

#include <QString>

class Keyboard;
class Domain
{
public:
    enum Type { Integer, Double, Discrete };

public:
    Domain(quint8 midicode, QString name, Keyboard* keyboard = 0);
    virtual ~Domain() {}
    virtual Type type() const = 0;
    virtual Domain* copy(Keyboard* keyboard) const = 0;
    virtual quint8 encode() const = 0;
    bool liveUpdate = true;

    QString name() const { return _name; }
    Keyboard* keyboard() const { return _keyboard; }
    quint8 midicode() const { return _midicode; }

private:
    Keyboard* _keyboard;
    quint8 _midicode;
    QString _name;


};

#endif // DOMAIN_H
