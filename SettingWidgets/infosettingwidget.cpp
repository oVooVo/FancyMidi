#include "infosettingwidget.h"
#include "Settings/infosetting.h"
#include "QLabel"
#include <QHBoxLayout>

REGISTER_DEFN_SETTINGWIDGETTYPE(InfoSettingWidget);

InfoSettingWidget::InfoSettingWidget(Setting* set, QWidget* parent)
    : SettingWidget(set, parent)
{
    Q_ASSERT(QString(set->metaObject()->className()) == QString(InfoSetting::staticMetaObject.className()));

    QHBoxLayout* layout = new QHBoxLayout(this);
    _label = new QLabel(this);
    layout->addWidget(_label);
    setLayout(layout);

    reset();
}

void InfoSettingWidget::reset()
{
    _label->setText(setting<InfoSetting>()->string());
}

