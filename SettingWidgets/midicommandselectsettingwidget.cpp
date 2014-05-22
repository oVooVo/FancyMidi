#include "midicommandselectsettingwidget.h"
#include "ui_midicommandselectsettingwidget.h"
#include <QDebug>
#include "Domain/doubledomain.h"
#include "Domain/integerdomain.h"

MidiCommandSelectSettingWidget::MidiCommandSelectSettingWidget(MidiCommandSelectSetting* setting, QWidget *parent) :
    SettingWidget(setting , parent),
    ui(new Ui::MidiCommandSelectSettingWidget)
{
    _initMode = true;
    ui->setupUi(this);

    ui->category->addItems(setting->categories());

    connect(ui->category, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updatePropertyBox()));

    _initMode = false;

    ui->category->setCurrentIndex(0);

    connect(ui->category, SIGNAL(currentIndexChanged(int)), setting, SLOT(setCategory(int)));
    connect(ui->property, SIGNAL(currentIndexChanged(int)), setting, SLOT(setProperty(int)));
    connect(ui->doubleSpinBox, SIGNAL(valueChanged(double)), setting, SLOT(setDouble(double)));
    connect(ui->spinBox, SIGNAL(valueChanged(int)), setting, SLOT(setInt(int)));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), setting, SLOT(setIndex(int)));
    connect(ui->pushButton, SIGNAL(clicked()), setting, SIGNAL(sendMidi()));
    reset();
}

MidiCommandSelectSettingWidget::~MidiCommandSelectSettingWidget()
{
    delete ui;
}

void MidiCommandSelectSettingWidget::updatePropertyBox()
{

}

void MidiCommandSelectSettingWidget::reset()
{
    MidiCommandSelectSetting* mcss = (MidiCommandSelectSetting*) _setting;

    ui->comboBox->blockSignals(true);
    ui->spinBox->blockSignals(true);
    ui->doubleSpinBox->blockSignals(true);
    ui->property->blockSignals(true);
    ui->category->blockSignals(true);
    ui->property->clear();      // we dont want to let property combobox emit its index changed to -1.
    ui->property->addItems(((MidiCommandSelectSetting*) _setting)->properties());


    switch (mcss->domainType()) {
    case Domain::Discrete:
        ui->spinBox->hide();
        ui->doubleSpinBox->hide();
        ui->comboBox->show();
        ui->comboBox->clear();
        ui->comboBox->addItems(mcss->items());
        ui->comboBox->setCurrentIndex(mcss->index());
        break;
    case Domain::Double:
        ui->spinBox->hide();
        ui->doubleSpinBox->show();
        ui->comboBox->hide();
        ui->doubleSpinBox->setRange(mcss->min(), mcss->max());
        ui->doubleSpinBox->setValue(mcss->value());
        break;
    case Domain::Integer:
        ui->spinBox->show();
        ui->doubleSpinBox->hide();
        ui->comboBox->hide();
        ui->spinBox->setRange(mcss->min(), mcss->max());
        ui->spinBox->setValue(mcss->value());
        break;
    }
    ui->property->blockSignals(false);
    ui->category->blockSignals(false);
    ui->comboBox->blockSignals(false);
    ui->spinBox->blockSignals(false);
    ui->doubleSpinBox->blockSignals(false);

    ui->category->setCurrentIndex(mcss->currentCategory());
    ui->property->setCurrentIndex(mcss->currentProperty());

}
