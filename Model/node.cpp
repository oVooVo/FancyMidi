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

/// <summary>
/// Initializes a new instance of the <see cref="Node" /> class.
/// </summary>
/// <param name="position">The position.</param>
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

/// <summary>
/// Gets the position.
/// </summary>
/// <returns></returns>
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

// TODO: 32 bytes in 1 blocks are definitely lost in loss record 3,761 of 11,810
//    in Node::polish() in node.cpp:161
//    1: operator new(unsigned long) in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so
//    2: Node::polish() in <a href="file:///home/ksiks/Workspace/PSE/svn_fuceekay/main/implementierungsphase/video2k/video2k-build-Desktop-Debug/../video2k/node.cpp:161" >node.cpp:161</a>
//    3: DisplayOutput::DisplayOutput(QPoint, Project*) in <a href="file:///home/ksiks/Workspace/PSE/svn_fuceekay/main/implementierungsphase/video2k/video2k-build-Desktop-Debug/../video2k/displayoutput.cpp:9" >displayoutput.cpp:9</a>
//    4: NodeTest::run() in <a href="file:///home/ksiks/Workspace/PSE/svn_fuceekay/main/implementierungsphase/video2k/video2k-build-Desktop-Debug/../video2k/nodetest.cpp:87" >nodetest.cpp:87</a>
//    5: NodeTest::qt_static_metacall(QObject*, QMetaObject::Call, int, void**) in <a href="file:///home/ksiks/Workspace/PSE/svn_fuceekay/main/implementierungsphase/video2k/video2k-build-Desktop-Debug/moc_nodetest.cpp:63" >/home/ksiks/Workspace/PSE/svn_fuceekay/main/implementierungsphase/video2k/video2k-build-Desktop-Debug/moc_nodetest.cpp:63</a>
//    6: QMetaMethod::invoke(QObject*, Qt::ConnectionType, QGenericReturnArgument, QGenericArgument, QGenericArgument, QGenericArgument, QGenericArgument, QGenericArgument, QGenericArgument, QGenericArgument, QGenericArgument, QGenericArgument, QGenericArgument) const in /usr/lib/libQtCore.so.4.8.4
//    7: QMetaObject::invokeMethod(QObject*, char const*, Qt::ConnectionType, QGenericReturnArgument, QGenericArgument, QGenericArgument, QGenericArgument, QGenericArgument, QGenericArgument, QGenericArgument, QGenericArgument, QGenericArgument, QGenericArgument, QGenericArgument) in /usr/lib/libQtCore.so.4.8.4
//    8: /usr/lib/libQtTest.so.4.8.4
//    9: QTest::qExec(QObject*, int, char**) in /usr/lib/libQtTest.so.4.8.4
//    10: QTestUnit::QTestUnit() in <a href="file:///home/ksiks/Workspace/PSE/svn_fuceekay/main/implementierungsphase/video2k/video2k-build-Desktop-Debug/../video2k/qtestunit.cpp:117" >qtestunit.cpp:117</a>
//    11: main in <a href="file:///home/ksiks/Workspace/PSE/svn_fuceekay/main/implementierungsphase/video2k/video2k-build-Desktop-Debug/../video2k/main.cpp:13" >main.cpp:13</a>

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
    if (!_creatorMap)
    {
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

    foreach(Setting *setting, _settings)
    {
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

bool Node::isModifying(InputPort *port)
{
    if (_inputs.size() == 0 || inherits("Output"))
        return false;
    return port == _inputs.first();
}
