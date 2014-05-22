#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Model/node.h"

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
private slots:
    void updateSettingTable(Node* node);
};

#endif // MAINWINDOW_H
