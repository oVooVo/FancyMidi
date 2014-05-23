#include "integersettingwidget.h"

#include <QHBoxLayout>

REGISTER_DEFN_SETTINGWIDGETTYPE(IntegerSettingWidget);

IntegerSettingWidget::IntegerSettingWidget(Setting* set, QWidget *parent) : SettingWidget(set, parent)
{
    Q_ASSERT(set->metaObject()->className() == IntegerSetting::staticMetaObject.className());

    _initMode = true;
	setupUi(this);
    _title->setText(setting<IntegerSetting>()->getName());
    _toolTip->setText(setting<IntegerSetting>()->tooltip());
    _toolTip->setVisible(false);

    _slider->setMinimum(setting<IntegerSetting>()->minValue());
    _slider->setMaximum(setting<IntegerSetting>()->maxValue());
    _slider->setValue(setting<IntegerSetting>()->value());
    _slider->setSingleStep(setting<IntegerSetting>()->stepSize());
	_slider->setOrientation(Qt::Horizontal);
    _spinBox->setMinimum(setting<IntegerSetting>()->minValue());
    _spinBox->setMaximum(setting<IntegerSetting>()->maxValue());
    _spinBox->setValue(setting<IntegerSetting>()->value());
    _spinBox->setSingleStep(setting<IntegerSetting>()->stepSize());

    _spinBox->setToolTip(setting<IntegerSetting>()->tooltip());
    _slider->setToolTip(setting<IntegerSetting>()->tooltip());

    // Synchronize Slider<->SpinBox
	connect(_slider, SIGNAL(valueChanged(int)), _spinBox, SLOT(setValue(int)));
	connect(_spinBox, SIGNAL(valueChanged(int)), _slider, SLOT(setValue(int)));

    connect(_slider, SIGNAL(valueChanged(int)), setting<IntegerSetting>(), SLOT(setValue(int)));

    connect(helpIcon, SIGNAL(pressed()), _toolTip, SLOT(show()));
    connect(helpIcon, SIGNAL(released()), _toolTip, SLOT(hide()));
    _initMode = false;
}

void IntegerSettingWidget::reset()
{
    _slider->setValue(setting<IntegerSetting>()->value());
    _spinBox->setValue(setting<IntegerSetting>()->value());
}



