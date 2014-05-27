#include "graphscene.h"

#include <QKeyEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QPointF>
#include <QTimer>
#include <QMimeData>

#include "port.h"
#include "View/connectionitem.h"
#include "mainwindow.h"

#include <QDebug>

#include "View/nodewidget.h"

#define SCENE_SIZE 1000000

GraphScene::GraphScene(Project *project, MainWindow* mainWindow, QObject *parent) :
    AbstractGraphScene(project, mainWindow, parent, true)
{
    _locked = false;
    _contentRect = new QGraphicsRectItem();
    _contentRect->setRect(-SCENE_SIZE/2, -SCENE_SIZE/2, SCENE_SIZE, SCENE_SIZE);
    addItem(_contentRect);
	_contentRect->setZValue(-100);
    if (_model) {
        _model->installEventFilter(this);   //to recognize child add, child remove and polish event
    }
    _temporaryConnection = 0;
}

bool GraphScene::eventFilter(QObject *watched, QEvent *event)
{
    if (!_locked && event->type() == QEvent::KeyPress) {
        int key = ((QKeyEvent*) event)->key();
        if (16777223 == key) {                              //entf

            QList<NodeItem*> nodeItemsToDelete;
            QList<InputPort*> disconnectedInputports; //the relation inputport --> connection is unambiguous
            foreach (QGraphicsItem* gi, selectedItems())
            {
                if (gi->type() == NodeItem::Type) {
                    nodeItemsToDelete.append(((NodeItem*)gi));
                    ((NodeItem*) gi)->prepareDeletion();
                } else if (gi->type() == ConnectionItem::Type) {
                    disconnectedInputports.append((InputPort*)((ConnectionItem*)gi)->inputPort()->port());
                }
            }

            foreach (InputPort* inputPort, disconnectedInputports) {
                foreach (NodeItem* ni, nodeItemsToDelete)
                {
                    if (ni->node() == inputPort->node()) {
                        disconnectedInputports.removeOne(inputPort);
                        break;
                    }
                }
            }
			foreach (InputPort* inputPort, disconnectedInputports) {
				inputPort->disconnect();
			}
            foreach (NodeItem* n, nodeItemsToDelete) {
                delete n->node();
            }
            _model->popularizeModelChange();
            _model->popularizeNodesChange(disconnectedInputports);
            showSettings(selectedNodes());
            redraw();
        } else if (16777249 == key) {   //strg
            _strgPressed = true;
        } else if (65 == key && _strgPressed) { //A
            foreach (QGraphicsItem* gi, items()) {
                if (gi->type() == NodeItem::Type) {
                    gi->setSelected(true);
                } else {
                    gi->setSelected(false);
                }
            }
        } else if (67 == key && _strgPressed) { //C
            copy();
        } else if (84 == key && _strgPressed) { //T
            foreach (QGraphicsItem* gi, items()) {
                if (gi->type() == ConnectionItem::Type) {
                    gi->setSelected(true);
                } else {
                    gi->setSelected(false);
                }
            }
        } else if (!_locked && 86 == key && _strgPressed) { //V
            paste();
        }
    }
    if (event->type() == QEvent::KeyRelease) {
        int key = ((QKeyEvent*) event)->key();
        if (16777249 == key) {   //strg
            _strgPressed = false;
        }
    }
    return QGraphicsScene::eventFilter(watched, event);
}

void GraphScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if (!_locked) {
        _mainWindow->stop();
        QString text = event->mimeData()->text();        
        Node *node = Node::createInstance(text);
        node->setPosition(event->scenePos().toPoint());
        node->setParent(_model);
        node->polish();
        emit showSettings(QList<Node*>() << node);
    }
    QGraphicsScene::dropEvent(event);
}

void GraphScene::dragMoveEvent(QGraphicsSceneDragDropEvent *)
{
    //do nothing, but nothing else!
}

void GraphScene::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    bool forwardMousePress = true;
    if (e->button() == Qt::LeftButton) {

        NodeItem* clicked = nodeItemAt(e->scenePos());
        if (clicked) {
            foreach (QGraphicsItem* gi, items()) {
                NodeItem* ni = dynamic_cast<NodeItem*>(gi);
                if (ni && ni != clicked) {
                    ni->stackBefore(clicked);
                }
            }
        }
        //bring selected on top
        foreach (QGraphicsItem* gi, selectedItems()) {
            foreach (QGraphicsItem* before, items()) {
                if (before->type() == NodeItem::Type && !selectedItems().contains(before) && before != clicked) {
                    before->stackBefore(gi);
                }
            }
        }
    }
    if (e->button() == Qt::LeftButton) {
        QTransform t_unused;
        PortItem* portItem = dynamic_cast<PortItem*>(itemAt(e->scenePos(), t_unused));
        if (!_locked && portItem) {
            forwardMousePress = false;
            TemporaryConnection* temporaryConnection = new TemporaryConnection(portItem, this);
            _temporaryConnection = temporaryConnection;
        }
    }
    if (forwardMousePress)
        QGraphicsScene::mousePressEvent(e);
    emit showSettings(selectedNodes());
}

void GraphScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (_temporaryConnection) {
        QTransform t_unused;
        QGraphicsItem* gi = itemAt(event->scenePos(), t_unused);
        PortItem* pi = (PortItem*) gi;
        if (gi && gi->type() == PortItem::Type
                && pi->port() && Port::canConnect(pi->port(), _temporaryConnection->portItem()->port())
                && pi->port()->isInput() != _temporaryConnection->portItem()->port()->isInput()) {
            _temporaryConnection->setBlack();
        } else {
            _temporaryConnection->setGrey();
        }
        _temporaryConnection->updatePath(event->scenePos());
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void GraphScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QTransform t_unused;
        QGraphicsItem* gi = itemAt(event->scenePos(), t_unused);
        PortItem* endPort = 0;
        if (gi) {
            endPort = dynamic_cast<PortItem*>(gi);
        }
        if (_temporaryConnection) {
            PortItem* startPort = 0;
            if (endPort) {
                startPort = _temporaryConnection->portItem();
            }
            delete _temporaryConnection;
            _temporaryConnection = 0;
            if (startPort && endPort && endPort->port() && endPort->port()->isInput() != startPort->port()->isInput()) {
                _mainWindow->stop();
                startPort->port()->connect(endPort->port());
                if (startPort->nodeItem() == endPort->nodeItem())
                    return; // ignore connection from same item
                if (startPort->port()->isInput()) {
                    _model->popularizeNodesChange(QList<InputPort*>() << (InputPort*) startPort->port());
                } else {
                    _model->popularizeNodesChange(QList<InputPort*>() << (InputPort*) endPort->port());
                }
            }
        }
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void GraphScene::copy()
{
    _copyPasteNodeList.clear();
    _copy.clear();
    QDataStream copyStream(&_copy, QIODevice::WriteOnly);

    foreach (QGraphicsItem* gi, selectedItems()) {
        if (gi->type() == NodeItem::Type) {
            if (((NodeItem*) gi)->node()) {
                _copyPasteNodeList.append(((NodeItem*) gi)->node());
            }
        }
    }
    copyStream << _copyPasteNodeList;
    int count = 0;
    for(int i = 0; i < _copyPasteNodeList.count(); i++) {
        for(int p = 0; p < _copyPasteNodeList[i]->outputPorts().count(); p++) {
            foreach (InputPort* inputPort, _copyPasteNodeList[i]->outputPorts()[p]->targets()) {
                if (_copyPasteNodeList.contains(inputPort->node())) {
                    count++;
                }
            }
        }
    }
    copyStream << count;
    for (int nodeIndex = 0; nodeIndex < _copyPasteNodeList.count(); nodeIndex++) {
        for (int inputPortIndex = 0; inputPortIndex < _copyPasteNodeList[nodeIndex]->inputPorts().count(); inputPortIndex++) {
            OutputPort* outputPort = _copyPasteNodeList[nodeIndex]->inputPorts()[inputPortIndex]->source();
            if (outputPort && _copyPasteNodeList.contains(outputPort->node())) {
                copyStream << nodeIndex;                                                //target node
                copyStream << inputPortIndex;                                           //target port
                copyStream << _copyPasteNodeList.indexOf(outputPort->node());        //source node
                copyStream << outputPort->node()->outputPorts().indexOf(outputPort);  //source port
            }
        }
    }
}

void GraphScene::paste()
{
    if (!_copy.isEmpty()) {
        _mainWindow->stop();
        QList<InputPort*> newInputPorts;
        _pastedNodes.clear();

        QDataStream istream(&_copy, QIODevice::ReadOnly);
        istream >> _pastedNodes;

        for(int i = 0; i < _pastedNodes.count(); i++) {
           _pastedNodes[i]->setParent(this->model());
           _pastedNodes[i]->setPosition(_pastedNodes[i]->getPosition() + QPoint(20, 20));
           _pastedNodes[i]->polish();
        }

        int count;
        istream >> count;
        for(int c = 0; c < count; c++) {
           int targetNodeIndex, targetPortIndex, sourceNodeIndex, sourcePortIndex;
           istream >> targetNodeIndex >> targetPortIndex >> sourceNodeIndex >> sourcePortIndex;
           _pastedNodes[targetNodeIndex]->inputPorts()[targetPortIndex]->connect(_pastedNodes[sourceNodeIndex]->outputPorts()[sourcePortIndex]);
           newInputPorts += _pastedNodes[targetNodeIndex]->inputPorts()[targetPortIndex];

        }
        selectPastedNodes();
        _model->popularizeModelChange();
        _model->popularizeNodesChange(newInputPorts);
    }

}

void GraphScene::selectPastedNodes()
{
    foreach (QGraphicsItem* gi, items()) {
        if (gi->type() == NodeItem::Type && _pastedNodes.contains(((NodeItem*) gi)->node())) {
            foreach (QGraphicsItem* before, items()) {
                if (before->type() == NodeItem::Type && !_pastedNodes.contains(((NodeItem*) before)->node()))
                    before->stackBefore(gi);
            }
            gi->setSelected(true);
        } else {
            gi->setSelected(false);
        }
    }
}

void GraphScene::lock()
{
    _locked = true;

}

void GraphScene::unlock()
{
    _locked = false;
}

QPointF GraphScene::getCenter() const
{
    return boundingBox().center();
}


void GraphScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseDoubleClickEvent(event);
}

QList<Node*> GraphScene::selectedNodes() const
{
    QList<Node*> nodes;
    for (QGraphicsItem* item : selectedItems()) {
        if (item->type() == NodeItem::Type) {
            nodes.append(((NodeItem*) item)->node());
        }
    }
    return nodes;
}


