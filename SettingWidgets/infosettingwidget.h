#ifndef INFOSETTINGWIDGET_H
#define INFOSETTINGWIDGET_H

#include "settingwidget.h"


class InfoSettingWidget : public SettingWidget
{
public:
    InfoSettingWidget(Setting* set, QWidget* parent);

public slots:
    void reset();

private:
    QLabel* _label;

    REGISTER_DECL_SETTINGWIDGETTYPE(InfoSettingWidget);
};

#endif // INFOSETTINGWIDGET_H
