#ifndef TRIGGERSETTINGWIDGET_H
#define TRIGGERSETTINGWIDGET_H

#include "settingwidget.h"

class TriggerSettingWidget : public SettingWidget
{
    Q_OBJECT
public:
    explicit TriggerSettingWidget(Setting* set, QWidget *parent = 0);

public slots:
    void reset() {}

    REGISTER_DECL_SETTINGWIDGETTYPE(TriggerSettingWidget);

};

#endif // TRIGGERSETTINGWIDGET_H
