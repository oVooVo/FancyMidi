#pragma once

#include <QString>
#include <QCheckBox>
#include "../Settings/boolsetting.h"
#include "settingwidget.h"
#include "ui_boolsettingwidget.h"

class BoolSettingWidgetTest;

/**
 * @brief The BoolSettingWidget class provides a graphical user interface for the BoolSetting class.
 * @see SettingWidget
 * @see BoolSetting
 */
class BoolSettingWidget : public SettingWidget, private Ui::BoolSettingWidget
{
	Q_OBJECT
    REGISTER_DECL_SETTINGWIDGETTYPE(BoolSettingWidget);

public:
    /**
     * @brief BoolSettingWidget creates a new BoolSettingWidget out of a given BoolSetting and optionally a parent.
     * @param setting the chef of this widget.
     * @param parent the parent of this widget.
     */
    BoolSettingWidget(Setting *setting, QWidget* parent = 0);

    /**
     * @brief ~BoolSettingWidget destroys this BoolSettingWidget.
     */
    virtual ~BoolSettingWidget() {}

private slots:
    void reset();


};


