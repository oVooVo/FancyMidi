#include <QApplication>
#include <QThread>
#include "boolsetting.h"

BoolSetting::BoolSetting(Node *parent, QString name, QString tooltip, bool defaultValue, bool currentValue):
    ScalarSetting(parent, name, tooltip, defaultValue, currentValue)
{
	Q_ASSERT_X(QApplication::instance()->thread() == QThread::currentThread(), "constructor", "called from a thread other than the main thread");
	_defaultValue = defaultValue;
    setValue(currentValue);
	setValid(true);
}

bool BoolSetting::defaultValue() const
{
	return _defaultValue;
}

QDataStream &operator>>(QDataStream &in, BoolSetting *&setting)
{
	QString name;
	QString tooltip;
	bool value;
	bool defaultValue;

	in >> name;

	if(name == QString("BoolSetting"))
	{
		in >> name;
	}
	in >> tooltip >> defaultValue >> value;

	setting = new BoolSetting(NULL, name, tooltip, defaultValue, value);

	return in;
}
QDataStream &operator<<(QDataStream &out, const BoolSetting *boolSetting)
{
	out << QString("BoolSetting");
    out << boolSetting->name() << boolSetting->tooltip() << boolSetting->defaultValue() << boolSetting->value();
	return out;
}
