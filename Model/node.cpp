#include <QDebug> // debug
#include <QEvent>
#include <QApplication>
#include <QThreadPool>
#include <QThread>

#include "node.h"
#include "inputport.h"
#include "project.h"
#include <QCoreApplication>
#include "Settings/setting.h"

QMap<QString, Node* (*)(QPoint, Project*)> *Node::_creatorMap = 0;

Node::Node(QPoint position, Project* parent, QString name, QString infoText, QSizeF size)
{
    setParent(parent);
	_position = position;
    _size = size;
    _name = name;
    _infoText = infoText;
    _state = GOOD;
}

Node::~Node()
{
    qDeleteAll(_inputs);
    qDeleteAll(_outputs);
}

const QList<OutputPort*> Node::getOutputs()
{
    return _outputs.values();
}
const QList<InputPort*> Node::getInputs()
{
    return _inputs.values();
}

void Node::selfCheck()
{
	foreach (Setting* setting, _settings)
        if(!setting->isValid())
            _state = RED;
}

Node::STATE Node::getState()
{
    return _state;
}

void Node::setState(STATE state)
{
    _state = state;
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

QString Node::getName() const
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

Node *Node::createInstance(QString className)
{
    if (!_creatorMap) {
        _creatorMap = new QMap<QString, Node* (*)(QPoint, Project*)>();
    }

    QMap<QString, Node* (*)(QPoint, Project*)>::iterator it = _creatorMap->find(className);
    if (it == _creatorMap->end())
        return 0;

    return (it.value())(QPoint(), 0);
}

QDataStream &operator << (QDataStream &ostream, const Node *node)
{
    //qDebug() << "operator <<: metaObject class name: " << node->metaObject()->className();
    QString className = QString(node->metaObject()->className());
    ostream << className << node->getPosition() << node->getSize() << node->settings();
    return ostream;
}

QDataStream &operator >> (QDataStream &istream, Node *&node)
{
    QString className;
    QPoint position;
    QSizeF size;
    QList<Setting*> settings;

    istream >> className;
    if(className.isEmpty()) {
        node = 0;
        return istream;
    }
    istream >> position;
    istream >> size;
    istream >> settings;

    node = Node::createInstance(className);
    node->setPosition(position);
    node->setSize(size);

    //qDebug() << "operator <<: metaObject class name: " << node->metaObject()->className();

    node->setSettings(settings);
    return istream;
}

QList<QString> Node::getModuleClassNames() {
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
        //qDebug() << setting->getName() << " "<< _settings.size();
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
    Q_ASSERT(!_settings.contains(setting->name()));
    _settings.insert(setting->name(), setting);
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





