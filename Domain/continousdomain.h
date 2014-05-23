#ifndef CONTINOUSDOMAIN_H
#define CONTINOUSDOMAIN_H

#include "domain.h"
#include <QString>
#include <QDebug>
#include <functional>
#include "keyboard.h"

#define Decoder(T) std::function<T(quint8, bool&)>
#define Encoder(T) std::function<quint8(T, bool&)>

template<typename T>
class ContinousDomain : public Domain
{
public:
    ContinousDomain(MidiKey midiKey, QString name, T min, T max, Encoder(T) encoder, Decoder(T) decoder, Keyboard* keyboard)
        : Domain(midiKey, name, keyboard)
    {
        _encoder = encoder;
        _decoder = decoder;
        if (min > max) qSwap(min, max);
        _min = min;
        _max = max;
        _value = _min;
    }

    ContinousDomain(MidiKey midiKey, QString name, T min, T max, T value, Encoder(T) encoder, Decoder(T) decoder, Keyboard* keyboard)
        : Domain(midiKey, name, keyboard)
    {
        _encoder = encoder;
        _decoder = decoder;
        if (min > max) qSwap(min, max);
        _min = min;
        _max = max;
        _value = qBound(min, value, max);
        if (_value != value) {
            qWarning() << "Expected value to be between" << min << "and" << max << ".";
        }
    }

    virtual ~ContinousDomain() {}

    T min() const { return _min; }
    T max() const { return _max; }
    T value() const { return _value; }

    void setValue(T value)
    {
        _value = qBound(min(), value, max());
        if (_value != value) {
            qWarning() << "Expected value to be between" << min() << "and" << max() << ".";
        }
    }

    bool setCode(quint8 code)
    {
        bool ok;
        _value = qBound(min(), _encoder(code, ok), max());
        return ok;
    }

    quint8 encode() const
    {
        bool unused;
        return _encoder(_value, unused);
    }

    T decode(quint8 code) const
    {
        bool unused;
        return _decoder(code, unused);
    }

private:
    T _min, _max, _value;

protected:
    Encoder(T) _encoder;
    Decoder(T) _decoder;
};

#endif // CONTINOUSDOMAIN_H
