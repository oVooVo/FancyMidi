#include "doublesettingwidget.h"

REGISTER_DEFN_SETTINGWIDGETTYPE(DoubleSettingWidget);

DoubleSettingWidget::DoubleSettingWidget(Setting* set, QWidget *parent) :
    SettingWidget(set, parent)
{
    Q_ASSERT(set->metaObject()->className() == DoubleSetting::staticMetaObject.className());

    _initMode = true;
    setupUi(this);
    _title->setText(setting<DoubleSetting>()->getName());
    _toolTip->setText(setting<DoubleSetting>()->tooltip());
    _toolTip->setVisible(false);


    _doubleSpinBox->setMinimum(setting<DoubleSetting>()->minValue());
    _doubleSpinBox->setMaximum(setting<DoubleSetting>()->maxValue());
    _doubleSpinBox->setValue(setting<DoubleSetting>()->value());
    _doubleSpinBox->setSingleStep(setting<DoubleSetting>()->stepSize());

    _doubleSpinBox->setToolTip(setting<DoubleSetting>()->tooltip());

    connect(_doubleSpinBox, SIGNAL(valueChanged(double)), setting<DoubleSetting>(), SLOT(setValue(double)));

    connect(helpIcon, SIGNAL(pressed()), _toolTip, SLOT(show()));
    connect(helpIcon, SIGNAL(released()), _toolTip, SLOT(hide()));
    _initMode = false;
}

void DoubleSettingWidget::reset()
{
    _doubleSpinBox->setValue(setting<DoubleSetting>()->value());
}
