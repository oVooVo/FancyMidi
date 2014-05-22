#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nordstage2.h"

#include "Model/graphscene.h"
#include "Model/Nodes/keyboardnode.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    Project* project = new Project();
    GraphScene* scene = new GraphScene(project, this);
    new KeyboardNode(QPoint(), project, "Test", "blabla", QSizeF(200, 161));

    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}
