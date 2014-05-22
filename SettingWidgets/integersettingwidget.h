#pragma once

#include "settingwidget.h"
#include "../Settings/integersetting.h"
#include <QSlider>
#include <QSpinBox>
#include "ui_integersettingwidget.h"

/**
 * @brief The IntegerSettingWidget class provides a graphical user interface for the IntegerSetting class.
 * @see SettingWidget
 * @see IntegerSetting
 */
class IntegerSettingWidget : public SettingWidget, private Ui::IntegerSettingWidget
{
	Q_OBJECT

public:
	/**
     * @brief IntegerSettingWidget Creates a IntegerSettingWidget out of given minimum, maximum, default value
     *  and step size
	 * @param minValue The minimum value
	 * @param maxValue The maximal value
	 * @param defaultValue The default value
	 * @param stepSize The step size
	 */
    IntegerSettingWidget(IntegerSetting *setting, QWidget* parent = 0);

private:
    IntegerSetting* _setting;

private slots:
    void forwardValue(int value);
    void reset();
};


