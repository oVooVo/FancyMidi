#pragma once

#include <QGraphicsView>
#include "Model/minimapgraphscene.h"
#include <QResizeEvent>

/**
 * @brief The MinimapView class provides minimap-view-widget.
 */
class MinimapView : public QGraphicsView
{
    Q_OBJECT
public:
    /**
     * @brief MinimapView creates a new minimap view out of a given parent.
     * @param parent the parent of the minimap view.
     */
    explicit MinimapView(QWidget* parent = 0);

    void setMainViewRect(QRectF mainViewRect);

protected:
    void resizeEvent(QResizeEvent* e);

private:
    QRectF _mainViewRect;
    void updateSceneRect();

};


