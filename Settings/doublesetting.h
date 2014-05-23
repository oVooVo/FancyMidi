#ifndef DOUBLESETTING_H
#define DOUBLESETTING_H

#include "setting.h"

class DoubleSetting : public Setting
{
public:
    DoubleSetting(Node *parent, QString name, QString tooltip,
                  double minValue, double maxValue,
                  double defaultValue, double stepSize, double currentValue);
    ~DoubleSetting();
    double value() const;
    double defaultValue() const;
    double minValue() const;
    double maxValue() const;
    double stepSize() const;

public slots:
    void setValue(double value);

private:
    double _minValue;
    double _maxValue;
    double _value;
    double _stepSize;
    double _defaultValue;
};

QDataStream &operator<<(QDataStream &out, const DoubleSetting *DoubleSetting);
QDataStream &operator>>(QDataStream &in, DoubleSetting *&setting);

#endif // DOUBLESETTING_H
