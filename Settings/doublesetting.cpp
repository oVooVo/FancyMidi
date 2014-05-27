#include "doublesetting.h"

REGISTER_DEFN_SETTINGTYPE(DoubleSetting);

DoubleSetting::DoubleSetting(Node *parent, QString name, QString tooltip,
                             double minValue, double maxValue,
                             double defaultValue, double currentValue,
                             bool showInNode)
    : ScalarSetting(parent, name, tooltip, minValue, maxValue, defaultValue, currentValue, showInNode)
{
}

DoubleSetting::DoubleSetting(Node *parent, QString name, QString tooltip,
                             double defaultValue, double currentValue,
                             bool showInNode)
    : ScalarSetting(parent, name, tooltip, defaultValue, currentValue, showInNode)
{
}

DoubleSetting::DoubleSetting(QDataStream &stream)
    : ScalarSetting(stream)
{
}

DoubleSetting::~DoubleSetting()
{
}
