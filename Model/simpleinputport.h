#pragma once

#include "inputport.h"

/**
 * @brief The SimpleInputPort class is a variant of the InputPort class just providing a input port in its basic means
 * @see InputPort
 */
class SimpleInputPort:
	public InputPort
{

public:
    /**
     * @brief SimpleInputPort Creates a SimpleInputPort for a given node with a given name and a description
     * @param node The given node
     * @param name THe name of this port
     * @param infoText THe description of the port
     */
    SimpleInputPort(Node* node, QString name, QString infoText, Type type);
    /**
     * @brief pushPacket Notifies the node that a new packet arose
     * @param packet the new packet
     */
    void pushPacket(QSharedPointer<Packet> packet);

    /**
     * @brief ~SimpleInputPort destroys this SimpleInputPort.
     */
    virtual ~SimpleInputPort() {}
};











