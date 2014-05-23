#include "doublesetting.h"

DoubleSetting::DoubleSetting(Node *parent, QString name, QString tooltip, double minValue, double maxValue, double defaultValue, double stepSize, double currentValue):
    Setting(parent, name, tooltip)
{
    _minValue = minValue;
    _maxValue = maxValue;
    _value = currentValue;
    _value = qMax(_value, _minValue);
    _value = qMin(_value, _maxValue);
    _stepSize = stepSize;
    _defaultValue = defaultValue;
    setValid(true);
}

DoubleSetting::~DoubleSetting()
{
}
double DoubleSetting::value() const
{
    return _value;
}
double DoubleSetting::defaultValue() const
{
    return _defaultValue;
}

double DoubleSetting::minValue() const
{
    return _minValue;
}
double DoubleSetting::maxValue() const
{
    return _maxValue;
}
double DoubleSetting::stepSize() const
{
    return _stepSize;
}

void DoubleSetting::setValue(double value)
{
    if (value == _value) return;

    _value = value;
    _value = qMax(_value, _minValue);
    _value = qMin(_value, _maxValue);

    emitChanged();
}

QDataStream &operator<<(QDataStream &out, const DoubleSetting *setting)
{
    out << QString("DoubleSetting");
    out << setting->getName() << setting->tooltip()
        << qreal(setting->minValue()) << qreal(setting->maxValue())
        << qreal(setting->defaultValue()) << qreal(setting->stepSize())
        << qreal(setting->value());
    return out;
}

QDataStream &operator>>(QDataStream &in, DoubleSetting *&setting)
{
    QString name;
    QString tooltip;
    qreal minValue;
    qreal maxValue;
    qreal defaultValue;
    qreal currentValue;
    qreal stepSize;

    in >> name;

    if(name == QString("DoubleSetting"))
    {
        in >> name;
    }
    in >> tooltip >> minValue >> maxValue >> defaultValue >> stepSize >> currentValue;

    //delete setting;
    setting = new DoubleSetting(NULL, name, tooltip, minValue, maxValue, defaultValue, stepSize, currentValue);

    return in;
}
