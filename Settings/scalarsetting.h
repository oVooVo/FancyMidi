#ifndef SCALARSETTING_H
#define SCALARSETTING_H

#include "setting.h"
#include <QVariant>
#include "Model/port.h"
#include "Model/inputport.h"
#include "Model/outputport.h"
#include <qdebug.h>
#include "Model/datainputport.h"

template<typename T>
class ScalarSetting : public Setting
{
public:
    ScalarSetting(Node *parent, QString name, QString tooltip, T min, T max,
                  T defaultValue, T currentValue,
                  bool showInNode = true)
        : Setting(parent, name, tooltip, showInNode)
    {
        _min = min;
        _max = max;
        _default = qBound(_min, defaultValue, _max);
        _value = qBound(_min, currentValue, _max);
        _hasBounds = true;
    }

    ScalarSetting(Node *parent, QString name, QString tooltip,
                  T defaultValue, T currentValue, bool showInNode = true)
        : Setting(parent, name, tooltip, showInNode)
    {
        _default = defaultValue;
        _value = currentValue;
        _hasBounds = false;
    }

    ScalarSetting(QDataStream& stream) : Setting(stream)
    {
        stream >> _default >> _value >> _min >> _max >> _hasBounds;
    }

    void writeToStream(QDataStream &stream) const
    {
        Setting::writeToStream(stream);
        stream << _default << _value << _min << _max << _hasBounds;
    }

    T value() const { return _value; }
    T min() const { return _min; }
    T max() const { return _max; }
    T defaultValue() const { return _default; }
    bool hasBounds() const { return _hasBounds; }

    void connectPort(DataInputPort* port)
    {
        port->setFallback(value());

        connect(this, &Setting::changed, [port, this](){
            port->setFallback(value());
        });
        connect(port, &DataInputPort::dataChanged, [this, port]() {
            setValue(port->data().value<T>());
        });
        connect(port, &DataInputPort::connectionToggled, [this](bool connected) {
            setEnabled(!connected);
        });
    }


protected:
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
