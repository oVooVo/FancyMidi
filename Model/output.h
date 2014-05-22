#pragma once
#include <QVector>
#include <QSharedPointer>
#include <QMutex>
#include "queuednode.h"
#include "packet.h"

/**
 * @brief The Output class provides abstract parents for all outputs.
 */
class Output : public QueuedNode
{
    Q_OBJECT
public:
    /**
     * @brief Output creates a new node on a given position in a given project.
     * @param position the position where this node spawns.
     * @param parent the parent this node is associated with.
     * @param name the name of this node.
     * @param infoText the tooltip of this node.
     */
    Output(QPoint position, Project* parent, QString name, QString infoText);

    //TODOcomment
    void frameArise(QueueInputPort* port, int id);

    //TODOcomment
    virtual void savePacket(QSharedPointer<Packet> packet) = 0;

    /**
     * @brief clear clears all cached data.
     */
    virtual void clear();

    //TODOcomment
	virtual void finalize();

    /**
     * @brief count returns the total count of all packets.
     * @return the total count of all packets.
     */
    int count() const;

    /**
     * @brief exactCount the count of all non-EndPackets. You should only call this if this node is complete.
     * @return the count of all non-EndPackets.
     */
	int exactCount() const;

    /**
     * @brief isComplete returns whether the calculation in this node is complete.
     * @return whether the calculation in this node is complete.
     */
	bool isComplete();

private:
    int _count;
	int _exactCount; // is -1 when unknown
    QMutex _mutex;
};

