#pragma once

#include <QSharedPointer>
#include "node.h"
#include "packet.h"
#include "port.h"

/**
 * @brief The InputPort class is a in going connection to a node
 * @see Port
 */
class InputPort:
	public Port
{
	public:
        /**
         * @brief InputPort Creates a InputPort for a specific node
         * @param node The specific node
         * @param name Name of the input port
         * @param infoText Text for the information about the input port
         */
        InputPort(Node* node, QString name, QString infoText, bool isData = false);
		~InputPort();
        /**
         * @brief isModifying Whether the associated node or a following one is modifying the packet
         * @return Whether the associated node or a following one is modifying the packet
         */
		virtual bool isModifying();

		//virtual void pushFrame(QSharedPointer<FramePacket> frame);
        /**
         * @brief pushPacket The node receives the given packet
         * @param packet The given packet
         */
		virtual void pushPacket(QSharedPointer<Packet> packet) = 0;
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
		bool isInput();

        /**
         * @brief getSource returns the OutputPort this port is connected with.
         * @return the OutputPort this port is connected with.
         */
        OutputPort* getSource();

	protected:
        /**
         * @brief _source the OutputPorts that are connected to this InputPort.
         */
        OutputPort* _source;
};











