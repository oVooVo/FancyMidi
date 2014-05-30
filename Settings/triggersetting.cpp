#include "triggersetting.h"

REGISTER_DEFN_SETTINGTYPE(TriggerSetting);

TriggerSetting::TriggerSetting(Node* node, QString name, QString tooltip, bool showInNode)
    : Setting(node, name, tooltip, showInNode)
{

}

TriggerSetting::TriggerSetting(QDataStream &stream) : Setting(stream)
{

}

void TriggerSetting::writeToStream(QDataStream &stream)
{
    Setting::writeToStream(stream);
}
