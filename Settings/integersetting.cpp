#include <QApplication>
#include <QThread>
#include "integersetting.h"
#include "../Model/project.h"
#include <QDebug>

REGISTER_DEFN_SETTINGTYPE(IntegerSetting);

IntegerSetting::IntegerSetting(Node *parent, QString name, QString tooltip,
                               int minValue, int maxValue,
                               int defaultValue, int currentValue,
                               bool showInNode)
    : ScalarSetting<int>(parent, name, tooltip, minValue, maxValue, defaultValue, currentValue, showInNode)
{
}

IntegerSetting::IntegerSetting(Node *parent, QString name, QString tooltip,
                               int defaultValue, int currentValue,
                               bool showInNode)
    : ScalarSetting<int>(parent, name, tooltip, defaultValue, currentValue, showInNode)
{
}

IntegerSetting::IntegerSetting(QDataStream &stream)
    : ScalarSetting<int>(stream)
{

}

IntegerSetting::~IntegerSetting()
{
}

