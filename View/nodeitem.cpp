#include "nodeitem.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

#include "connectionitem.h"
#include "Model/inputport.h"
#include "Model/outputport.h"
#include "Model/abstractgraphscene.h"

#include <QDebug>


NodeItem::NodeItem(Node* node, bool selectable, bool resizeable, QGraphicsScene* scene, QGraphicsPathItem* parent) :
    QGraphicsPathItem(parent)
{
    if (!parent) scene->addItem(this);
    setToolTip(node->getInfoText());
	_node = node;
	_resizeable = resizeable;
	_portCount = 0;
	_portItemRadius = -1;
	_resizeHandlerSize = 10;

	/* define the way this item becomes painted */
	QPainterPath p;
	setPos(node->getPosition());
	if (selectable) {
		setFlag(QGraphicsItem::ItemIsMovable);
		setFlag(QGraphicsItem::ItemIsSelectable);
	}

	horzMargin = 35;
	vertMargin = 5;
	width = horzMargin;
	height = vertMargin;
	/**************************************/


    /********* add ports ******************/
    addNamePort(node->getName());
    for (int i = 0; i < _node->getInputs().size(); i++) {
        addInputPort(_node->getInputs().at(i));
    }
    for (int i = 0; i < _node->getOutputs().size(); i++) {
        addOutputPort(_node->getOutputs().at(i));
    }
    /**************************************/

    setFlag(ItemSendsGeometryChanges); //tell me position changes
	_resize = false;
	_pwidth = width;
	_pheight = height;
	_currentId = 0;
    if (_resizeable) {
		p.addRect(width-_resizeHandlerSize, height-_resizeHandlerSize, _resizeHandlerSize, _resizeHandlerSize);
        setSize(node->getSize());
    }
    p.addRoundedRect(0, 0, width, height, 5, 5);
    setPath(p.translated(-width/2, -height/2));
}

NodeItem::~NodeItem()
{
    foreach (PortItem* pi, _portItems) {
		delete pi;
	}
}

Node* NodeItem::getNode()
{
	return _node;
}

void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	QPen pen;
	if (_node->getState() == Node::GOOD) {
		pen.setColor(Qt::black);
		pen.setWidth(1);
		if (isSelected()) {
			painter->setBrush(QColor(255, 255, 0, 210));
		} else {
			painter->setBrush(QColor(255, 255, 255, 210));
		}
	} else if (_node->getState() == Node::DEAD) {
		pen.setColor(Qt::darkGray);
		pen.setWidth(2);
		if (isSelected()) {
			painter->setBrush(QColor(255, 255, 0, 210));
		} else {
			painter->setBrush(QColor(180, 180, 180, 210));
		}
	} else if (_node->getState() == Node::RED) {
		pen.setColor(Qt::darkRed);
		pen.setWidth(2);
		if (isSelected()) {
			painter->setBrush(QColor(255, 255, 0, 210));
		} else {
			painter->setBrush(QColor(255, 100, 100, 210));
		}
	}
	painter->setPen(pen);

    painter->drawPath(path());
	if (_resizeable) {
        /** handle display output */
	}
}

void NodeItem::addPort(Port* port, const QString &name, bool isOutput, int flags)
{
    PortItem *portItem = new PortItem(port, name, scene(), this);
	portItem->setIsOutput(isOutput);
	portItem->setPortFlags(flags);

	QFontMetrics fm(getGraphScene()->font());
	int w = fm.width(name);
	int h = fm.height();
	// port->setPos(0, height + h/2);
	if (w > width - horzMargin)
		width = w + horzMargin;
	height += h;
	if(_resizeable) {
		width = 250;
		height = 150;
	}
	QPainterPath p;
	p.addRoundedRect(0, 0, width, height, 5, 5);

    int y = vertMargin + portItem->radius() - height/2;

    foreach(QGraphicsItem *port_, QGraphicsPathItem::childItems()) {
		if (port_->type() != PortItem::Type)
			continue;

		PortItem *portItem = (PortItem*) port_;
		if (portItem->isOutput())
            portItem->setPos(width/2 + portItem->radius(), y);
		else
            portItem->setPos(-portItem->radius() - width/2, y);
		y += h;
	}

	_portItems.append(portItem);
	if (port && !isOutput) {
		_inputPortItems.append(portItem);
	}
	_portCount++;
	if (_portItemRadius == -1) {
		_portItemRadius = portItem->radius();
	}
	_initialHeight = height;
	_initialWidth = width;
	_pwidth = width;
	_pheight = height;
	setPath(p);

}

void NodeItem::setSize(QSizeF size)
{
    width = size.width() > _initialWidth ? size.width() : _initialWidth;
    height = size.height() > _initialHeight ? size.height() : _initialHeight;
	QPainterPath p;
    p.addRoundedRect(0, 0, width, height, 5, 5);
	setPath(p);
    getNode()->setSize(QSizeF(width, height));
}

void NodeItem::addInputPort(Port *port)
{
	addPort(port, port->getName(), false);
}

void NodeItem::addOutputPort(Port *port)
{
	addPort(port, port->getName(), true);
}

void NodeItem::addNamePort(const QString &name)
{
	addPort(0, name, false, PortItem::NamePort);
}

QVariant NodeItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
	//If this is moved by user
	if (change == ItemPositionHasChanged) {
		getGraphScene()->beginUpdate();
		_node->setPosition(value.toPoint());    //Set pos in Model
		updateConnections();
		getGraphScene()->endUpdate();
	}
	return value;
}

void NodeItem::updateConnections()
{
	foreach(PortItem *portItem, _portItems) {
        foreach (ConnectionItem *connectionItem, portItem->connections()) {
			connectionItem->updatePath();
		}
	}
}

AbstractGraphScene* NodeItem::getGraphScene() const
{
	return qobject_cast<AbstractGraphScene*>(scene());
}

QList<PortItem*> NodeItem::getInputs() const
{
	return _inputPortItems;
}

void NodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (_resize)
	{
		prepareGeometryChange();
		_pwidth  += (event->scenePos().x() - event->lastScenePos().x());
		_pheight += (event->scenePos().y() - event->lastScenePos().y());
        setSize(QSizeF(_pwidth, _pheight));
	} else {
		QGraphicsPathItem::mouseMoveEvent(event);
	}
}

void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (_resizeable && event->button() == Qt::LeftButton && (event->pos() - QPointF(width, height)).manhattanLength() < 2*_resizeHandlerSize) {
		_resize = true;
	}
	QGraphicsPathItem::mousePressEvent(event);
}

void NodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	_resize = false;
	_pwidth = width;
	_pheight = height;
	QGraphicsPathItem::mouseReleaseEvent(event);
}

void NodeItem::showFrame(int id) {
	if (id >= 0)
	{
		_currentId = id;
        update();
	}
}

QRectF NodeItem::myBoundingRect() const
{
    int hasInputs = 0;
    int hasOutputs = 0;
    foreach (PortItem* pi, _portItems) {
        if (!pi->port()) continue;

        if (pi->port()->isInput()) {
            hasInputs = 1;
        } else {
            hasOutputs = 1;
        }

        if (hasInputs == 1 && hasOutputs == 1) break;
    }
    return QRectF(scenePos(), QSizeF(width + (hasInputs + hasOutputs) * _portItemRadius, height));
}

void NodeItem::redraw()
{
    prepareGeometryChange();
}

bool NodeItem::isResizeable() const
{
	return _resizeable;
}
















