#include <QDragEnterEvent>
#include <QDebug>
#include <QApplication>
#include "Model/Nodes/node.h"
#include <QDebug>
#include <QDrag>
#include <QMimeData>

#include "nodetree.h"

bool lessThan(Node const *n1, Node const *n2)
{
    return n1->name() < n2->name();
}

NodeTree::NodeTree(QWidget* parent) : QTreeWidget(parent)
{
	setHeaderHidden(true);
	//Move this to a more central place?>
    QMap<QString, QList<Node*> > nodes;
    for (QString className : Node::nodeClassnames()) {
		Node* node = Node::createInstance(className);
        if (nodes.keys().contains(node->category())) {
            nodes[node->category()].append(node);
        } else {
            nodes.insert(node->category(), QList<Node*>() << node);
        }
	}

    for (QString category : nodes.keys()) {
        QTreeWidgetItem* categoryItem = new QTreeWidgetItem(this, QStringList(category));
        QList<Node*> cnodes = nodes[category];
        qSort(cnodes.begin(), cnodes.end(), lessThan);
        for (Node* node : cnodes) {
            QTreeWidgetItem* subitem = new QTreeWidgetItem(QStringList(node->name()));
            _nodes.insert(subitem, node->metaObject()->className());
            categoryItem->addChild(subitem);
            delete node;
        }
    }
}

void NodeTree::mouseMoveEvent(QMouseEvent *event)
{
    if (((_dragStart - event->pos()).manhattanLength() < 10)
            || selectedItems().size() < 1 || !_nodes.keys().contains(selectedItems().first()))
        return;

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;

    mimeData->setText(_nodes[selectedItems().first()]);
    drag->setMimeData(mimeData);

    drag->exec();
}
