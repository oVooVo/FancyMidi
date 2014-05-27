#include "nodewidget.h"
#include <QSlider>
#include <QHBoxLayout>
#include <QSlider>

NodeWidget::NodeWidget(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout* layou = new QHBoxLayout();
    layou->setContentsMargins(0, 30, 0, 0);
    QSlider* slider = new QSlider(this);
    layou->addWidget(slider);
    setLayout(layou);
}

void NodeWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(QRectF(-30, -30, 60, 60), Qt::red);
    QWidget::paintEvent(event);
}
