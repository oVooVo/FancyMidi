#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SettingWidgets/settingwidget.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    newProject();
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->actionSave_As, SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newProject()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setProject(Project *project)
{
    if (_project)
        delete _project;
    if (_scene)
        delete _scene;
    _project = project;
    _scene = new GraphScene(_project, this, this);
    ui->graphicsView->setScene(_scene);
    connect(_scene, SIGNAL(showSettings(Node*)), this, SLOT(updateSettingTable(Node*)));
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
        ui->nodeName->setText(node->name());
        ui->nodeInfoText->setText(node->getInfoText());
        foreach (Setting* s, node->settings()) {
            SettingWidget* settingWidget = SettingWidget::createNewSettingWidget(s, ui->settingFrame);
            ui->settingFrame->layout()->addWidget(settingWidget);
        }
    }
}

bool MainWindow::save(QString filepath)
{
    QFile file(filepath);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Cannot write file.",
                             QString("Could not open file \"%1\" for writing.").arg(filepath),
                             QMessageBox::Ok, QMessageBox::NoButton);
        return false;
    }
    QDataStream stream(&file);
    stream << _project;
    file.close();
    return true;
}

bool MainWindow::open(QString filepath, Project *&project)
{
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Cannot open file.",
                             QString("Could not open file \"%1\" for reading.").arg(filepath),
                             QMessageBox::Ok, QMessageBox::NoButton);
        return false;
    }
    QDataStream stream(&file);
    stream >> project;
    file.close();

    if (!project) {
        QMessageBox::warning(this, "Cannot read file.",
                             QString("Could not read file \"%1\".").arg(filepath),
                             QMessageBox::Ok, QMessageBox::NoButton);
        return false;
    }

    return true;
}

bool MainWindow::save()
{
    if (!_project->projectPath()) {
        return saveAs();
    } else {
        return save(_project->projectPath()->absoluteFilePath());
    }
}

bool MainWindow::saveAs()
{
    QString currentDirectory = _project->projectPath() ?
                _project->projectPath()->absoluteFilePath()
              : QDir::home().absolutePath();
    QString filepath = QFileDialog::getSaveFileName(this, "Save Project", currentDirectory);
    if (!filepath.isEmpty() && save(filepath)) {
        _project->setProjectPath(filepath);
        return true;
    }
    return false;
}

void MainWindow::newProject()
{
    if (!canDropProject()) return;

    setProject(new Project);
}

void MainWindow::open()
{
    if (!canDropProject()) return;

    QString currentDirectory = _project->projectPath() ?
                _project->projectPath()->absoluteFilePath()
              : QDir::home().absolutePath();
    QString filepath = QFileDialog::getOpenFileName(this, "Open Project", currentDirectory);
    Project* project;
    if (!filepath.isEmpty() && open(filepath, project)) {
        project->setProjectPath(filepath);
        setProject(project);
    }
}

bool MainWindow::canDropProject()
{
    if (!_project || _project->isSaved())
        return true;

    switch(QMessageBox::question(this, QString("Quit %1").arg(QApplication::applicationName()),
                                 "There are unsaved Changes.",
                                 QMessageBox::Save, QMessageBox::Abort, QMessageBox::Discard)) {
    case QMessageBox::Save:
        return save();
    case QMessageBox::Abort:
        return false;
    case QMessageBox::Discard:
        return true;
    }
    return true;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (!canDropProject())
        event->ignore();
    else
        event->accept();
}
