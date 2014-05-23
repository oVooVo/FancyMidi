#ifndef MIDICOMMANDSELECTSETTINGWIDGET_H
#define MIDICOMMANDSELECTSETTINGWIDGET

#include <QWidget>
#include "../Settings/midicommandselectsetting.h"
#include "settingwidget.h"

namespace Ui {
class MidiCommandSelectSettingWidget;
}

class MidiCommandSelectSettingWidget : public SettingWidget
{
    Q_OBJECT
    REGISTER_DECL_SETTINGWIDGETTYPE(MidiCommandSelectSettingWidget);

public:
    explicit MidiCommandSelectSettingWidget(Setting *setting, QWidget *parent = 0);
    ~MidiCommandSelectSettingWidget();

public slots:
    void reset();

private:
    Ui::MidiCommandSelectSettingWidget *ui;

private slots:
    void updatePropertyBox();
};

#endif // MIDICOMMANDSELECTSETTINGWIDGET
