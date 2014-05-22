#pragma once

#include <QGraphicsPathItem>
#include <QGraphicsScene>

#include "portitem.h"

/**
 * @brief The TemporaryConnection class is the representation of a tube in the graph, that is connected to exactly one
 *  Port. It has - unlike ConnectionItem - no representation in model.
 */
class TemporaryConnection : public QGraphicsPathItem
{
public:
    /**
     * @brief TemporaryConnection Creates a new TemporaryConnection.
     * @param portItem the base of this Connection.
     * @param parent the parent of this connection.
     * @param scene the scene where this connection is drawn.
     */
    explicit TemporaryConnection(PortItem *portItem, QGraphicsScene *scene, QGraphicsItem *parent = 0);

    /**
     * @brief updatePath update the second position to position.
     * @param position the second position where the line is drawn to.
     */
    void updatePath(QPointF position);

    /**
     * @brief portItem returns the anchor of this connection
     * @return the anchor of this connection
     */
    PortItem* portItem();

    /**
     * @brief setBlack sets the color of the tube black.
     */
    void setBlack();

    /**
     * @brief setGrey sets the color of the tube grey.
     */
    void setGrey();

private:
    PortItem* _portItem;
    bool _black;
};


