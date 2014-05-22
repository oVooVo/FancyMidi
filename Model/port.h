#pragma once

#include <QSharedPointer>
#include "node.h"
#include "packet.h"

/**
 * @brief The Port class is a abstract class to have common method shared between input and output port
 */
class Port
{
	public:
        /**
         * @brief Port Creates a port for a specific node
         * @param node The specific node
         * @param name The name of the port
         * @param infoText The text describing this port
         */
        Port(Node* node, QString name, QString infoText, bool isData);
        virtual ~Port();
        /**
         * @brief pushPacket Sends the packet to the connected input port
         * @param packet The given packet
         */
		virtual void pushPacket(QSharedPointer<Packet> packet) = 0;
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
		virtual bool isInput() = 0;
        /**
         * @brief getNode Returns the associated node
         * @return Returns the associated node
         */
		Node* getNode();
        /**
         * @brief getName Returns the name of this port
         * @return Returns the name of this port
         */
        QString getName();
        /**
         * @brief getInfoText Returns the text describing this port
         * @return Returns the text describing this port
         */
        QString getInfoText();

        /**
         * @brief isData returns whether this port represents a data port.
         * @return whether this port represents a data port.
         */
        bool isData();

	private:
		Node* _node;
        QString _name;
        QString _infoText;
        bool _isData;
};










