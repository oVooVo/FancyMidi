#include "discretedomain.h"
#include <QDebug>

DiscreteDomain::DiscreteDomain(quint8 midicode, QString name, QStringList values, Keyboard* keyboard)
    : Domain(midicode, name, keyboard)
{
    _values = values;
}

quint8 DiscreteDomain::toCode(int index, bool &ok) const
{
    ok = true;
    switch (_values.length()) {
    case 2:
        switch (index) {
        case 0: return 0;
        case 1: return 127;
        } break;
    case 3:
        switch (index) {
        case 0: return 0;
        case 1: return 64;
        case 2: return 127;
        } break;
    case 4:
        switch (index) {
        case 0: return 0;
        case 1: return 43;
        case 2: return 85;
        case 3: return 127;
        } break;
    case 5:
        switch (index) {
        case 0: return 0;
        case 1: return 32;
        case 2: return 64;
        case 3: return 96;
        case 4: return 127;
        } break;
    case 6: switch (index) {
        case 0: return 0;
        case 1: return 26;
        case 2: return 51;
        case 3: return 77;
        case 4: return 102;
        case 5: return 127;
        } break;
    case 7:
        switch (index) {
        case 0: return 0;
        case 1: return 22;
        case 2: return 43;
        case 3: return 64;
        case 4: return 85;
        case 5: return 106;
        case 6: return 127;
        } break;
    }
    ok = false;
    qWarning() << "Index" << index << "invalid.";
    return 0;

}

int DiscreteDomain::toIndex(quint8 code, bool &ok) const
{
    ok = true;
    for (int i = 0; i < _values.size(); i++) {
        bool unused;
        if (toCode(i, unused) == code) {
            return i;
        }
    }
    ok = false;
    qWarning() << "Code" << code << "invalid.";
    return 0;
}

bool DiscreteDomain::setIndex(int index)
{
    _index = qBound(0, index, _values.length() - 1);
    if (_index != index) {
        qWarning() << "Index" << index << "invalid.";
        return false;
    }
    return true;
}

bool DiscreteDomain::setCode(quint8 code)
{
    bool ok;
    return ok && setIndex(toIndex(code, ok));
}

Domain* DiscreteDomain::copy(Keyboard* keyboard) const
{
    return new DiscreteDomain(midicode(), name(), values(), keyboard);
}
