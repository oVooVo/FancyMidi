#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Model/node.h"
#include "Model/graphscene.h"
#include <QCloseEvent>

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
    bool save(QString filepath);
    bool open(QString filepath, Project* &project);
    void setProject(Project* project);
    bool canDropProject();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void updateSettingTable(Node* node);
    bool save();
    bool saveAs();
    void newProject();
    void open();
};

#endif // MAINWINDOW_H
