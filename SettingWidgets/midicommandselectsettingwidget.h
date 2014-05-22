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

public:
    explicit MidiCommandSelectSettingWidget(MidiCommandSelectSetting* setting, QWidget *parent = 0);
    ~MidiCommandSelectSettingWidget();

public slots:
    void reset();

private:
    Ui::MidiCommandSelectSettingWidget *ui;

private slots:
    void updatePropertyBox();
};

#endif // MIDICOMMANDSELECTSETTINGWIDGET
