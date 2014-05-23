#pragma once

#include <QString>
#include "setting.h"
#include "../Model/node.h"

/**
 * @brief The IntegerSetting class is the model of handling integer based preferences
 * @see Setting
 */
class IntegerSetting:
	public Setting
{

Q_OBJECT

public:
    /**
     * @brief IntegerSetting Creates a IntegerSetting with the given information
     * @param parent the Node this Setting is used in.
     * @param name the name of this setting.
     * @param tooltip a short description of this setting.
     * @param minValue The minimum value of this setting
     * @param maxValue The maximum value of this setting
     * @param defaultValue the default value of this setting.
     * @param stepSize The step size of this setting.
     */
    IntegerSetting(Node *parent, QString name, QString tooltip, int minValue, int maxValue, int defaultValue, int stepSize, int currentValue);
    ~IntegerSetting();

    /**
     * @brief getValue Get the currently used value
     * @return Returns the currently used value
     */
    int value() const;

    /**
     * @brief getValue Get the default value
     * @return Returns the default value
     */
    int defaultValue() const;

    /**
     * @brief getMinValue Get the minimal value
     * @return Returns the minimal value
     */
    int minValue() const;

    /**
     * @brief getMaxValue Get the maximal value
     * @return Returns the maximal value
    */
    int maxValue() const;

    /**
     * @brief getStepSize Get the default value
     * @return Returns the default value
    */
    int stepSize() const;

    void connectPort(Port* port);

public slots:
    /**
     * @brief setValue sets the value of this setting to the given value.
     * @param value the value on that is this setting set to.
     */
    void setValue(int value);

private:
    Q_DISABLE_COPY(IntegerSetting)
    int _minValue;
    int _maxValue;
    int _stepSize;
    int _value;
    int _defaultValue;
};
QDataStream &operator<<(QDataStream &out, const IntegerSetting *setting);
QDataStream &operator>>(QDataStream &in, IntegerSetting *&setting);
