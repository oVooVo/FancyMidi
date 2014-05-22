#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nordstage2.h"

#include "Model/graphscene.h"
#include "Model/Nodes/nordstage2node.h"
#include "SettingWidgets/settingwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    Project* project = new Project();
    GraphScene* scene = new GraphScene(project, this);
    new NordStage2Node(QPoint(), project);

    ui->graphicsView->setScene(scene);
    connect(scene, SIGNAL(showSettings(Node*)), this, SLOT(updateSettingTable(Node*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateSettingTable(Node* node)
{
    delete ui->settingFrame->layout();
    foreach(QObject* o, ui->settingFrame->children())
        delete o;
    ui->settingFrame->setLayout(new QVBoxLayout());
    if (!node) {
        ui->noNodeSelectedHint->show();
        ui->nodePropertyHead->hide();
    } else {
        ui->noNodeSelectedHint->hide();
        ui->nodePropertyHead->show();
        ui->nodeName->setText(node->getName());
        ui->nodeInfoText->setText(node->getInfoText());
        foreach (Setting* s, node->getSettings()) {
            SettingWidget* settingWidget = SettingWidget::createNewSettingWidget(s, ui->settingFrame);
            ui->settingFrame->layout()->addWidget(settingWidget);
        }
    }
}
