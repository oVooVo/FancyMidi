#pragma once

#include "Nodes/node.h"
#include "packet.h"
#include "port.h"
#include <QVariant>

/**
 * @brief The InputPort class is a in going connection to a node
 * @see Port
 */
class InputPort : public Port
{
    Q_OBJECT
    /**
     * @brief InputPort Creates a InputPort for a specific node
     * @param node The specific node
     * @param name Name of the input port
     * @param infoText Text for the information about the input port
     */
protected:
    InputPort(Node* node, QString name, QString infoText, Type type);

public:
    ~InputPort();

    /**
     * @brief connect Connect this input port with an output port
     * @param port The output port to connect to
     * @return whether connection to the port worked
     */
    bool connect(Port* port);
    /**
     * @brief disconnect Whether detaching this port from a output port worked
     * @return Whether detaching this port from the node worked
     */
    bool disconnect();
    /**
     * @brief isInput Whether this port is a InputPort
     * @return Whether this port is a InputPort
     */
    bool isInput() const;

    /**
     * @brief getSource returns the OutputPort this port is connected with.
     * @return the OutputPort this port is connected with.
     */
    OutputPort* source() const;

protected:
    /**
     * @brief _source the OutputPorts that are connected to this InputPort.
     */
    OutputPort* _source;
};











