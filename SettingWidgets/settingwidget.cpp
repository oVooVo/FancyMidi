#include "settingwidget.h"
#include "QPainter"
#include <QDebug>
#include <QBrush>
#include "mainwindow.h"
#include "../Settings/midicommandselectsetting.h"
#include "midicommandselectsettingwidget.h"
#include "../Settings/integersetting.h"
#include "integersettingwidget.h"

SettingWidget::SettingWidget(Setting *setting, QWidget* parent) : QWidget(parent)
{
    _initMode = false;
	_setting = setting;
    connect(setting, SIGNAL(validChange()), this, SLOT(update())); //repaint when valid state changed
    connect(setting, SIGNAL(changed()), this, SLOT(reset()));
}

void SettingWidget::paintEvent(QPaintEvent *)
{
	const int FRAME_WIDTH = 5;
    if (!_setting->isValid()) {
		QPainter painter(this);
		QPen pen;
		pen.setWidth(FRAME_WIDTH);
		pen.setColor(Qt::red);
		painter.setPen(pen);
        painter.drawRect(0, 0, width(), height());
	}
}

SettingWidget* SettingWidget::createNewSettingWidget(Setting *setting, QWidget *parent)
{
    //todo use register-mechanism from nodes
    if (setting->inherits("MidiCommandSelectSetting")) {
        return new MidiCommandSelectSettingWidget(qobject_cast<MidiCommandSelectSetting*>(setting), parent);
    } else if (setting->inherits("IntegerSetting")) {
        return new IntegerSettingWidget(qobject_cast<IntegerSetting*>(setting), parent);
    }
	return 0;
}

void SettingWidget::stop()
{
    qDebug() << "Stopp in SettingWidget. _initMode: " << _initMode;
    if (_initMode && !parent()) return;      //do not stop when calling stop due first paint of this widget
    QObject* p = parent();
    while (p && !p->inherits("MainWindow"))
    {
        p = p->parent();
    }
    if (p->inherits("MainWindow")) {
        ((MainWindow*) p)->stop();
    }
}

