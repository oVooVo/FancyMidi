#include "midifiltersettingwidget.h"
#include "ui_midifiltersettingwidget.h"
#include "../Settings/midifiltersetting.h"
#include <QComboBox>
#include "nordstage2.h"

REGISTER_DEFN_SETTINGWIDGETTYPE(MidiFilterSettingWidget);

MidiFilterSettingWidget::MidiFilterSettingWidget(Setting *set, QWidget *parent) :
    SettingWidget(set, parent),
    ui(new Ui::MidiFilterSettingWidget)
{
    Q_ASSERT(set->metaObject()->className() == MidiFilterSetting::staticMetaObject.className());
    ui->setupUi(this);
    ui->category->addItems(NordStage2::categories());
    connect(ui->filterProperty, &QCheckBox::toggled, [this](bool on) {
        if (on) {
            ui->filterCategory->setChecked(true);
        }
    });
    connect(ui->filterCategory, &QCheckBox::toggled, [this](bool on) {
       if (!on) {
           ui->filterProperty->setChecked(false);
       }
    });

    connect(ui->type, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [this]() {
        updateVisibility();
    });

    connect(ui->category, SIGNAL(currentIndexChanged(int)),
            setting<MidiFilterSetting>(), SLOT(setCategoryIndex(int)));

    connect(ui->type, SIGNAL(currentIndexChanged(int)),
            setting<MidiFilterSetting>(), SLOT(setTypeIndex(int)));
    connect(ui->type, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateVisibility()));
    connect(ui->property, SIGNAL(currentIndexChanged(int)),
            setting<MidiFilterSetting>(), SLOT(setPropertyIndex(int)));
    connect(ui->channel, SIGNAL(valueChanged(int)),
            setting<MidiFilterSetting>(), SLOT(setChannel(int)));
    connect(ui->category, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updatePropertyBox()));


    connect(ui->filterCategory, SIGNAL(toggled(bool)),
            setting<MidiFilterSetting>(), SLOT(setFilterCategory(bool)));
    connect(ui->filterType, SIGNAL(toggled(bool)),
            setting<MidiFilterSetting>(), SLOT(setFilterType(bool)));
    connect(ui->filterChannel, SIGNAL(toggled(bool)),
            setting<MidiFilterSetting>(), SLOT(setFilterChannel(bool)));
    connect(ui->filterProperty, SIGNAL(toggled(bool)),
            setting<MidiFilterSetting>(), SLOT(setFilterProperty(bool)));
    updatePropertyBox();
    reset();
}

void MidiFilterSettingWidget::updateVisibility()
{
    bool e = ui->type->currentIndex() == 2;
    ui->filterProperty->setEnabled(e);
    ui->filterCategory->setEnabled(e);
    ui->property->setEnabled(e && ui->filterProperty->isChecked());
    ui->category->setEnabled(e && ui->filterCategory->isChecked());
}

MidiFilterSettingWidget::~MidiFilterSettingWidget()
{
    delete ui;
}

void MidiFilterSettingWidget::reset()
{
    if (ui->category->currentIndex() != setting<MidiFilterSetting>()->categoryIndex()) {
        updatePropertyBox();
        ui->category->setCurrentIndex(setting<MidiFilterSetting>()->categoryIndex());
    }
    if (ui->property->currentIndex() != setting<MidiFilterSetting>()->propertyIndex()) {
        qDebug() << "set property box index " << setting<MidiFilterSetting>()->propertyIndex();
        ui->property->setCurrentIndex(setting<MidiFilterSetting>()->propertyIndex());
    }
    if (ui->type->currentIndex() != setting<MidiFilterSetting>()->typeIndex()) {
        ui->type->setCurrentIndex(setting<MidiFilterSetting>()->typeIndex());
    }
    if (ui->channel->value() != setting<MidiFilterSetting>()->channel()) {
        ui->channel->setValue(setting<MidiFilterSetting>()->channel());
    }
    if (ui->filterCategory->isChecked() != setting<MidiFilterSetting>()->filterCategory()) {
        ui->filterCategory->setChecked(setting<MidiFilterSetting>()->filterCategory());
    }
    if (ui->filterType->isChecked() != setting<MidiFilterSetting>()->filterType()) {
        ui->filterType->setChecked(setting<MidiFilterSetting>()->filterType());
    }
    if (ui->filterChannel->isChecked() != setting<MidiFilterSetting>()->filterChannel()) {
        ui->filterChannel->setChecked(setting<MidiFilterSetting>()->filterChannel());
    }
    if (ui->filterProperty->isChecked() != setting<MidiFilterSetting>()->filterProperty()) {
        ui->filterProperty->setChecked(setting<MidiFilterSetting>()->filterProperty());
    }
    updateVisibility();
}

void MidiFilterSettingWidget::updatePropertyBox()
{
    ui->property->blockSignals(true);
    ui->property->clear();      // we dont want to let property combobox emit its index changed to -1.
    ui->property->addItems(NordStage2::properties(setting<MidiFilterSetting>()->categoryIndex()));
    ui->property->setCurrentIndex(setting<MidiFilterSetting>()->propertyIndex());
    ui->property->blockSignals(false);
}

