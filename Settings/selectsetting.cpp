#include "selectsetting.h"
#include <QThread>
#include <QApplication>
#include <QDebug>

REGISTER_DEFN_SETTINGTYPE(SelectSetting);

SelectSetting::SelectSetting(Node *parent, QString name, QString tooltip, int currentIndex,
                             QList<QString> values, int defaultIndex, bool showInNode)
    : ScalarSetting<int>(parent, name, tooltip, 0, values.length() - 1, currentIndex, defaultIndex, showInNode)
{
    _values = values;
}

SelectSetting::SelectSetting(QDataStream& stream)
    : ScalarSetting(stream)
{
    stream >> _values;
}

void SelectSetting::writeToStream(QDataStream &stream) const
{
    ScalarSetting::writeToStream(stream);
    stream << _values;
}

SelectSetting::~SelectSetting()
{
}

const QList<QString> SelectSetting::values() const
{
	return _values;
}
