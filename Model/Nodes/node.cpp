#include <QDebug> // debug
#include <QEvent>
#include <QApplication>
#include <QThreadPool>
#include <QThread>

#include "node.h"
#include "../inputport.h"
#include "../project.h"
#include <QCoreApplication>
#include "Settings/setting.h"

QMap<QString, Node* (*)(QDataStream&)> *Node::_creatorMap = 0;

Node::Node(QDataStream &stream)
{
    QList<Setting*> settings;
    stream >> _position >> _size >> _name >> _infoText >> settings;
    setSettings(settings);
}

void Node::writeToStream(QDataStream &stream) const
{
    stream << _position << _size << _name << _infoText << _settings.values();
}

Node::~Node()
{
    qDeleteAll(_inputs);
    qDeleteAll(_outputs);
}

const QList<OutputPort*> Node::outputPorts() const
{
    return _outputs.values();
}
const QList<InputPort*> Node::inputPorts() const
{
    return _inputs.values();
}

void Node::setPosition(QPoint position)
{
    if (position == _position) return;
    _position = position;
    if(getProject())
        getProject()->popularizeNodesChange();
}

QPoint Node::getPosition() const
{
	return _position;
}

const QList<Setting*> Node::settings() const
{
    return _settings.values();
}

Project* Node::getProject() {
    return qobject_cast<Project *>(parent());
}

QString Node::name() const
{
    return _name;
}

QString Node::getInfoText() const
{
    return _infoText;
}

void Node::polish()
{
    if(parent())
        QCoreApplication::sendEvent(parent(), new QChildEvent(QEvent::ChildPolished, this));
}

Node *Node::createInstance(QString className, QDataStream& stream)
{
    if (!_creatorMap) {
        _creatorMap = new QMap<QString, Node* (*)(QDataStream&)>();
    }

    QMap<QString, Node* (*)(QDataStream&)>::iterator it = _creatorMap->find(className);

    Q_ASSERT(it != _creatorMap->end());

    return (it.value())(stream);
}

Node *Node::createInstance(QString className)
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::ReadWrite);
    stream << QPoint() << QSize() << QString() << QString() << QList<Setting*>();
    return createInstance(className, stream);
}


QList<QString> Node::nodeClassnames() {
    QSet<QString> re;
    foreach(QString className, _creatorMap->keys()) {
        re += className;
    }
	QList<QString> list = re.toList();
	qSort(list);
    return list;
}

void Node::setSettings(QList<Setting *> settings)
{
    _settings.clear();
    for (Setting *setting : settings) {
        _settings.insert(setting->name(), setting);
        setting->setParent(this);
    }
}

void Node::clear()
{
	Q_ASSERT_X(QThreadPool::globalInstance()->activeThreadCount() == 0, "Node::clear()", "Called clear() while running.");
	Q_ASSERT_X(QApplication::instance()->thread() == QThread::currentThread(), "Node::clear()", "Called clear() from an other thread then the main thread.");
}

QSizeF Node::getSize() const
{
    return _size;
}

void Node::setSize(QSizeF size)
{
    if (size == _size) return;
    _size = size;
    if(getProject())
        getProject()->popularizeNodesChange();
}

void Node::addPort(Port *port)
{
    if (port->isInput()) {
        Q_ASSERT(!_inputs.contains(port->name()));
        _inputs.insert(port->name(), (InputPort*) port);
    } else {
        Q_ASSERT(!_outputs.contains(port->name()));
        _outputs.insert(port->name(), (OutputPort*) port);
        ((OutputPort*) port)->setBlock(_block);
    }
}

void Node::addSetting(Setting *setting)
{
    if (_settings.contains(setting->name())) {
        delete setting; //setting already exists (e.g. created from deserialization).
    } else {
        _settings.insert(setting->name(), setting);
    }
}

void Node::setBlock(bool block)
{
    _block = block;
    for (OutputPort* port : _outputs.values()) {
        port->setBlock(block);
    }
}

InputPort* Node::inputPort(QString key) const
{
    Q_ASSERT(_inputs.contains(key));
    return _inputs[key];
}

OutputPort* Node::outputPort(QString key) const
{
    Q_ASSERT(_outputs.contains(key));
    return _outputs[key];
}

void Node::setName(QString name)
{
    _name = name;
}

QDataStream &operator << (QDataStream &ostream, const Node *node)
{
    ostream << QString(node->metaObject()->className());
    node->writeToStream(ostream);
    return ostream;
}

QDataStream &operator >> (QDataStream &istream, Node *&node)
{
    QString classname;
    istream >> classname;
    node = Node::createInstance(classname, istream);
    return istream;
}

void Node::setParent(Project *project)
{
    connect(this, SIGNAL(newLogMessage(QString)), project, SIGNAL(newLogMessage(QString)));
    QObject::setParent(project);
}

bool Node::hasSettingsToDisplayInNode() const
{
    for (Setting* s : settings()) {
        if (s->showInNode())
            return true;
    }
    return false;
}




