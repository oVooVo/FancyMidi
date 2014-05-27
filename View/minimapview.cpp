#include "minimapview.h"


MinimapView::MinimapView(QWidget *parent) :
    QGraphicsView(parent)
{
    setRenderHint(QPainter::Antialiasing);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MinimapView::setMainViewRect(QRectF mainViewRect)
{
    _mainViewRect = mainViewRect;
    updateSceneRect();
}

void MinimapView::updateSceneRect()
{
    QRectF actual = mapToScene(viewport()->geometry()).boundingRect();
    if (_mainViewRect.isEmpty()) {
        _mainViewRect = actual;
    }

    setSceneRect(_mainViewRect);
    double xscale = actual.width()  / _mainViewRect.width();
    double yscale = actual.height() / _mainViewRect.height();
    double mscale = qMin(xscale, yscale);
    if (mscale > 1)
        mscale = 1;
    scale(mscale, mscale);
}

void MinimapView::resizeEvent(QResizeEvent *e)
{
    updateSceneRect();
    QGraphicsView::resizeEvent(e);
}
