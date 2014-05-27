#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Model/Nodes/node.h"
#include "Model/graphscene.h"
#include <QCloseEvent>
#include "Model/minimapgraphscene.h"
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void stop() {}

private:
    Ui::MainWindow *ui;
    Project* _project = 0;
    GraphScene* _scene = 0;
    MinimapGraphScene* _minimapScene = 0;
    bool save(QString filepath);
    bool open(QString filepath, Project* &project);
    void setProject(Project* project);
    bool canDropProject();

    void writeSettings();
    void readSettings();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void updateSettingTable(QList<Node *> nodes);
    bool save();
    bool saveAs();
    void newProject();
    void open();
    void updateWindowTitle();
    void updateMinimapDelayed();
    void updateMinimap();
    void centerOn(QPointF center);
};

#endif // MAINWINDOW_H
