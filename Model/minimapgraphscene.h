#pragma once

#include "abstractgraphscene.h"

/**
 * @brief The MinimapGraphScene class represents the minimap view of the graph.
 */
class MinimapGraphScene : public AbstractGraphScene
{
    Q_OBJECT
public:
    /**
     * @brief MinimapGraphScene creates a new MinimapGraphScene out of a given model an parent.
     * @param model the visualized model.
     * @param parent the parent.
     */
    explicit MinimapGraphScene(MainWindow* mainWindow, Project* model = 0, QObject *parent = 0);

    void setVisibleRect(QRectF rect);

    /**
     * @brief setModel sets the given model as project of this Scene.
     * @param model the new project.
     */
    void setModel(Project* model);  //make protected setModel public

signals:
    /**
     * @brief doubleClick is emitted when a double click occurs.
     * @param scenePos the position where the doubleclick occurs.
     */
    void doubleClick(QPointF scenePos);

private:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    QGraphicsRectItem _visibleRect;
};


