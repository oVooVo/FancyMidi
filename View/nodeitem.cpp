#include "nodeitem.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

#include "connectionitem.h"
#include "Model/inputport.h"
#include "Model/outputport.h"
#include "Model/abstractgraphscene.h"
#include <QGraphicsProxyWidget>
#include <QVBoxLayout>
#include "SettingWidgets/settingwidget.h"

#include <QDebug>


NodeItem::NodeItem(Node* node, bool selectable, QGraphicsScene *scene, QGraphicsPathItem* parent) :
    QGraphicsPathItem(parent)
{
    if (!parent)
        scene->addItem(this);
    setToolTip(node->getInfoText());
    _node = node;
    _portCount = 0;
    _portItemRadius = -1;

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
    addNamePort(node->name());
    for (int i = 0; i < _node->inputPorts().size(); i++) {
        addInputPort(_node->inputPorts().at(i));
    }
    for (int i = 0; i < _node->outputPorts().size(); i++) {
        addOutputPort(_node->outputPorts().at(i));
    }
    /**************************************/

    setFlag(ItemSendsGeometryChanges); //tell me position changes
    _pwidth = width;
    _pheight = height;
    p.addRoundedRect(0, 0, width, height, 2, 2);
    setPath(p);

    if (node->hasSettingsToDisplayInNode()) {
        QWidget* settingContainer = new QWidget();
        _settingsItem = new GraphicsProxyWidget(this);

        settingContainer->setLayout(new QVBoxLayout());
        settingContainer->layout()->setSpacing(0);
        settingContainer->layout()->setContentsMargins(0,0,0,0);
        foreach (Setting* s, node->settings()) {
            if (!s->showInNode())
                continue;
            SettingWidget* settingWidget = SettingWidget::createNewSettingWidget(s, settingContainer);
            settingContainer->layout()->addWidget(settingWidget);
            _settingWidgets.append(settingWidget);
        }
        _settingsItem->setWidget(settingContainer);
        _settingsItem->setPos(0, height);
        _settingsItem->blockSignals(true);
    }
}

NodeItem::~NodeItem()
{
    foreach (PortItem* pi, _portItems) {
        delete pi;
    }
}

Node* NodeItem::node()
{
    return _node;
}

void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen pen;
    pen.setColor(Qt::lightGray);
    pen.setWidth(2);
    if (_settingsItem && _showSettings && isSelected()) {
        _settingsItem->show();
    } else if (_settingsItem) {
        _settingsItem->hide();
    }
    if (isSelected()) {
        painter->setBrush(QColor(255, 255, 0, 210));
    } else {
        painter->setBrush(QColor(180, 180, 180, 210));
    }
    painter->setPen(pen);

    painter->drawPath(path());
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

    QPainterPath p;
    p.addRoundedRect(0, 0, width, height, 2, 2);

    int y = vertMargin + portItem->radius();

    foreach(QGraphicsItem *port_, QGraphicsPathItem::childItems()) {
        if (port_->type() != PortItem::Type)
            continue;

        PortItem *portItem = (PortItem*) port_;
        if (portItem->isOutput())
            portItem->setPos(width + portItem->radius(), y);
        else
            portItem->setPos(-portItem->radius(), y);
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
    node()->setSize(QSizeF(width, height));
}

void NodeItem::addInputPort(Port *port)
{
    addPort(port, port->name(), false);
}

void NodeItem::addOutputPort(Port *port)
{
    addPort(port, port->name(), true);
}

void NodeItem::addNamePort(const QString &name)
{
    addPort(0, name, false, PortItem::NamePort);
}

QVariant NodeItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    //If this is moved by user
    if (change == ItemPositionHasChanged) {
        _wasMoved = true;
        _showSettings = false;
        getGraphScene()->beginUpdate();
        _node->setPosition(value.toPoint()); //Set pos in Model
        updateConnections();
        getGraphScene()->endUpdate();
    } else if (change == ItemSelectedChange) {
        if (!value.value<bool>())
            _showSettings = false;
    }
    return QGraphicsItem::itemChange(change, value);
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

QList<PortItem*> NodeItem::inputs() const
{
    return _inputPortItems;
}

void NodeItem::prepareDeletion()
{
    qDeleteAll(_settingWidgets);
}

void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    _wasMoved = false;
    QGraphicsItem::mousePressEvent(event);
}

void NodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    _showSettings = !_wasMoved & isSelected();
    update();
}
