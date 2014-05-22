#pragma once

#include "node.h"

/**
 * @brief The QueuedNode class is a variant of the Node class capable of having a queued input port
 * @see Node
 */
class QueuedNode: public Node
{
    Q_OBJECT
public:
    /**
    * @brief QueuedNode creates a QueuedNode out of a given position, parent name and infoText.
    * @param position the position where the node spawns.
    * @param parent the nodes parent.
    * @param name the name of this node.
    * @param infoText a short text that describes this node-
    */
   QueuedNode(QPoint position, Project* parent, QString name, QString infoText = "");

   /**
    *     @brief frameArise Called when a new frame arise on one of the input ports.
    *     @param port the port on which the new package arose.
    *     @param id the id of the package
    */
   virtual void frameArise(QueueInputPort* port, int id) = 0;

   /**
    * @brief clear clears all cached data.
    */
   virtual void clear();
};










//~ Formatted by Jindent --- http://www.jindent.com
