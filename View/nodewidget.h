#ifndef NODEWIDGET_H
#define NODEWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

class NodeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NodeWidget(QWidget *parent = 0);

    void paintEvent(QPaintEvent* event);


signals:

public slots:

};

#endif // NODEWIDGET_H
