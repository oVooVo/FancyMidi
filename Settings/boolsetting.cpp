#include <QApplication>
#include <QThread>
#include "boolsetting.h"

REGISTER_DEFN_SETTINGTYPE(BoolSetting);

BoolSetting::BoolSetting(Node *parent, QString name, QString tooltip, bool defaultValue, bool currentValue)
    : ScalarSetting(parent, name, tooltip, defaultValue, currentValue)
{
}

BoolSetting::BoolSetting(QDataStream &stream)
    : ScalarSetting(stream)
{

}
