#include "doublesettingwidget.h"

REGISTER_DEFN_SETTINGWIDGETTYPE(DoubleSettingWidget);

DoubleSettingWidget::DoubleSettingWidget(Setting* set, QWidget *parent) :
    SettingWidget(set, parent)
{
    CHECK_SETTING(DoubleSetting);
    _initMode = true;
    setupUi(this);
    _title->setText(setting<DoubleSetting>()->name());

    _doubleSpinBox->setVisible(setting<DoubleSetting>()->hasBounds());
    lineEdit->setVisible(!setting<DoubleSetting>()->hasBounds());

    if (setting<DoubleSetting>()->hasBounds()) {
        _doubleSpinBox->setMinimum(setting<DoubleSetting>()->min());
        _doubleSpinBox->setMaximum(setting<DoubleSetting>()->max());
        _doubleSpinBox->setToolTip(setting<DoubleSetting>()->tooltip());
        connect(_doubleSpinBox, SIGNAL(valueChanged(double)), setting<DoubleSetting>(), SLOT(setValue(double)));
    } else {
        lineEdit->setValidator(new QDoubleValidator(this));
        connect(lineEdit, &QLineEdit::editingFinished, [this]() {
            setting<DoubleSetting>()->setValue(lineEdit->text().toDouble());
        });
    }

    _initMode = false;
    reset();
}

void DoubleSettingWidget::reset()
{
    if (setting<DoubleSetting>()->hasBounds()) {
        _doubleSpinBox->setValue(setting<DoubleSetting>()->value());
    } else {
        lineEdit->setText(QString("%1").arg(setting<DoubleSetting>()->value()));
    }
}
