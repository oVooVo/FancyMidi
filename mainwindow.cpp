#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nordstage2.h"

#include "Model/graphscene.h"
#include "SettingWidgets/settingwidget.h"
#include "View/graphview.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Project* project = new Project();
    GraphScene* scene = new GraphScene(project, this, this);
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
        foreach (Setting* s, node->settings()) {
            SettingWidget* settingWidget = SettingWidget::createNewSettingWidget(s, ui->settingFrame);
            ui->settingFrame->layout()->addWidget(settingWidget);
        }
    }
}
