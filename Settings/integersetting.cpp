#include <QApplication>
#include <QThread>
#include "integersetting.h"
#include "../Model/project.h"

IntegerSetting::IntegerSetting(Node *parent, QString name, QString tooltip, int minValue, int maxValue, int defaultValue, int stepSize, int currentValue):
	Setting(parent, name, tooltip)
{
	Q_ASSERT_X(QApplication::instance()->thread() == QThread::currentThread(), "constructor", "called from a thread other than the main thread");
	_minValue = minValue;
	_maxValue = maxValue;
	_value = currentValue;
	_value = qMax(_value, _minValue);
	_value = qMin(_value, _maxValue);
	_stepSize = stepSize;
	_defaultValue = defaultValue;
	setValid(true);
}

IntegerSetting::~IntegerSetting()
{
}
int IntegerSetting::value() const
{
	return _value;
}
int IntegerSetting::defaultValue() const
{
	return _defaultValue;
}

int IntegerSetting::minValue() const
{
	return _minValue;
}
int IntegerSetting::maxValue() const
{
	return _maxValue;
}
int IntegerSetting::stepSize() const
{
	return _stepSize;
}

void IntegerSetting::setValue(int value)
{
	Q_ASSERT_X(QApplication::instance()->thread() == QThread::currentThread(), "setValue", "called from a thread other than the main thread");
	value = qMax(value, _minValue);
	value = qMin(value, _maxValue);
    if ((value - _defaultValue)%_stepSize != 0) {	//not a correct value
        emitChanged();
    } else if (_value != value) {
		_value = value;
        emitChanged();
	}
}

void IntegerSetting::connectPort(Port *port)
{
    if (port->isInput()) {
        connect((InputPort*) port, &InputPort::receivedData, [this](QVariant data) {
            if (!data.canConvert(QVariant::Int)) return;
            setValue(data.value<int>());
        });
    }
}

QDataStream &operator<<(QDataStream &out, const IntegerSetting *integerSetting)
{
	out << QString("IntegerSetting");
	out << integerSetting->getName() << integerSetting->tooltip()
		<< qint32(integerSetting->minValue()) << qint32(integerSetting->maxValue())
		<< qint32(integerSetting->defaultValue()) << quint32(integerSetting->stepSize())
		<< qint32(integerSetting->value());
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
	setting = new IntegerSetting(NULL, name, tooltip, minValue, maxValue, defaultValue, stepSize, currentValue);

	return in;
}
