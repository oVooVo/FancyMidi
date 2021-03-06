#pragma once

#include <QSharedPointer>
#include "Nodes/node.h"
#include "packet.h"
#include "numbered.h"

/**
 * @brief The Port class is a abstract class to have common method shared between input and output port
 */
class Port : public QObject, public Numbered
{
    Q_OBJECT
public:
    enum Type { Trigger, Data, Other };
    /**
     * @brief Port Creates a port for a specific node
     * @param node The specific node
     * @param name The name of the port
     * @param infoText The text describing this port
     */
    Port(Node* node, QString name, QString infoText, Type type);
    virtual ~Port();

    /**
     * @brief connect Whether this port is connected to the given one
     * @param port The given port
     * @return Whether this port is connected to the given one
     */
    virtual bool connect(Port* port) = 0;
    /**
     * @brief isInput Whether this is a input port
     * @return Returns whether this is a input port
     */
    virtual bool isInput() const = 0;
    /**
     * @brief getNode Returns the associated node
     * @return Returns the associated node
     */
    Node* node() const;
    /**
     * @brief getName Returns the name of this port
     * @return Returns the name of this port
     */
    QString name() const;
    /**
     * @brief getInfoText Returns the text describing this port
     * @return Returns the text describing this port
     */
    QString infoText() const;

    Type type() const { return _type; }

    static bool canConnect(const Port *port1, const Port *port2);

    virtual void on_connect(Port*) {}

signals:
    void blink();


private:
    Node* _node;
    QString _name;
    QString _infoText;
    Type _type;
};











