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
    foreach (InputPort *p, _inputs)
        delete p;
    foreach (OutputPort *p, _outputs)
        delete p;
}

const QList<OutputPort*> Node::getOutputs()
{
	return _outputs;
}
const QList<InputPort*> Node::getInputs()
{
	return _inputs;
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

const QVector<Setting*> Node::getSettings() const
{
	return _settings;
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

void Node::childEvent(QChildEvent *event)
{
    if(event->polished() || event->added()) {
        
        Setting* newSetting = (Setting*)event->child();
        if(!_settings.contains(newSetting))
            _settings += newSetting;
    }
    else
    {
        _settings.remove(_settings.indexOf((Setting*)event->child()));
    }
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
    ostream << className << node->getPosition() << node->getSize() << node->getSettings();
    return ostream;
}

QDataStream &operator >> (QDataStream &istream, Node *&node)
{
    QString className;
    QPoint position;
    QSizeF size;
    QVector<Setting*> settings;

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
void Node::setSettings(QVector<Setting *> settings)
{
    _settings.clear();

    _settings = settings;

    for (Setting *setting : _settings) {
        //qDebug() << setting->getName() << " "<< _settings.size();
        setting->setParent(this);
    }
}

void Node::clear()
{
	Q_ASSERT_X(QThreadPool::globalInstance()->activeThreadCount() == 0, "Node::clear()", "Called clear() while running.");
	Q_ASSERT_X(QApplication::instance()->thread() == QThread::currentThread(), "Node::clear()", "Called clear() from an other thread then the main thread.");
    _newSettings = true;
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






