#pragma once

#include <QSharedPointer>
#include "node.h"
#include "packet.h"

/**
 * @brief The Port class is a abstract class to have common method shared between input and output port
 */
class Port : public QObject
{
    Q_OBJECT
public:
    enum Type { Trigger, Scalar, Other };
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
    Node* getNode() const;
    /**
     * @brief getName Returns the name of this port
     * @return Returns the name of this port
     */
    QString getName() const;
    /**
     * @brief getInfoText Returns the text describing this port
     * @return Returns the text describing this port
     */
    QString getInfoText() const;

    /**
     * @brief isData returns whether this port represents a data port.
     * @return whether this port represents a data port.
     */
    Type type() const;

private:
    Node* _node;
    QString _name;
    QString _infoText;
    Type _type;
};











