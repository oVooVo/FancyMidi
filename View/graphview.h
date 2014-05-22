#pragma once

#include <QGraphicsView>

#include "Model/abstractgraphscene.h"

/**
 * @brief The GraphView class proviedes the main-view-widget of the graph with advanced features such as
 *  zooming and panning.
 */
class GraphView : public QGraphicsView
{
    Q_OBJECT
public:
    /**
     * @brief GraphView creates a new GraphView with given scene.
     * @param scene the scene that this view is listening to.
     */
    GraphView(QWidget *parent);

    /**
     * @brief getCurrentlyVisibleRegion returns the currently visible region.
     * @return the currently visible region.
     */
    QRectF getCurrentlyVisibleRegion() const;

signals:
    /**
     * @brief viewRectangleChanged is emitted when the visible region changed eg. on zoom or pan.
     */
    void viewRectangleChanged(QRectF);

private:
    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void scaleView(qreal scaleFactor);
    bool _pan;
    int _panStartX, _panStartY;
    void resizeEvent(QResizeEvent *event);
    bool eventFilter(QObject *, QEvent *);
    void popularizeVisibleRegionChange();

    bool _leftButtonPressed;
    bool _rubberBandKeyPressed;
};


