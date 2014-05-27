#include "boolsettingwidget.h"
#include <QHBoxLayout>

REGISTER_DEFN_SETTINGWIDGETTYPE(BoolSettingWidget);

BoolSettingWidget::BoolSettingWidget(Setting *set, QWidget *parent) : SettingWidget(set, parent)
{
    Q_ASSERT(set->metaObject()->className() == BoolSetting::staticMetaObject.className());

   _initMode = true;
	setupUi(this);
    _checkBox->setText(set->name());
    _checkBox->setChecked(setting<BoolSetting>()->value());
    connect(_checkBox, &QCheckBox::toggled, [this](bool on) {
        setting<BoolSetting>()->setValue(on);
    });

    _initMode = false;
}

void BoolSettingWidget::reset()
{
    _checkBox->setChecked(setting<BoolSetting>()->value());
}
