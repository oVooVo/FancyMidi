#ifndef GRAPHICSPROXYWIDGET_H
#define GRAPHICSPROXYWIDGET_H

#include <QGraphicsProxyWidget>
#include <QKeyEvent>

class GraphicsProxyWidget : public QGraphicsProxyWidget
{
    Q_OBJECT
public:
    explicit GraphicsProxyWidget(QGraphicsItem *parent = 0);

};

#endif // GRAPHICSPROXYWIDGET_H
