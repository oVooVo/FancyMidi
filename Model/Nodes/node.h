#pragma once
#include <QSet>
#include <QVector>
#include <QPoint>
#include <QSizeF>
#include <QMap>
#include <QString>
#include <QChildEvent>
#include <QCoreApplication>
#include <QDebug>
#include "numbered.h"
#include <QTimer>

class InputPort;
class OutputPort;
class Project;
class Setting;
class Port;

/**
 * @brief The Node class represents a module, containing the In/Output-Ports and the Settings
 */

class Node;
template<typename T> Node *createNode(QDataStream& stream) { return new T(stream); }

class Node:	public QObject
{

	Q_OBJECT
protected:
    Node() {}

public:
    /**
     * @brief setSettings adds given settings.
     * @param settings the settings of this node.
     */
    void setSettings(QList<Setting *> settings);

    /**
     * @brief Node Creates a new Node into given project.
     * @param position the position of the Node
     * @param parent the project this node is associated
     * @param name the name of this Node
     * @param infoText the tooltip
     * @param size the size of this Node.
     * @note only DisplayOutput has a size.
     */
    explicit Node(QDataStream& stream);
    virtual void writeToStream(QDataStream& stream) const;

    virtual ~Node();

    /**
     * @brief setPosition Sets the position of the node
     * @param position The new position
     */
    void setPosition(QPoint position);

    /**
     * @brief getPosition Returns the position
     * @return Returns the position
     */
    QPoint getPosition() const;

    /**
     * @brief getInputs Returns a 'list' of all input ports
     * @return Returns a 'list' of all input ports
     */
    const QList<InputPort*> inputPorts() const;

    /**
     * @brief getInputs Returns a 'list' of all output ports
     * @return Returns a 'list' of all output ports
     */
    const QList<OutputPort*> outputPorts() const;

    /**
     * @brief getSettings Returns the settings from this node
     * @return Returns the settings
     */
    const QList<Setting *> settings() const;

    /**
     * @brief getProject Returns the Project
     * @return Returns the Project
     */
    Project *getProject();

    /**
     * @brief getName Returns the name of the node
     * @return Returns the name of the node
     */
    QString name() const;

    /**
     * @brief getInfoText Returns a text describing this node
     * @return Returns a text describing this node
     */
    QString getInfoText() const;

    /**
     * @brief createInstance creates a new instance of a node with given classname.
     * @param className the new node's type.
     * @return a new instance of a node with given classname.
     */
    static Node *createInstance(QString className); // for drag & drop
    static Node *createInstance(QString className, QDataStream &stream);    // for deserialization
    static QList<QString> nodeClassnames();

    virtual void clear();

    /**
     * @brief getSize returns the size of this node.
     * @return the size of this node.
     * @note only DisplayOutput has a size.
     */
    QSizeF getSize() const;

    /**
     * @brief setSize sets the size of this node.
     * @note only DisplayOutput has a size.
     */
    void setSize(QSizeF size);

    virtual QString category() const { return "NoCategory"; }

    /**
     * @brief must be called as the last function of child constructor. Sends polish-event (= construction done)
     */
    void polish();

    void setParent(Project* project);

    bool hasSettingsToDisplayInNode() const;

public slots:
    void start();
    void stop();

protected:
    void addPort(Port* port);
    void addSetting(Setting* setting);
    void registerTimer(QTimer* timer);
    InputPort* inputPort(QString key) const;
    OutputPort* outputPort(QString key) const;
    template<typename T> T* setting(QString key) const
    {
        Q_ASSERT(_settings.contains(key));

        return (T*) _settings[key];
    }
    void setName(QString name);


    /**
     * @brief _creatorMap this map contains all nodes.
     */
    static QMap<QString, Node* (*)(QDataStream&)> *_creatorMap;

    void setBlock(bool block);
    bool block() const { return _block; }

private:
    QMap<QString, InputPort*> _inputs;
    QMap<QString, OutputPort*> _outputs;
    QMap<QString, Setting*> _settings;
    QList<QTimer*> _timer;              // timers that can be startet and stopped via Node::start() and Node::stop()
    QPoint _position;
    QString _name;
    QString _infoText;
    QSizeF _size;
    bool _block = false;
    int _num_outputs = 0;
    int _num_inputs = 0;
    int _num_settings = 0;

    template<typename T>
    static QList<T> sort(QList<T> setting);

signals:
    void newLogMessage(QString);
};

template<typename T>
struct NodeRegister : Node
{
    NodeRegister(QString className) : Node()
	{
		if (!_creatorMap)
            _creatorMap = new QMap<QString, Node* (*)(QDataStream&)>();
        _creatorMap->insert(className, &createNode<T>);
	}
};

#define REGISTER_DECL_NODETYPE(CLASSNAME) \
private:    \
    static NodeRegister<CLASSNAME> reg

#define REGISTER_DEFN_NODETYPE(CLASSNAME) \
	NodeRegister<CLASSNAME> CLASSNAME::reg(#CLASSNAME)

QDataStream &operator << (QDataStream &ostream, const Node *node);
QDataStream &operator >> (QDataStream &istream, Node *&node);













