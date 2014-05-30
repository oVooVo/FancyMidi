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
#include "../datainputport.h"

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
    return sort(_outputs.values());

}
const QList<InputPort*> Node::inputPorts() const
{
    return sort(_inputs.values());
}

const QList<Setting*> Node::settings() const
{
    return sort(_settings.values());
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


Project* Node::getProject() {
    return qobject_cast<Project *>(parent());
}

QString Node::name() const
{
    if (_name.isEmpty())
        return metaObject()->className();
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
        port->setNumber(_num_inputs++);
    } else {
        Q_ASSERT(!_outputs.contains(port->name()));
        _outputs.insert(port->name(), (OutputPort*) port);
        ((OutputPort*) port)->setBlock(_block);
        port->setNumber(_num_outputs++);
    }
}

void Node::addSetting(Setting *setting)
{
    if (_settings.contains(setting->name())) {
        delete setting; //setting already exists (e.g. created from deserialization).
    } else {
        _settings.insert(setting->name(), setting);
        setting->setNumber(_num_settings++);
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

DataInputPort* Node::dataInputPort(QString key) const
{
    Q_ASSERT(inputPort(key)->type() == Port::Data);
    return (DataInputPort*) inputPort(key);
}

TriggerInputPort* Node::triggerInputPort(QString key) const
{
    Q_ASSERT(inputPort(key)->type() == Port::Trigger);
    return (TriggerInputPort*) inputPort(key);
}

OutputPort* Node::outputPort(QString key) const
{
    Q_ASSERT(_outputs.contains(key));
    return _outputs[key];
}

DataOutputPort *Node::dataOutputPort(QString key) const
{
    Q_ASSERT(outputPort(key)->type() == Port::Data);
    return (DataOutputPort*) outputPort(key);
}

TriggerOutputPort *Node::triggerOutputPort(QString key) const
{
    Q_ASSERT(outputPort(key)->type() == Port::Trigger);
    return (TriggerOutputPort*) outputPort(key);
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

template<typename T>
QList<T> merge(QList<T> a, QList<T> b)
{
    QList<T> m;
    while (!a.isEmpty() || !b.isEmpty()) {
        if (b.isEmpty() || a.isEmpty()) {
            m.append(b);
            m.append(a);
            break;
        }
        if (a.first()->number() < b.first()->number()) {
            m.append(a.takeFirst());
        } else {
            m.append(b.takeFirst());
        }
    }
    return m;
}

template<typename T>
QList<T> Node::sort(QList<T> list)
{
    if (list.size() <= 1)
        return list;

    QList<T> left  = sort(list.mid(0, list.length() / 2));
    QList<T> right = sort(list.mid(list.length() / 2));
    return merge(left, right);
}

void Node::start()
{
    for (QTimer* timer : _timer)
        timer->start();
}

void Node::stop()
{
    for (QTimer* timer : _timer)
        timer->stop();
}

void Node::registerTimer(QTimer *timer)
{
    _timer.append(timer);
}



