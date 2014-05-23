#ifndef DOUBLESETTINGWIDGET_H
#define DOUBLESETTINGWIDGET_H

#include <QWidget>
#include "../Settings/doublesetting.h"
#include "ui_doublesettingwidget.h"
#include "settingwidget.h"

class DoubleSettingWidget : public SettingWidget, private Ui::DoubleSettingWidget
{
    Q_OBJECT
    REGISTER_DECL_SETTINGWIDGETTYPE(DoubleSettingWidget);

public:
    explicit DoubleSettingWidget(Setting *setting, QWidget *parent = 0);

private slots:
    void reset();
};

#endif // DOUBLESETTINGWIDGET_H
