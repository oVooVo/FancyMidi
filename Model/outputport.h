#pragma once

#include <QSet>
#include "port.h"
#include "inputport.h"

/**
 * @brief The OutputPort class is a outgoing connection from a node
 * @see Port
 */
class OutputPort:public Port
{
public:
    /**
     * @brief OutputPort Creates a OutputPort for a specific node
     * @param node The specific node
     * @param name The name of the output port
     * @param infoText Text for the information about the output port
     */
    OutputPort(Node* node, QString name, QString infoText, bool isData = false);
    /**
     * @brief getTargets Returns a list of connected input ports
     * @return Returns a list of connected input ports
     */
    ~OutputPort();

    const QSet<InputPort*> getTargets();
    /**
     * @brief pushPacket Pushes the packet to all connected port
     * @param packet The packet to be pushed
     * @warning Copies of the packet might be created if necessary
     */
    void pushPacket(QSharedPointer<Packet> packet);
    /**
     * @brief connect Whether this port is connected with the given port
     * @param port The given port
     * @return Whether this port is connected with the given port
     */
    bool connect(Port* port);
    /**
     * @brief Disconnect Whether disconnecting from the given input port was successful
     * @param port The given input port
     * @return Whether disconnecting from the given input port was successful
     */
    bool disconnect(InputPort* port);
    /**
     * @brief isInput Whether this is a input port
     * @return Whether this is a input port
     */
    bool isInput();

private:
    QSet<InputPort*> _targets;
};











