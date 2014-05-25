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

    /**
     * @brief ~BoolSetting destroys this BoolSetting.
     */
    virtual ~BoolSetting() {}

	/**
	 * @brief value returns the  default value of this setting
	 * @return the default value of this setting. Is either true or false.
	 */
	bool defaultValue() const;

public slots:
    void setValue(bool value) { ScalarSetting<bool>::setValue(value); }

private:
	bool _defaultValue;
};

QDataStream &operator<<(QDataStream &out, const BoolSetting *setting);
QDataStream &operator>>(QDataStream &in, BoolSetting *&setting);


