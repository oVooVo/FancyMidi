#include "minimapgraphscene.h"
#include <QGraphicsSceneMouseEvent>

#include <QDebug>

MinimapGraphScene::MinimapGraphScene(MainWindow *mainWindow, Project *model, QObject *parent) :
    AbstractGraphScene(model, mainWindow, parent, false)
{
    _visibleRect.setBrush(QColor(128, 128, 255, 50));
    _visibleRect.setPen(QColor(0, 0, 128, 255));
    addItem(&_visibleRect);
}

void MinimapGraphScene::setModel(Project *model)
{
    AbstractGraphScene::setModel(model);
}

void MinimapGraphScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    emit doubleClick(event->scenePos());
}

void MinimapGraphScene::setVisibleRect(QRectF rect)
{
    _visibleRect.setRect(rect);
    update();
}
