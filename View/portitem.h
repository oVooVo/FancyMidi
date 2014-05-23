#pragma once

#include <QGraphicsPathItem>
#include "Model/port.h"
#include <QTimer>

class AbstractGraphScene;
class NodeItem;
class ConnectionItem;

/**
 * @brief The PortItem class is the graphical representation of the Port class
 * @see QGraphicsPathItem
 * @see Port
 */
class PortItem : public QGraphicsPathItem
{

public:
    enum { Type = QGraphicsItem::UserType + 1 };
    enum { NamePort = 1, TypePort = 2 };

    /**
     * @brief PortItem Creates a new PortItem out of a given Port, parent and scene.
     * @param port the corresponing port.
     * @param parent the parent of the port.
     * @param scene the scene where the PortItem should be drawn at.
     */
    explicit PortItem(Port *port, QString name, QGraphicsScene *scene, NodeItem *parent = 0);

    /**
     * @brief destroys this PortItem.
     */
    ~PortItem();

    /**
     * @brief setIsOutput sets a fleg wheter this PortItem represents an input or output port.
     * @param o true means output port, false means input port
     */
    void setIsOutput(bool o);

    /**
     * @brief radius returns the radius of the circle that visualizes the port item.
     * @return the radius of the circle that visualizes the port item.
     */
    int radius();

    /**
     * @brief isOutput returns whether this port item represents an input or output port.
     * @return whether this port item represents an input or output port.
     */
    bool isOutput();

    /**
     * @brief connections returns all connections that begins or ends at this PortItem.
     * @return all connections that begins or ends at this PortItem.
     */
    QVector<ConnectionItem*>& connections();

    /**
     * @brief setPortFlags set port flags e.g. whether this port is a type or a name port.
     */
    void setPortFlags(int);

    /**
     * @brief portName returns the name of this port.
     * @return the name of this port.
     */
    const QString& portName() const { return _name; }

    /**
     * @brief portFlags returns the port flags e.g. whether this port is a type or a name port.
     * @return the port flags e.g. whether this port is a type or a name port.
     */
    int portFlags() const { return _portFlags; }

    /**
     * @brief type returns the specific type of this QGraphicsPathItem.
     * @return the specific type of this QGraphicsPathItem.
     */
    int type() const { return Type; }

    /**
     * @brief nodeItem returns the NodeItem also known as parent of this PortItem.
     * @return returns the NodeItem also known as parent of this PortItem.
     */
    NodeItem* nodeItem() const;

    /**
     * @brief port returns the corresponding Port from model.
     * @return  the corresponding Port from model.
     */
    Port* port();

    /**
     * @brief addConnectionItem adds a ConnectionItem to a list containing all connections beginning and ending on this port.
     * @param connectionItem the ConnectionItem that should be added.
     */
    void addConnectionItem(ConnectionItem* connectionItem);

    /**
     * @brief deleteConnectionItem removes a ConnectionItem from a list containing all connections beginning and ending on this port.
     *  If the list does not contain connectionItem, nothing happens.
     * @param connectionItem the ConnectionItem that should be removed.
     */
    void removeConnectionItem(ConnectionItem* connectionItem);


protected:
    /**
     * @brief itemChange is calles when this NodeItem made a change.
     * @param change the change this NodeItem made.
     * @param value the new value. E.g. the NodeItem moved, it is the new position.
     * @return value.
     */
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    QString _name;
    bool _isOutput;
    QGraphicsTextItem *_label;
    int _radius;
    int _margin;
    QVector<ConnectionItem*> _connections;
    int _portFlags;
    Port* _port;

    // controls the animation
    QTimer _timer;
    int _time = 0;
    int _duration = 300;
    double time() const { return (double) _time / _duration; }
    void adjustColor();
    QColor _brushColor;

};


