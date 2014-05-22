#ifndef DISCRETEDOMAIN_H
#define DISCRETEDOMAIN_H

#include "domain.h"
#include <QList>
#include <QString>
#include <QStringList>

class DiscreteDomain : public Domain
{
public:
    DiscreteDomain(quint8 midicode, QString name, QStringList values, Keyboard* keyboard = 0);
    QStringList values() const { return _values; }
    Type type() const { return Discrete; }

    bool setIndex(int index);
    int index() const { return _index; }

    quint8 encode() const { bool unused; return toCode(_index, unused); }
    bool setCode(quint8 code);

    Domain* copy(Keyboard* keyboard) const;

private:
    int _index = 0;
    QStringList _values;


    int toIndex(quint8 code, bool &ok) const;
    quint8 toCode(int index, bool &ok) const;

};

#endif // DISCRETEDOMAIN_H
