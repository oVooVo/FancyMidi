#pragma once

#include "scalarsetting.h"

/**
 * @brief The BoolSetting class provides a boolean value.
 */
class BoolSetting : public ScalarSetting<bool>
{
	Q_OBJECT

public:
	/**
	 * @brief BoolSetting creates a new BoolSetting out of a parental Node, its name, tooltip and default value.
	 * @param parent the Node this Setting is used in.
	 * @param name the name of this setting.
	 * @param tooltip a short description of this setting.
	 * @param defaultValue the default value of this setting.
	 */
	BoolSetting(Node *parent, QString name, QString tooltip, bool defaultValue, bool currentValue);
    BoolSetting(QDataStream& stream);

    /**
     * @brief ~BoolSetting destroys this BoolSetting.
     */
    virtual ~BoolSetting() {}

public slots:
    void setValue(bool value) { ScalarSetting<bool>::setValue(value); }

    REGISTER_DECL_SETTINGTYPE(BoolSetting);
};
