#include "integersettingwidget.h"

#include <QHBoxLayout>
#include <QIntValidator>

REGISTER_DEFN_SETTINGWIDGETTYPE(IntegerSettingWidget);

IntegerSettingWidget::IntegerSettingWidget(Setting* set, QWidget *parent) : SettingWidget(set, parent)
{
    Q_ASSERT(set->metaObject()->className() == IntegerSetting::staticMetaObject.className());

    _initMode = true;
	setupUi(this);
    _title->setText(setting<IntegerSetting>()->name());

    _slider->setVisible(setting<IntegerSetting>()->hasBounds());
    _spinBox->setVisible(setting<IntegerSetting>()->hasBounds());
    lineEdit->setVisible(!setting<IntegerSetting>()->hasBounds());

    if (setting<IntegerSetting>()->hasBounds()) {
        _slider->setMinimum(setting<IntegerSetting>()->min());
        _slider->setMaximum(setting<IntegerSetting>()->max());
        _slider->setOrientation(Qt::Horizontal);
        _spinBox->setMinimum(setting<IntegerSetting>()->min());
        _spinBox->setMaximum(setting<IntegerSetting>()->max());

        _spinBox->setToolTip(setting<IntegerSetting>()->tooltip());
        _slider->setToolTip(setting<IntegerSetting>()->tooltip());

        // Synchronize Slider<->SpinBox
        connect(_slider, SIGNAL(valueChanged(int)), _spinBox, SLOT(setValue(int)));
        connect(_spinBox, SIGNAL(valueChanged(int)), _slider, SLOT(setValue(int)));

        connect(_slider, &QSlider::valueChanged, [this](int value) {
            setting<IntegerSetting>()->setValue(value);
        });
    } else {
        lineEdit->setValidator(new QIntValidator(this));
        connect(lineEdit, &QLineEdit::editingFinished, [this]() {
            setting<IntegerSetting>()->setValue(lineEdit->text().toInt());
        });
    }
    _initMode = false;
    reset();
}

void IntegerSettingWidget::reset()
{
    if (setting<IntegerSetting>()->hasBounds()) {
        _slider->setValue(setting<IntegerSetting>()->value());
        _spinBox->setValue(setting<IntegerSetting>()->value());
    } else {
        lineEdit->setText(QString("%1").arg(setting<IntegerSetting>()->value()));
    }
}


