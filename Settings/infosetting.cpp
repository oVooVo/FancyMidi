#include "infosetting.h"

#include "setting.h"

REGISTER_DEFN_SETTINGTYPE(InfoSetting);

InfoSetting::InfoSetting(QDataStream& stream) : Setting(stream)
{
}

InfoSetting::InfoSetting(Node* parent, QString name, QString tooltip, QString text, bool showInNode)
    : Setting(parent, name, tooltip, showInNode)
{
    _string = text;
}

void InfoSetting::setString(const QString &string)
{
    if (_string == string)
        return;
    _string = string;
    emitChanged();
}
