#include "graphview.h"

#include <QWheelEvent>
#include <QScrollBar>

#include <QDebug>

GraphView::GraphView(QWidget* parent = 0) : QGraphicsView(parent)
{
    _pan = false;
    _rubberBandKeyPressed = false;
    setRenderHint(QPainter::Antialiasing);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    installEventFilter(this);
}

void GraphView::scaleView(qreal scaleFactor)
{
    qreal factor = matrix().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.5 || factor > 2)
        return;
    scale(scaleFactor, scaleFactor);
    popularizeVisibleRegionChange();
}

void GraphView::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, event->delta() / 480.0));
    popularizeVisibleRegionChange();
}

void GraphView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        _pan = true;
        _panStartX = event->x();
        _panStartY = event->y();
        setCursor(Qt::ClosedHandCursor);
        event->accept();
        popularizeVisibleRegionChange();

        return;
    } else if (event->button() == Qt::LeftButton)
    {
        _leftButtonPressed = true;
    }

    event->ignore();
    QGraphicsView::mousePressEvent(event);
}

void GraphView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        _pan = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
        popularizeVisibleRegionChange();
        return;
    }
    QGraphicsView::mouseReleaseEvent(event);
    if (event->button() == Qt::LeftButton)
    {
        _leftButtonPressed = false;
        if (!_rubberBandKeyPressed) {
            setDragMode(QGraphicsView::NoDrag);
        }
    }
    event->ignore();
}

void GraphView::mouseMoveEvent(QMouseEvent *event)
{
    if (_pan)
    {
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (event->x() - _panStartX));
        verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->y() - _panStartY));
        _panStartX = event->x();
        _panStartY = event->y();
        event->accept();
        popularizeVisibleRegionChange();
        return;
    }
    event->ignore();
    QGraphicsView::mouseMoveEvent(event);

}

void GraphView::popularizeVisibleRegionChange()
{
    emit viewRectangleChanged(getCurrentlyVisibleRegion());
}

QRectF GraphView::getCurrentlyVisibleRegion() const
{

        QPointF topLeft = mapToScene (0, 0);
        QPointF bottomRight = mapToScene (this->width(), this->height());

        return QRectF (topLeft, bottomRight);
}

void GraphView::resizeEvent(QResizeEvent *event)
{
    popularizeVisibleRegionChange();
    QGraphicsView::resizeEvent(event);
}

bool GraphView::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::KeyPress && ((QKeyEvent*) event)->key() == 16777248) { //SHIFT
        _rubberBandKeyPressed = true;
        setDragMode(QGraphicsView::RubberBandDrag);
    } else if (event->type() == QEvent::KeyRelease && ((QKeyEvent*) event)->key() == 16777248) { //SHIFT
        _rubberBandKeyPressed = false;
        if (!_leftButtonPressed) {
            setDragMode(QGraphicsView::NoDrag);
        }
    } else if (event->type() == QEvent::KeyPress && ((QKeyEvent*) event)->key() == 16777249) { //STRG
        /*
         * Unfortunately, there seems to be no way to extend rubberband selections unless hacking the code like in the
         * link but override the rubberbandselection-methodes in this class.
         * The latter seems to be to much overhead, so we have to live with unextandable rubberband selections.
         * http://asmaloney.com/2012/06/code/extending-selections-in-qgraphicsview/
         */
        // enable extension
    } else if (event->type() == QEvent::KeyRelease && ((QKeyEvent*) event)->key() == 16777249) { //STRG
        // disable extension
    }
    return QGraphicsView::eventFilter(watched, event);
}
