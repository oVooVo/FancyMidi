#pragma once

#include <QComboBox>
#include <QString>
#include <QList>
#include "../Settings/selectsetting.h"
#include "settingwidget.h"
#include "ui_selectsettingwidget.h"
/**
 * @brief The SelectSettingWidget class provides a graphical user interface for the SelectSetting.
 */
class SelectSettingWidget: public SettingWidget, private Ui::SelectSettingWidget
{
	Q_OBJECT
public:
	/**
	 * @brief SelectSettingWidget Creates a SelectSetting Widget, based on the settings of a Selectsetting
	 * @param list The list of the selectSetting
	 * @param index the current item of the selectSetting
	 * @param tooltip The tooltip of the selectSetting
	 */
    SelectSettingWidget(SelectSetting* setting, QWidget *parent = 0);

private:
    SelectSetting* _setting;

private slots:
    void forwardValue(int currentIndex);
    void reset();
};


