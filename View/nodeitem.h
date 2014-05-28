#pragma once

#include <QGraphicsPathItem>

#include "Model/Nodes/node.h"
#include "Model/port.h"
#include <QSlider>
#include "graphicsproxywidget.h"
#include "SettingWidgets/settingwidget.h"
#include <QGraphicsSceneMouseEvent>

class NodeEvent;
class AbstractGraphScene;
class PortItem;

/**
* @brief The NodeItem class is the graphical representation of a node
* @see QGraphicsPathItem
* @see Node
*/
class NodeItem : public QGraphicsPathItem
{
    //Q_OBJECT //Does not work here because QGraphicsItem is no child of QObject.
public:
    enum { Type = QGraphicsItem::UserType + 42 };
    /**
* @brief NodeItem Creates a NodeItem based on a given node on the graphic scene
* @param node The given node
* @param parent the parent object
* @param scene The graph scene
*/
    explicit NodeItem(Node* node, bool selectable, QGraphicsScene *scene, QGraphicsPathItem *parent = 0);
    ~NodeItem();

    /**
* @brief getNode Get the represented node
* @return Returns the represented node
*/
    Node* node();
    /**
* @brief addInputPort Adds a input port to the represented node
* @param port The given input port
*/
    void addInputPort(Port *port);
    /**
* @brief addOutputPort Adds a input port to the represented node
* @param port The given output port
*/
    void addOutputPort(Port *port);
    /**
* @brief addNamePort Adds a NamePort with the given name to this node
* @param name The name
*/
    void addNamePort(const QString &name);
    /**
* @brief type returns the specific type of this QGraphicsPathItem.
* @return the specific type of this QGraphicsPathItem.
*/
    int type() const { return Type; }

    /**
* @brief getInputs returns all inputPorts of this nodeItem.
* @return all inputPorts of this nodeItem.
*/
    QList<PortItem*> inputs() const;

    /**
* @brief setSize sets this NodeItem's size to given size.
* @param size the new size
* @note the size is only respected by Displayoutputs. Any other NodeItem cannot be resized, using this function will have no effect.
*/
    void setSize(QSizeF size);

    void prepareDeletion();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    /**
* @brief itemChange is calles when this NodeItem made a change.
* @param change the change this NodeItem made.
* @param value the new value. E.g. the NodeItem moved, it is the new position.
* @return value.
*/
    void addPort(Port* port, const QString &name, bool isOutput, int flags = 0);
    int horzMargin;
    int vertMargin;
    int width;
    int height;
    Node* _node;
    QList<PortItem*> _portItems;
    QList<PortItem*> _inputPortItems;
    AbstractGraphScene* getGraphScene() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void updateConnections();
    GraphicsProxyWidget* _settingsItem = 0;
    QList<SettingWidget*> _settingWidgets;
    bool _showSettings = false;
    bool _wasMoved = false;

    int _portCount;
    int _portItemRadius;
    int _initialWidth;
    int _initialHeight;
    int _pwidth;
    int _pheight;
};
