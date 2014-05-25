#include "doublesetting.h"

DoubleSetting::DoubleSetting(Node *parent, QString name, QString tooltip, double minValue, double maxValue, double defaultValue, double currentValue)
    : ScalarSetting(parent, name, tooltip, minValue, maxValue, defaultValue, currentValue)
{
}

DoubleSetting::DoubleSetting(Node *parent, QString name, QString tooltip, double defaultValue, double currentValue)
    : ScalarSetting(parent, name, tooltip, defaultValue, currentValue)
{
}

DoubleSetting::~DoubleSetting()
{
}

QDataStream &operator<<(QDataStream &out, const DoubleSetting *setting)
{
//    out << QString("DoubleSetting");
//    out << setting->name() << setting->tooltip()
//        << qreal(setting->minValue()) << qreal(setting->maxValue())
//        << qreal(setting->defaultValue()) << qreal(setting->stepSize())
//        << qreal(setting->value());
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
    setting = new DoubleSetting(NULL, name, tooltip, minValue, maxValue, defaultValue, currentValue);

    return in;
}
