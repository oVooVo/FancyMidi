#include <QThread>
#include <QApplication>
#include <QThreadPool>
#include <QDebug>
#include "setting.h"

#include "Model/project.h"

QMap<QString, Setting* (*)(QDataStream&)> *Setting::_creatorMap = 0;


Setting::Setting(Node *parent, QString name, QString tooltip):
	QObject(parent)
{
	_name = name;
    _tooltip = tooltip;
}

Setting::Setting(QDataStream& stream)
{
    stream >> _name >> _tooltip >> _isValid;
}

void Setting::writeToStream(QDataStream& stream) const
{
    stream << _name << _tooltip << _isValid;
}


Setting::~Setting()
{
}

bool Setting::isValid() const
{
    return true;
}

const QString Setting::name() const
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
    out << QString(setting->metaObject()->className());
    qDebug() << "write " << QString(setting->metaObject()->className());
    setting->writeToStream(out);
    return out;
}

QDataStream &operator>>(QDataStream &in, Setting *&setting)
{
    QString classname;
    in >> classname;
    qDebug() << "read " << classname;
    setting = Setting::createInstance(classname, in);
    return in;
}

Setting *Setting::createInstance(QString className, QDataStream &stream)
{
    if (!_creatorMap) {
        _creatorMap = new QMap<QString, Setting* (*)(QDataStream&)>();
    }

    QMap<QString, Setting* (*)(QDataStream&)>::iterator it = _creatorMap->find(className);

    qDebug() << _creatorMap->contains(className);

    qDebug() << className;
    qDebug() << *_creatorMap;
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
