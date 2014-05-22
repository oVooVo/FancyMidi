#pragma once

#include <QWidget>
#include "Settings/setting.h"
#include <QLabel>
#include <QPainter>
#include <QHBoxLayout>

/**
 * @brief The SettingWidget class is a widget representing the Setting class
 * @see Setting
 */
class SettingWidget : public QWidget
{
    Q_OBJECT
protected:
    /**
     * @brief SettingWidget Creates a SettingWidget on the given parent QWidget
     * @param parent The given parent QWidget
     */
    explicit SettingWidget(Setting* setting, QWidget *parent = 0);

public:
    /**
     * @brief createNewSettingWidget creates a new SettingWidget with a given Setting and parent.
     * @param setting the setting this SettingWidget is associated with.
     * @param parent the parent QWidget of this SettingWidget.
     * @return the new SettingWidget.
     */
    static SettingWidget* createNewSettingWidget(Setting *setting, QWidget *parent = 0);

public slots:
    /**
     * @brief stop tries to stop the project.
     */
    void stop();

    /**
     * @brief reset resets the widget after it's setting object became changed.
     */
    virtual void reset() = 0;

protected:
    /**
     * @brief paintEvent is called when the Widget has to be redrawn.
     * @param event the event.
     */
    void paintEvent(QPaintEvent *event);

    /**
     * @brief _initMode whether this widget changes due to initial draw.
     */
    bool _initMode;

    /**
     * @brief _setting the setting associated with this SettingWidget.
     */
    Setting* _setting;
};


