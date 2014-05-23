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
    REGISTER_DECL_SETTINGWIDGETTYPE(SelectSettingWidget);
public:
	/**
	 * @brief SelectSettingWidget Creates a SelectSetting Widget, based on the settings of a Selectsetting
	 * @param list The list of the selectSetting
	 * @param index the current item of the selectSetting
	 * @param tooltip The tooltip of the selectSetting
	 */
    SelectSettingWidget(Setting *set, QWidget *parent = 0);

private slots:
    void reset();


};



