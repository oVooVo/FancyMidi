#ifndef MIDIFILTERSETTINGWIDGET_H
#define MIDIFILTERSETTINGWIDGET_H

#include <QWidget>
#include "settingwidget.h"

namespace Ui {
class MidiFilterSettingWidget;
}

class MidiFilterSettingWidget : public SettingWidget
{
    Q_OBJECT
    REGISTER_DECL_SETTINGWIDGETTYPE(MidiFilterSettingWidget);

public:
    explicit MidiFilterSettingWidget(Setting* setting, QWidget *parent = 0);
    ~MidiFilterSettingWidget();

private:
    Ui::MidiFilterSettingWidget *ui;

signals:
    void categoryChanged(int);
    void propertyChanged(int);
    void typeChanged(int);

private slots:
    void updateVisibility();
    void reset();
    void updatePropertyBox();
};

#endif // MIDIFILTERSETTINGWIDGET_H
