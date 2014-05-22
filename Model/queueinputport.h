#pragma once

#include <QReadWriteLock>
#include <QSharedPointer>
#include "inputport.h"
#include "queueinputport.h"

/**
 * @brief The QueueInputPort class is a variant of the InputPort class capable of receiving and sending out of ordered packets
 * @see InputPort
 */
class QueueInputPort: public InputPort
{
public:
    /**
     * @brief QueueInputPort Creates a QueueInputPort for a given node and a given name and a description
     * @param node The given node
     * @param name The name of the port
     * @param infoText The description of the port
     */
    QueueInputPort(Node* node, QString name, QString infoText = "");
    /**
     * @brief pushPacket Notifies the associated node that a packet arose
     * @param packet The new packet
     */
    void pushPacket(QSharedPointer<Packet> packet);
    /**
     * @brief hasPacket Whether the queue contains the packet with a given id
     * @param id The given id of the packet
     * @return Returns whether the queue contains the packet with a given id
     */
    bool hasPacket(int id);
    /**
     * @brief dequeuePacket Removes the packet with the given id from the queue
     * @param id The given id of the packet
     * @return Returns the removed packet
     */
    QSharedPointer<Packet> dequeuePacket(int id);

    /**
     * @brief clear clears all cached data.
     */
    void clear();

private:
    QHash<int, QSharedPointer<Packet> > _hashMap;
    QReadWriteLock _readWriteLock;
};










//~ Formatted by Jindent --- http://www.jindent.com
