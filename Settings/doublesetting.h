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

    DoubleSetting(QDataStream& stream);
    ~DoubleSetting();

public slots:
    void setValue(double value) { ScalarSetting<double>::setValue(value); }

    REGISTER_DECL_SETTINGTYPE(DoubleSetting);
};

#endif // DOUBLESETTING_H
