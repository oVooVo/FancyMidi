#include "integersettingwidget.h"

#include <QHBoxLayout>

IntegerSettingWidget::IntegerSettingWidget(IntegerSetting* setting, QWidget *parent) : SettingWidget(setting, parent)
{
    _initMode = true;
	setupUi(this);
    _setting = setting;
    _title->setText(setting->getName());
    _toolTip->setText(setting->tooltip());
    _toolTip->setVisible(false);

    _slider->setMinimum(setting->minValue());
    _slider->setMaximum(setting->maxValue());
    _slider->setValue(setting->value());
    _slider->setSingleStep(setting->stepSize());
	_slider->setOrientation(Qt::Horizontal);
    _spinBox->setMinimum(setting->minValue());
    _spinBox->setMaximum(setting->maxValue());
    _spinBox->setValue(setting->value());
    _spinBox->setSingleStep(setting->stepSize());

    _spinBox->setToolTip(setting->tooltip());
    _slider->setToolTip(setting->tooltip());

    // Synchronize Slider<->SpinBox
	connect(_slider, SIGNAL(valueChanged(int)), _spinBox, SLOT(setValue(int)));
	connect(_spinBox, SIGNAL(valueChanged(int)), _slider, SLOT(setValue(int)));

    connect(_slider, SIGNAL(valueChanged(int)), this, SLOT(forwardValue(int)));

    connect(helpIcon, SIGNAL(pressed()), _toolTip, SLOT(show()));
    connect(helpIcon, SIGNAL(released()), _toolTip, SLOT(hide()));
    _initMode = false;
}

void IntegerSettingWidget::forwardValue(int value)
{
    stop();
    _setting->setValue(value);
}

void IntegerSettingWidget::reset()
{
    _slider->setValue(_setting->value());
    _spinBox->setValue(_setting->value());
}



