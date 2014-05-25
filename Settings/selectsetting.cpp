#include "selectsetting.h"
#include <QThread>
#include <QApplication>
#include <QDebug>

REGISTER_DEFN_SETTINGTYPE(SelectSetting);

SelectSetting::SelectSetting(Node *parent, QString name, QString tooltip, int currentIndex,
                             QList<QString> values, int defaultIndex)
    : Setting(parent, name, tooltip)
{
	_values = values;
	_currentIndex = currentIndex;
	_defaultIndex = defaultIndex;
}

SelectSetting::SelectSetting(QDataStream& stream)
    : Setting(stream)
{
    stream >> _values >> _currentIndex >> _defaultIndex;
}

void SelectSetting::writeToStream(QDataStream &stream) const
{
    Setting::writeToStream(stream);
    stream << _values << _currentIndex << _defaultIndex;
}

SelectSetting::~SelectSetting()
{
}

const QList<QString> SelectSetting::values() const
{
	return _values;
}

int SelectSetting::currentIndex() const
{
	return _currentIndex;
}

int SelectSetting::defaultIndex() const
{
	return _currentIndex;
}

void SelectSetting::setCurrentIndex(int index)
{
    if((_values.length() > index) && (index >= 0) && _currentIndex != index)
    {
        _currentIndex = index;
        emitChanged();
    }
}
