#ifndef TRIGGERSETTING_H
#define TRIGGERSETTING_H

#include "setting.h"

class TriggerSetting : public Setting
{
    Q_OBJECT
public:
    TriggerSetting(Node* node, QString name, QString tooltip, bool showInNode = true);
    TriggerSetting(QDataStream& stream);
    void writeToStream(QDataStream& stream);

    REGISTER_DECL_SETTINGTYPE(TriggerSetting);
};

#endif // TRIGGERSETTING_H
