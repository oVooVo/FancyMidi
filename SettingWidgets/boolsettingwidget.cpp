#include "boolsettingwidget.h"
#include <QHBoxLayout>

REGISTER_DEFN_SETTINGWIDGETTYPE(BoolSettingWidget);

BoolSettingWidget::BoolSettingWidget(Setting *set, QWidget *parent) : SettingWidget(set, parent)
{
    Q_ASSERT(set->metaObject()->className() == BoolSetting::staticMetaObject.className());

   _initMode = true;
	setupUi(this);
    _title->setText(set->name());
    _toolTip->setText(set->tooltip());
    _toolTip->setVisible(false);
	helpIcon->setVisible(false);
    _checkBox->setText(set->tooltip());
    _checkBox->setChecked(setting<BoolSetting>()->value());
    _checkBox->setToolTip(set->tooltip());
    connect(_checkBox, SIGNAL(toggled(bool)), setting<BoolSetting>(), SLOT(setValue(bool)));

    connect(helpIcon, SIGNAL(pressed()), _toolTip, SLOT(show()));
    connect(helpIcon, SIGNAL(released()), _toolTip, SLOT(hide()));
    _initMode = false;
}

void BoolSettingWidget::reset()
{
    _checkBox->setChecked(setting<BoolSetting>()->value());
}
