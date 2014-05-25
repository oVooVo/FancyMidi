#include "arbitrarydoublesettingwidget.h"
#include "ui_arbitrarydoublesettingwidget.h"
#include "Settings/arbitrarydoublesetting.h"
#include <QDebug>

/*
REGISTER_DEFN_SETTINGWIDGETTYPE(ArbitraryDoubleSettingWidget);

ArbitraryDoubleSettingWidget::ArbitraryDoubleSettingWidget(Setting *set, QWidget *parent) :
    SettingWidget(set, parent),
    ui(new Ui::ArbitraryDoubleSettingWidget)
{
    CHECK_SETTING(ArbitraryDoubleSetting);
    ui->setupUi(this);
    reset();
    ui->lineEdit->setValidator(new QDoubleValidator(this));

    connect(ui->lineEdit, &QLineEdit::editingFinished, [this]() {
        bool ok;
        double d = ui->lineEdit->text().toDouble(&ok);
        Q_ASSERT(ok);
        setting<ArbitraryDoubleSetting>()->setValue(d);
    });
}

ArbitraryDoubleSettingWidget::~ArbitraryDoubleSettingWidget()
{
    delete ui;
}

void ArbitraryDoubleSettingWidget::reset()
{
    ui->lineEdit->setText(QString("%1").arg(setting<ArbitraryDoubleSetting>()->value()));
    _lastValidText = ui->lineEdit->text();
}
*/
