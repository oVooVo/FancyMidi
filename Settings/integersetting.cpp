#include <QApplication>
#include <QThread>
#include "integersetting.h"
#include "../Model/project.h"
#include <QDebug>

IntegerSetting::IntegerSetting(Node *parent, QString name, QString tooltip, int minValue, int maxValue, int defaultValue, int currentValue)
    : ScalarSetting<int>(parent, name, tooltip, minValue, maxValue, defaultValue, currentValue)
{
}

IntegerSetting::IntegerSetting(Node *parent, QString name, QString tooltip, int defaultValue, int currentValue)
    : ScalarSetting<int>(parent, name, tooltip, defaultValue, currentValue)
{
}

IntegerSetting::~IntegerSetting()
{
}


QDataStream &operator<<(QDataStream &out, const IntegerSetting *integerSetting)
{
//	out << QString("IntegerSetting");
//    out << integerSetting->name() << integerSetting->tooltip()
//		<< qint32(integerSetting->minValue()) << qint32(integerSetting->maxValue())
//		<< qint32(integerSetting->defaultValue()) << quint32(integerSetting->stepSize())
//		<< qint32(integerSetting->value());
    return out;
}

QDataStream &operator>>(QDataStream &in, IntegerSetting *&setting)
{
	QString name;
	QString tooltip;
	qint32 minValue;
	qint32 maxValue;
	qint32 defaultValue;
	qint32 currentValue;
	quint32 stepSize;

	in >> name;

	if(name == QString("IntegerSetting"))
	{
		in >> name;
	}
	in >> tooltip >> minValue >> maxValue >> defaultValue >> stepSize >> currentValue;

	//delete setting;
    setting = new IntegerSetting(NULL, name, tooltip, minValue, maxValue, defaultValue, currentValue);

	return in;
}
