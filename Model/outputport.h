#pragma once

#include <QSet>
#include "port.h"
#include "inputport.h"
#include <QVariant>

/**
 * @brief The OutputPort class is a outgoing connection from a node
 * @see Port
 */
class OutputPort : public Port
{
    Q_OBJECT
public:
    /**
     * @brief OutputPort Creates a OutputPort for a specific node
     * @param node The specific node
     * @param name The name of the output port
     * @param infoText Text for the information about the output port
     */
    OutputPort(Node* node, QString name, QString infoText, Type type);
    /**
     * @brief getTargets Returns a list of connected input ports
     * @return Returns a list of connected input ports
     */
    ~OutputPort();

    const QSet<InputPort*> getTargets();

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
    bool isInput() const;

    void send(QVariant data = QVariant());
    void setBlock(bool block);
    bool block() const { return _block; }

signals:
    void sendData(QVariant data);

private:
    bool _block;
    QSet<InputPort*> _targets;
};











