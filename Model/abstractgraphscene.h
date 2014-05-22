#pragma once

#include <QGraphicsScene>
#include "project.h"
#include "View/nodeitem.h"
#include <QObject>

class MainWindow;

/**
 * @brief The AbstractGraphScene class provides basically features of graph scenes, such as redraw
 *  and NodeItem managemant.
 */
class AbstractGraphScene : public QGraphicsScene
{
    Q_OBJECT
public:
    /**
     * @brief AbstractGraphScene creates a new AbstractGraphScene out of the given project, parent.
     * @param project the project that is visualized by this.
     * @param parent the scene's parent.
     * @param selectable Defines whether the scene's items are selectable or not.
     */
    AbstractGraphScene(Project* project, MainWindow* mainWindow, QObject *parent, bool selectable);

    /**
     * @brief ~AbstractGraphScene destroys this AbstractGraphScene.
     */
    virtual ~AbstractGraphScene() {}

    /**
     * @brief beginUpdate lock the scene for updates
     */
    void beginUpdate();

    /**
     * @brief endUpdate unlock the scene for updates
     */
    void endUpdate();

    /**
     * @brief model Returns the associated model.
     * @return Returns the associated model.
     */
    Project* model();

    /**
     * @brief nodeItemAt Returns The nodeItem at the denoted position or zero if there is no NodeItem.
     * @param scenePos Position of the returned nodeItem
     * @return the nodeItem at the denoted position or zero if there is no NodeItem.
     */
    NodeItem* nodeItemAt(QPointF scenePos);

protected:
    /**
     * @brief _model the visualized project.
     */
    Project* _model;

    /**
     * @brief _displayOutputNodeItems all NodeItems that can show a video inside themselfe.
     */
	QSet<NodeItem*> _displayOutputNodeItems;

    /**
     * @brief setModel sets the project to a given project.
     * @param model the new projetc.
     */
    void setModel(Project* model);

public slots:
    /**
     * @brief redraw redraws the scene completely new.
     */
    void redraw();

    /**
     * @brief lightRedraw redraws only the connections with denoted inputPort.
     * @param inputs each updated connection's input port is in this list.
     */
    void lightRedraw(QList<InputPort*> inputs = QList<InputPort*>());

private:
    bool _isUpdating;
    bool _isSelectable;
    QMap<NodeItem*, Node*> _nodeMap;
    QMap<InputPort*, PortItem*> _inputPortMap;
    QList<ConnectionItem*> _connectionItems;

protected:
    /**
     * @brief _mainWindow the main window, in which this scene is used.
     */
    MainWindow* _mainWindow;

signals:
    /**
     * @brief nodeItemMoved is invoked, when a NodeItem has moved.
     */
    void nodeItemMoved(); // TODO: NEVER USED --> remove it
};
