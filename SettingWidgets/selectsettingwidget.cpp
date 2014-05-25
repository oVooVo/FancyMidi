#include "selectsettingwidget.h"
#include "../Settings/selectsetting.h"
#include <QHBoxLayout>

REGISTER_DEFN_SETTINGWIDGETTYPE(SelectSettingWidget);

SelectSettingWidget::SelectSettingWidget(Setting* set, QWidget* parent) : SettingWidget(set, parent)
{
    Q_ASSERT(set->metaObject()->className() == SelectSetting::staticMetaObject.className());
    _initMode = true;
    setupUi(this);
    _title->setText(setting<SelectSetting>()->name());
    _toolTip->setText(setting<SelectSetting>()->tooltip());
    _toolTip->setVisible(false);

    foreach(QString entry, setting<SelectSetting>()->values())
	{
        _comboBox->addItem(entry);
	}

    _comboBox->setEditable(false);
    _comboBox->setCurrentIndex(setting<SelectSetting>()->currentIndex());
    _comboBox->setToolTip(setting<SelectSetting>()->tooltip());

    connect(_comboBox, SIGNAL(activated(int)), SettingWidget::setting<SelectSetting>(), SLOT(setCurrentIndex(int)));

    connect(helpIcon, SIGNAL(pressed()), _toolTip, SLOT(show()));
    connect(helpIcon, SIGNAL(released()), _toolTip, SLOT(hide()));
    _initMode = false;
}

void SelectSettingWidget::reset()
{
    _comboBox->setCurrentIndex(setting<SelectSetting>()->currentIndex());
}
