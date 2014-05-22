#include "queuednode.h"
#include "project.h"
#include "queueinputport.h"


QueuedNode::QueuedNode(QPoint position, Project* parent, QString name, QString infoText) :
    Node(position, parent, name, infoText)
{

}

void QueuedNode::clear() { // This function resets all inputs.
    foreach(InputPort* port, getInputs())
        ((QueueInputPort*)port)->clear();
	Node::clear();
}