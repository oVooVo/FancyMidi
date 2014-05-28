#include <QThread>
#include <QApplication>
#include <QThreadPool>
#include <QDebug>
#include "setting.h"

#include "Model/project.h"

QMap<QString, Setting* (*)(QDataStream&)> *Setting::_creatorMap = 0;


Setting::Setting(Node *parent, QString name, QString tooltip, bool showInNode):
	QObject(parent)
{
	_name = name;
    _tooltip = tooltip;
    _showInNode = showInNode;
}

Setting::Setting(QDataStream& stream)
{
    int number;
    stream >> _name >> _tooltip >> _showInNode >> number;
    setNumber(number);
}

void Setting::writeToStream(QDataStream& stream) const
{
    stream << _name << _tooltip << _showInNode << number();
}


Setting::~Setting()
{
}

const QString Setting::name() const
{
	return _name;
}

const QString Setting::tooltip() const
{
    return _tooltip;
}

QDataStream &operator<<(QDataStream &out, const Setting *setting)
{
    out << QString(setting->metaObject()->className());
    setting->writeToStream(out);
    return out;
}

QDataStream &operator>>(QDataStream &in, Setting *&setting)
{
    QString classname;
    in >> classname;
    setting = Setting::createInstance(classname, in);
    return in;
}

Setting *Setting::createInstance(QString className, QDataStream &stream)
{
    if (!_creatorMap) {
        _creatorMap = new QMap<QString, Setting* (*)(QDataStream&)>();
    }

    QMap<QString, Setting* (*)(QDataStream&)>::iterator it = _creatorMap->find(className);

    Q_ASSERT(it != _creatorMap->end());

    return (it.value())(stream);
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
