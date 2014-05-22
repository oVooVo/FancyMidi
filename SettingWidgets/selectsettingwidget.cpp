#include "selectsettingwidget.h"
#include "../Settings/selectsetting.h"
#include <QHBoxLayout>



SelectSettingWidget::SelectSettingWidget(SelectSetting* setting, QWidget* parent) : SettingWidget(setting, parent)
{
    _initMode = true;
    setupUi(this);
    _setting = setting;
    _title->setText(setting->getName());
    _toolTip->setText(setting->tooltip());
    _toolTip->setVisible(false);

    foreach(QString entry, setting->values())
	{
        _comboBox->addItem(entry);
	}

    _comboBox->setEditable(false);
    _comboBox->setCurrentIndex(setting->currentIndex());
    _comboBox->setToolTip(setting->tooltip());

    connect(_comboBox, SIGNAL(activated(int)), this, SLOT(forwardValue(int)));

    connect(helpIcon, SIGNAL(pressed()), _toolTip, SLOT(show()));
    connect(helpIcon, SIGNAL(released()), _toolTip, SLOT(hide()));
    _initMode = false;
}

void SelectSettingWidget::forwardValue(int currentIndex)
{
    stop();
    _setting->setCurrentIndex(currentIndex);
}

void SelectSettingWidget::reset()
{
    _comboBox->setCurrentIndex(_setting->currentIndex());
}
