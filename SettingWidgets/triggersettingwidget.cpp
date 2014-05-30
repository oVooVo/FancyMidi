#include "triggersettingwidget.h"
#include "Settings/triggersetting.h"
#include <QPushButton>

REGISTER_DEFN_SETTINGWIDGETTYPE(TriggerSettingWidget);

TriggerSettingWidget::TriggerSettingWidget(Setting *set, QWidget *parent) :
    SettingWidget(set, parent)
{
    Q_ASSERT(QString(set->metaObject()->className()) == QString(TriggerSetting::staticMetaObject.className()));

    QHBoxLayout* layout = new QHBoxLayout(this);
    QPushButton* button = new QPushButton(this);
    button->setText("Trigger");
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(button);
    setLayout(layout);

    connect(button, SIGNAL(pressed()), (TriggerSetting*) set, SIGNAL(changed()));
}
