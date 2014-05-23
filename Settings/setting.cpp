#include <QThread>
#include <QApplication>
#include <QThreadPool>
#include <QDebug>
#include "setting.h"

#include "Model/project.h"

Setting::Setting(Node *parent, QString name, QString tooltip):
	QObject(parent)
{
	Q_ASSERT_X(QApplication::instance()->thread() == QThread::currentThread(), "constructor", "called from a thread other than the main thread");
	_name = name;
    _tooltip = tooltip;
    _isValid = false;
}

Setting::~Setting()
{
}

bool Setting::isValid() const
{
    return _isValid;
}

const QString Setting::getName() const
{
	return _name;
}
const QString Setting::tooltip() const
{
    return _tooltip;
}

void Setting::setValid(bool valid)
{
    if (valid != _isValid) {
        _isValid = valid;
        if (node() && node()->getProject()) {
            node()->getProject()->popularizeNodesChange();
        }
        emit validChange();
    }
}

QDataStream &operator<<(QDataStream &out, const Setting *setting)
{
/*
	if (setting->inherits("IntegerSetting"))
	{
		out << (const IntegerSetting *&) setting;

    } else if (setting->inherits("ResolutionPathSetting"))
	{
        out << (const ResolutionPathSetting *&) setting;

	} else if (setting->inherits("SelectSetting"))
	{
		out << (const SelectSetting *&) setting;

	} else if (setting->inherits("BoolSetting"))
	{
		out << (const BoolSetting *&) setting;
	} else if (setting->inherits("ColorSetting"))
	{
		out << (const ColorSetting *&) setting;
	}
*/
	return out;
}

QDataStream &operator>>(QDataStream &in, Setting *&setting)
{
/*
	QString className;
	in >> className;

	if (className == QString("IntegerSetting"))
	{
		in >> (IntegerSetting *&) setting;

    } else if (className == QString("ResolutionPathSetting"))
	{
        in >> (ResolutionPathSetting *&) setting;

	} else if (className == QString("SelectSetting"))
	{
		in >> (SelectSetting *&) setting;

	} else if (className == QString("BoolSetting"))
	{
		in >> (BoolSetting *&) setting;
	} else if (className == QString("ColorSetting"))
	{
		in >> (ColorSetting *&) setting;
	}
    */
	return in;
}

Node* Setting::node() {
    if (parent() == 0) return 0;
    return (Node*) parent();
}

void Setting::emitChanged()
{
    if(node() && node()->getProject())
        node()->getProject()->setSaved(false);
    emit changed();
}
