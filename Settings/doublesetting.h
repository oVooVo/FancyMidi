#ifndef DOUBLESETTING_H
#define DOUBLESETTING_H

#include "scalarsetting.h"

class DoubleSetting : public ScalarSetting<double>
{
    Q_OBJECT
public:
    DoubleSetting(Node *parent, QString name, QString tooltip,
                  double minValue, double maxValue,
                  double defaultValue, double currentValue);

    DoubleSetting(Node *parent, QString name, QString tooltip,
                  double defaultValue, double currentValue);
    ~DoubleSetting();
};

QDataStream &operator<<(QDataStream &out, const DoubleSetting *DoubleSetting);
QDataStream &operator>>(QDataStream &in, DoubleSetting *&setting);

#endif // DOUBLESETTING_H
