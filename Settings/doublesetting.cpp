#include "doublesetting.h"

REGISTER_DEFN_SETTINGTYPE(DoubleSetting);

DoubleSetting::DoubleSetting(Node *parent, QString name, QString tooltip, double minValue, double maxValue, double defaultValue, double currentValue)
    : ScalarSetting(parent, name, tooltip, minValue, maxValue, defaultValue, currentValue)
{
}

DoubleSetting::DoubleSetting(Node *parent, QString name, QString tooltip, double defaultValue, double currentValue)
    : ScalarSetting(parent, name, tooltip, defaultValue, currentValue)
{
}

DoubleSetting::DoubleSetting(QDataStream &stream)
    : ScalarSetting(stream)
{
}

DoubleSetting::~DoubleSetting()
{
}
