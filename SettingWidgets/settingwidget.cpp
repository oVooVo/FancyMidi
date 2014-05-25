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

SETTINGWIDGET_CREATOR_MAP_TYPE *SettingWidget::_creatorMap = 0;

SettingWidget* SettingWidget::createNewSettingWidget(Setting* setting, QWidget* parent)
{
    QString classname = setting->metaObject()->className();

    // Ensure that each Attribute has a corresponding AttributeWidget.
    // AttributeWidget must have same classname as Attribute -"Attribute" + "Widget"
    // for example, "TransformationAttribute" -> "TransformationWidget"
    // what a hack!!! :)

    const QRegExp attribute_s = QRegExp("Setting$");
    const QString widget_s = "Widget";

    Q_ASSERT_X(classname.contains(attribute_s), "SettingWidget::createWidget",
               QString("classname should contain %1, [%2]")
               .arg(attribute_s.pattern())
               .arg(classname).toStdString().c_str());


    classname = classname.append(widget_s);

    SettingWidget* widget = 0;
    SETTINGWIDGET_CREATOR_MAP_TYPE::Iterator it = _creatorMap->find(classname);
    if (it != _creatorMap->end()) {
        widget = (it.value())(setting, parent);
    }

    Q_ASSERT_X(widget, "SettingWidget::createNewSettingWidget()",
               QString("Warning: Classname %1 not found.").arg(classname).toStdString().c_str());

    return widget;
}

