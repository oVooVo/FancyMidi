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

class InputPort;
class OutputPort;
class Project;
class Setting;
class Port;

/**
 * @brief The Node class represents a module, containing the In/Output-Ports and the Settings
 */

class Node;
template<typename T> Node *createT(QPoint position, Project *parent) { return new T(position, parent); }

class Node:	public QObject
{

	Q_OBJECT

public:
    /**
     * @brief The STATE enum represents the state of a node. GOOD means everything okay, ERROR means there is an error, eg.
     *      wrong configurated Setting and DEAD means the node has directly or indirectly no successor or predecessor.
     */
    enum STATE {GOOD, RED, DEAD};

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
    explicit Node(QPoint position, Project* parent, QString name, QString infoText = "", QSizeF size = QSizeF(0,0));

    virtual ~Node();

    /**
     * @brief selfCheck Checks whether the node is in a valid state
     */
    void selfCheck();

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
    const QList<InputPort*> getInputs();

    /**
     * @brief getInputs Returns a 'list' of all output ports
     * @return Returns a 'list' of all output ports
     */
    const QList<OutputPort*> getOutputs();

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
    QString getName() const;

    /**
     * @brief getInfoText Returns a text describing this node
     * @return Returns a text describing this node
     */
    QString getInfoText() const;

    /**
     * @brief getState returns the state of this node.
     * @return the state of this node.
     */
    STATE getState();

    /**
     * @brief setState Sets the state of this node.
     * @param state The state to set this one to.
     */
    void setState(STATE state);

    /**
     * @brief createInstance creates a new instance of a node with given classname.
     * @param className the new node's type.
     * @return a new instance of a node with given classname.
     */
    static Node *createInstance(QString className);

    /**
     * @brief getModuleClassNames returns all registred class names.
     * @return all registred class names.
     */
    static QList<QString> getModuleClassNames();

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

protected:
    void addPort(Port* port);
    void addSetting(Setting* setting);
    InputPort* inputPort(QString key) const;
    OutputPort* outputPort(QString key) const;
    template<typename T> T* setting(QString key) const
    {
        Q_ASSERT(_settings.contains(key));

        return (T*) _settings[key];
    }


    /**
     * @brief _creatorMap this map contains all nodes.
     */
    static QMap<QString, Node* (*)(QPoint, Project*)> *_creatorMap;

    /**
     * @brief _state contains the status of this node.
     */
    STATE _state;

    void setBlock(bool block);
    bool block() const { return _block; }

private:
    QMap<QString, InputPort*> _inputs;
    QMap<QString, OutputPort*> _outputs;
    QMap<QString, Setting*> _settings;
    QPoint _position;
    QString _name;
    QString _infoText;
    QSizeF _size;
    bool _block = false;
};

template<typename T>
struct NodeRegister : Node
{
	NodeRegister(QString className) : Node(QPoint(), 0, QString(""), QString(""))
	{
		if (!_creatorMap)
            _creatorMap = new QMap<QString, Node* (*)(QPoint, Project*)>();
        _creatorMap->insert(className, &createT<T>);
	}
};

#define REGISTER_DECL_NODETYPE(CLASSNAME) \
private:    \
	static NodeRegister<CLASSNAME> reg

#define REGISTER_DEFN_NODETYPE(CLASSNAME) \
	NodeRegister<CLASSNAME> CLASSNAME::reg(#CLASSNAME)

QDataStream &operator << (QDataStream &ostream, const Node *node);
QDataStream &operator >> (QDataStream &istream, Node *&node);













