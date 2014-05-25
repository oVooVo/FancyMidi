#include "selectsetting.h"
#include <QThread>
#include <QApplication>
#include <QDebug>

SelectSetting::SelectSetting(Node *parent, QString name, QString tooltip, int currentIndex,
                             QList<QString> values, int defaultIndex)
    : Setting(parent, name, tooltip)
{
	_values = values;
	_currentIndex = currentIndex;
	_defaultIndex = defaultIndex;
	setValid(true);
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

QDataStream &operator<<(QDataStream &out, const SelectSetting *selectSetting)
{
	out << QString("SelectSetting");
    out << selectSetting->name() << selectSetting->tooltip() <<
           qint32(selectSetting->currentIndex())
		<< selectSetting->values() << qint32(selectSetting->defaultIndex());
    return out;
}

QDataStream &operator>>(QDataStream &in, SelectSetting *&setting)
{
	QString name;
	QString tooltip;
	qint32 currentEntry;
	qint32 defaultEntry;
	QList<QString> values;

	in >> name;
    if (name == QString("SelectSetting")) {
		in >> name ;
    }

	in >> tooltip >> currentEntry >> values >> defaultEntry;

	setting = new SelectSetting(NULL, name, tooltip, currentEntry, values, defaultEntry);

	return in;
}
