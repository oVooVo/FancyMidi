#include <QDebug>

#include "abstractgraphscene.h"

#include "View/connectionitem.h"
#include "mainwindow.h"


AbstractGraphScene::AbstractGraphScene(Project* project, MainWindow *mainWindow, QObject* parent, bool selectable)
    : QGraphicsScene(parent)
{
    _isUpdating = false;
    _mainWindow = mainWindow;
    _isSelectable = selectable;
    installEventFilter(this);
    _model = 0;
    setModel(project);
}

void AbstractGraphScene::redraw()
{
    _model->selfCheck();
    //_mainWindow->adjustControlsAreEnabled();
    if(_isUpdating || !_model) return;
    beginUpdate();
    foreach (NodeItem* nodeItem, _nodeMap.keys()) {
        if (!_model->nodes().contains(nodeItem->getNode())) {
            _nodeMap.remove(nodeItem);
			_displayOutputNodeItems.remove(nodeItem);

            //unperformant, but input->port() will not work because input->port() is already deleted
            foreach (PortItem* input, nodeItem->getInputs()) {
                foreach (InputPort* inputPort, _inputPortMap.keys()) {
                    if (_inputPortMap.value(inputPort) == input) {
                        _inputPortMap.remove(inputPort);
                    }
                }
            }
            removeItem(nodeItem);

			// if we delete a nodeitem we have to remove its connectionItems first
			QSet<ConnectionItem*> toDel;
			foreach(ConnectionItem* ci, _connectionItems) {
				if(ci->outputPort() && ci->outputPort()->nodeItem() == nodeItem)
					toDel += ci;
				if(ci->inputPort() && ci->inputPort()->nodeItem() == nodeItem)
					toDel += ci;
			}
			foreach(ConnectionItem* ci, toDel)
				_connectionItems.removeAll(ci);
            delete nodeItem;
        }
    }
    foreach (Node* node, _model->nodes()) {
        if (!_nodeMap.values().contains(node)) {
            NodeItem* newNodeItem = new NodeItem(node, _isSelectable, node->inherits("DisplayOutput"), this);
            _nodeMap.insert(newNodeItem, node);
			if(node->inherits("DisplayOutput"))
				_displayOutputNodeItems += newNodeItem;
            foreach (PortItem* input, newNodeItem->getInputs()) {
                _inputPortMap.insert((InputPort*) input->port(), input);
            }
        }
    }
    emit nodeItemMoved();
    endUpdate();
}

void AbstractGraphScene::lightRedraw(QList<InputPort *> inputs)
{
    if(_isUpdating || !_model) return;
    beginUpdate();
    foreach (QGraphicsItem *g, items()) {
        NodeItem *nodeItem = dynamic_cast<NodeItem*>(g);
        if (nodeItem && nodeItem->getNode()) {
            nodeItem->redraw();
            nodeItem->setPos(nodeItem->getNode()->getPosition());
			if(nodeItem->isResizeable())
				nodeItem->setSize(nodeItem->getNode()->getSize());
		}
    }
    foreach (InputPort* inputPort, inputs) {
        PortItem* input = _inputPortMap.value(inputPort);
        OutputPort* source = ((InputPort*)input->port())->getSource();
        if (!input->connections().isEmpty()) {
            if (input->connections().first()->outputPort()->port() != source) {
                _connectionItems.removeAll(input->connections().first());   // use removeOne()? (only intension for this is performance)
                delete input->connections().first();
            }
        }
        foreach (QGraphicsItem* gi, items()) {
            if (gi->type() != PortItem::Type) continue;
            if (!((PortItem*) gi)->port() || ((PortItem*) gi)->port()->isInput()) continue;
            //so far, gi is a PortItem with a non-zero OutputPort
            PortItem* sourceItem = (PortItem*) gi;

            if (source == sourceItem->port()) {
                bool duplicate = false;
                foreach (ConnectionItem* ci, _connectionItems)
                {
                    if (ci->inputPort() == input && ci->outputPort() == sourceItem) {
                        duplicate = true;
                        break;
                    }
                }
                if (!duplicate) {
                    ConnectionItem* connection = new ConnectionItem(sourceItem, input, _isSelectable, this);
                    _connectionItems += connection;
                    //_model->selfCheck();
                }
                //optimize this using break here maybe... //TODO?
            }
        }
    }
    if (!inputs.isEmpty()) {    // inputs.isEmpty() <=> nur nodes wurden verschoben
                                //!inputs.isEmpty() <=> connection hinzugefügt/entfernt
        _model->selfCheck();
        //_mainWindow->adjustControlsAreEnabled();
    }
    endUpdate();
}

void AbstractGraphScene::beginUpdate()
{
    //assert(!_isUpdating);
    _isUpdating = true;
}

void AbstractGraphScene::endUpdate()
{
    //assert(_isUpdating);
    _isUpdating = false;
}

void AbstractGraphScene::setModel(Project *model){
    if (_model == model) return;
    if (_model) {
        disconnect(_model, SIGNAL(modelChanged()), this, SLOT(redraw()));
        disconnect(_model, SIGNAL(nodesChanged(QList<InputPort*>)), this, SLOT(lightRedraw(QList<InputPort*>)));
    }
    _model = model;
    if (_model) {
        connect(_model, SIGNAL(modelChanged()), this, SLOT(redraw()));
        connect(_model, SIGNAL(nodesChanged(QList<InputPort*>)), this, SLOT(lightRedraw(QList<InputPort*>)));
        redraw();
        QList<InputPort*> inputPorts;
        foreach (Node* node, _model->nodes()) {
            inputPorts.append(node->getInputs());
        }
        lightRedraw(inputPorts);
    }
}

Project* AbstractGraphScene::model()
{
    return _model;
}

NodeItem* AbstractGraphScene::nodeItemAt(QPointF scenePos)
{
    QTransform t_unused;
    QGraphicsItem* gi = itemAt(scenePos, t_unused);
    if (!gi) return 0;

    //move in top-direction until found a NodeItem or reached top-level
    while (gi && gi->type() != NodeItem::Type && gi->parentItem()) {
        gi = gi->parentItem();
    }

    if (gi->type() == NodeItem::Type) {
        return (NodeItem*) gi;
    } else {
        return 0;
    }
}
