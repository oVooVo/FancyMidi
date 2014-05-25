#pragma once

#include <QString>
#include "scalarsetting.h"
#include "../Model/node.h"

/**
 * @brief The IntegerSetting class is the model of handling integer based preferences
 * @see Setting
 */
class IntegerSetting:
    public ScalarSetting<int>
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
    IntegerSetting(Node *parent, QString name, QString tooltip, int minValue, int maxValue, int defaultValue, int currentValue);
    ~IntegerSetting();
    IntegerSetting(Node *parent, QString name, QString tooltip, int defaultValue, int currentValue);

};
QDataStream &operator<<(QDataStream &out, const IntegerSetting *setting);
QDataStream &operator>>(QDataStream &in, IntegerSetting *&setting);
