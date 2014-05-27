#pragma once

#include "abstractgraphscene.h"

#include "project.h"
#include "View/nodeitem.h"
#include "View/temporaryconnection.h"


/**
 * @brief The GraphScene class represents the main view of the graph, with advanced features such as
 *  copy/paste, selecting items, remove items, drag and drop, ...
 * @see QGraphicsScene
 * @see AbstractGraphScene
 * @see Project
 */
class GraphScene : public AbstractGraphScene
{
    Q_OBJECT
public:
    /**
     * @brief GraphScene Creates the GraphScene based on a given Project and a parent
     * @param Project the given parent
     * @param parent the parent object (QWidget)
     */
    explicit GraphScene(Project* project, MainWindow* mainWindow, QObject *parent = 0);

    /**
     * @brief showFrame shows the frame with denoted id in all DisplayOutputs of this scene.
     * @param id the frame with this id is shown.
     */
	void showFrame(int id);

    /**
     * @brief lock locks drag&drop, copy&paste, entf and new connections
     */
    void lock();

    /**
     * @brief unlock unlocks drag&drop, copy&paste, entf and new connections
     */
    void unlock();

    /**
     * @brief getCenter returns the center of all NodeItems.
     * @param defaultValue is returned when this scene contains none NodeItem
     * @return the center of all NodeItems.
     */
    QPointF getCenter() const;


signals:
    /**
     * @brief showSettings is emitted when mainwindow has to show settings of the specified Node.
     */
    void showSettings(Node*);

    /**
     * @brief togglePlay is emitted when the project should start playing.
     */
    void togglePlay();

private:
    bool eventFilter(QObject *watched, QEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

    bool _locked;
    TemporaryConnection* _temporaryConnection;
    QGraphicsRectItem* _contentRect;
    QByteArray _copy;
    bool _strgPressed;
    void copy();
    QList<Node*> _copyPasteNodeList;

    QList<Node*> _pastedNodes; //Only for the laterly selection, not directly for copy&paste

private slots:
    void paste();
    void selectPastedNodes();

};


