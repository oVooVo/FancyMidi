#pragma once

#include <QTreeWidget>
#include <QPoint>
#include <QMap>

/**
 * @brief The NodeTree class provides the nood-pool. From this class, you can drag and drop nodes
 *  into the graphscene.
 */
class NodeTree : public QTreeWidget
{
	Q_OBJECT
public:
	/**
	 * @brief NodeTree creates a new NodeTree with given parent.
	 * @param parent the parent of this Widget.
	 * @see QTreeWidget
	 */
	explicit NodeTree(QWidget *parent = 0);

protected:
	/**
	 * @brief mouseMoveEvent is calles when the mouse moves over this widget.
	 * @param event the provided data of the mouse move.
	 */
	void mouseMoveEvent(QMouseEvent *event);

private:
	QPoint _dragStart;
	QMap<QTreeWidgetItem*, QString> _nodes;
};


