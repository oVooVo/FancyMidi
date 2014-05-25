#ifndef SCALARSETTING_H
#define SCALARSETTING_H

#include "setting.h"
#include <QVariant>
#include "Model/port.h"
#include "Model/inputport.h"
#include "Model/outputport.h"
#include <qdebug.h>

template<typename T>
class ScalarSetting : public Setting
{

public:
    ScalarSetting(Node *parent, QString name, QString tooltip, T min, T max,
                  T defaultValue, T currentValue)
        : Setting(parent, name, tooltip)
    {
        _default = defaultValue;
        _value = currentValue;
        _min = min;
        _max = max;
        _hasBounds = true;
        setValid(true);
    }

    ScalarSetting(Node *parent, QString name, QString tooltip,
                  T defaultValue, T currentValue)
        : Setting(parent, name, tooltip)
    {
        _default = defaultValue;
        _value = currentValue;
        _hasBounds = false;
        setValid(true);
    }


    T value() const { return _value; }
    T min() const { return _min; }
    T max() const { return _max; }
    T defaultValue() const { return _default; }
    bool hasBounds() const { return _hasBounds; }

    virtual void connectPort(Port* port)
    {
        if (port->isInput()) {
            QObject::connect((InputPort*) port, &InputPort::receivedData, [this](QVariant data) {
                if (!data.canConvert<T>()) return;
                setValue(data.value<T>());
            });
        } else {
            QObject::connect(this, &Setting::changed, [this, port]() {
                ((OutputPort*) port)->send(value());
            });
        }
    }

    virtual void setValue(T value)
    {
        if (_value == value) {
            return;
        }

        if (_hasBounds) {
            _value = qBound(_min, value, _max);
        } else {
            _value = value;
        }
        emitChanged();

    }

private:
    T _value;
    T _min = 0;
    T _max = 0;
    T _default;
    bool _hasBounds;
};

#endif // SCALARSETTING_H
