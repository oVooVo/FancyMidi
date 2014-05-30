#include "midicommandselectsettingwidget.h"
#include "ui_midicommandselectsettingwidget.h"
#include <QDebug>
#include "Domain/doubledomain.h"
#include "Domain/integerdomain.h"

REGISTER_DEFN_SETTINGWIDGETTYPE(MidiCommandSelectSettingWidget);

MidiCommandSelectSettingWidget::MidiCommandSelectSettingWidget(Setting* set, QWidget *parent) :
    SettingWidget(set , parent),
    ui(new Ui::MidiCommandSelectSettingWidget)
{
    Q_ASSERT(set->metaObject()->className() == MidiCommandSelectSetting::staticMetaObject.className());
    _initMode = true;
    ui->setupUi(this);

    ui->category->addItems(NordStage2::categories());

    _initMode = false;

    ui->category->setCurrentIndex(0);

    connect(ui->category, SIGNAL(currentIndexChanged(int)),
            setting<MidiCommandSelectSetting>(), SLOT(setCategoryIndex(int)));
    connect(ui->property, SIGNAL(currentIndexChanged(int)),
            setting<MidiCommandSelectSetting>(), SLOT(setPropertyIndex(int)));
    connect(ui->category, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updatePropertyBox()));

    connect(ui->doubleSpinBox,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            [this](double value) {
        setting<MidiCommandSelectSetting>()->setValue(value);
    });
    connect(ui->spinBox,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            [this](int value) {
        setting<MidiCommandSelectSetting>()->setValue(value);
    });
    connect(ui->comboBox,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            [this](int value) {
        setting<MidiCommandSelectSetting>()->setValue(value);
    });

    ui->spinBox->setRange(0, Keyboard::NUM_MIDI_CHANNELS);
    updatePropertyBox();
    reset();
}

MidiCommandSelectSettingWidget::~MidiCommandSelectSettingWidget()
{
    delete ui;
}

void MidiCommandSelectSettingWidget::updatePropertyBox()
{
    ui->property->blockSignals(true);
    ui->property->clear();      // we dont want to let property combobox emit its index changed to -1.
    ui->property->addItems(NordStage2::properties(setting<MidiCommandSelectSetting>()->currentCategory()));
    ui->property->setCurrentIndex(setting<MidiCommandSelectSetting>()->currentProperty());
    ui->property->blockSignals(false);
}

void MidiCommandSelectSettingWidget::reset()
{
    if (ui->category->currentIndex() != setting<MidiCommandSelectSetting>()->currentCategory()) {
        updatePropertyBox();
        ui->category->setCurrentIndex(setting<MidiCommandSelectSetting>()->currentCategory());
    }
    if (ui->property->currentIndex() != setting<MidiCommandSelectSetting>()->currentProperty()) {
        ui->property->setCurrentIndex(setting<MidiCommandSelectSetting>()->currentProperty());
    }

    ui->comboBox->blockSignals(true);
    ui->spinBox->blockSignals(true);
    ui->doubleSpinBox->blockSignals(true);

    switch (setting<MidiCommandSelectSetting>()->domainType()) {
    case Domain::Discrete:
        ui->spinBox->hide();
        ui->doubleSpinBox->hide();
        ui->comboBox->show();
        ui->comboBox->clear();
        ui->comboBox->addItems(setting<MidiCommandSelectSetting>()->items());
        ui->comboBox->setCurrentIndex(setting<MidiCommandSelectSetting>()->index());
        break;
    case Domain::Double:
        ui->spinBox->hide();
        ui->doubleSpinBox->show();
        ui->comboBox->hide();
        ui->doubleSpinBox->setRange(setting<MidiCommandSelectSetting>()->min(),
                                    setting<MidiCommandSelectSetting>()->max());
        ui->doubleSpinBox->setValue(setting<MidiCommandSelectSetting>()->value());
        break;
    case Domain::Integer:
        ui->spinBox->show();
        ui->doubleSpinBox->hide();
        ui->comboBox->hide();
        ui->spinBox->setRange(setting<MidiCommandSelectSetting>()->min(),
                              setting<MidiCommandSelectSetting>()->max());
        ui->spinBox->setValue(setting<MidiCommandSelectSetting>()->value());
        break;
    }
    ui->comboBox->blockSignals(false);
    ui->spinBox->blockSignals(false);
    ui->doubleSpinBox->blockSignals(false);


}
