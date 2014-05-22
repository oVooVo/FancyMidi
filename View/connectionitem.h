#pragma once

#include <QGraphicsPathItem>
#include "View/portitem.h"

class AbstractGraphScene;

/**
 * @brief The ConnectionItem class is the graphical representation of a connection between two ports
 * @see QGraphicsPathItem
 */
class ConnectionItem : public QGraphicsPathItem
{

public:
    /**
     * @brief ConnectionItem Creates a ConnectionItem based on a a in- and output port and a scene where to paint on
     * @param outputPort The given output port
     * @param inputPort The given input port
     * @param parent the parent of the ConnectionItem
     * @param scene The scene where to paint on
     */
    explicit ConnectionItem(PortItem* outputPort, PortItem* inputPort, bool selectable,
                            QGraphicsScene *scene, QGraphicsPathItem* parent = 0);
    ~ConnectionItem();

    /**
     * @brief updatePath Re-paints the line
     */
    void updatePath();

    /**
     * @brief inputPort returns the end of the connection
     * @return the end of the connection
     */
    PortItem* inputPort();

    /**
     * @brief outputPort returns the beginning of the connection
     * @return the beginning of the connection
     */
    PortItem* outputPort();

private:
    PortItem* _inputPort;
    PortItem* _outputPort;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

};


