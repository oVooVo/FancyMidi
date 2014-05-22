#pragma once
#include <QSharedPointer>

/**
 * @brief The Packet class is a abstract class to have a common interface to different packet types
 */
class Packet
{
public:
    /**
     * @brief Packet Creates a packet
     */
    Packet(int id);

    /**
     * @brief ~Packet Destroys this packet
     */
    virtual ~Packet();

    /**
     * @brief copy Creates a encapsulated copy of this packet
     * @return Returns a encapsulated copy of this packet
     */
    virtual QSharedPointer<Packet> copy() = 0;

    virtual bool isEndPacket() = 0;

    /**
     * @brief getId Returns the id of this packet
     * @return Returns the id of this packet
     */
    int getId();

    /**
     * @brief setId Sets the id of the frame
     * @param id The new id of the frame
     */
    void setId(int id);

private:
    int _id;
};












