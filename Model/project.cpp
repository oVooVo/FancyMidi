#include "project.h"

#include <QErrorMessage>
#include <QDebug>
#include <QCoreApplication>
#include <QThreadPool>
#include <QVector>
#include <QList>
#include <QSettings>
#include <QCryptographicHash>
#include "inputport.h"
#include "mainwindow.h"

class MainWindow;

#ifdef __linux__
    #include <stdio.h>
    #include <sys/sysinfo.h>
#elif _WIN32
    #include <windows.h>
#endif


Project::Project(QFileInfo *filepath, QObject *parent) : QObject(parent)
{
    _projectPath = filepath;
    _isSaved = true;
}

Project::~Project()
{
    if (_projectPath)
        delete _projectPath;
}

void Project::childEvent(QChildEvent *event)
{
    if (event->polished()) {
        Node* node = qobject_cast<Node *>(event->child());
        if(node != NULL) {
            _nodes += node;
            popularizeModelChange();
        }
    } else if (event->removed()) {
        if(_nodes.contains((Node*)event->child()))
            _nodes -= (Node*)event->child();
        popularizeModelChange();
    }
}

QFileInfo *Project::projectPath() const
{
    return _projectPath;
}

void Project::setProjectPath(QString filepath)
{
    if (!_projectPath)
        _projectPath = new QFileInfo();
    _projectPath->setFile(filepath);
}

bool Project::isSaved() const
{
    return _isSaved;
}

void Project::setSaved(bool isSaved) {
    if (isSaved != _isSaved) {
        _isSaved = isSaved;
        emit isSaveStatusChanged(isSaved);
    }
}

QSet<Node *> Project::nodes() const
{
    return _nodes;
}

QDataStream &operator << (QDataStream &ostream, const Project *project)
{
    ostream << Project::magicNumber();
    QList<Node*> nodeList = project->nodes().toList();
    ostream << nodeList;

    int count = 0;
    for(int i = 0; i < nodeList.count(); i++)
        for(int p = 0; p < nodeList[i]->outputPorts().count(); p++)
            count += nodeList[i]->outputPorts()[p]->targets().count();
    ostream << count;
    for(int i = 0; i < nodeList.count(); i++)
    {
        for(int p = 0; p < nodeList[i]->inputPorts().count(); p++) {
            OutputPort* source = nodeList[i]->inputPorts()[p]->source();
            if(source) {
                ostream << i << p;
                int sourceNodeIndex = nodeList.indexOf(source->node());
                ostream << sourceNodeIndex;
                int sourceNodePortIndex = source->node()->outputPorts().indexOf(source);
                ostream << sourceNodePortIndex;
            }
        }
    }

    return ostream;
}

QDataStream &operator >> (QDataStream &istream, Project *&project)
{
    QByteArray magic;
    istream >> magic;
    if (magic != Project::magicNumber()) {
        project = 0;
        return istream;
    }

    project = new Project();
    QList<Node*> nodes;
    istream >> nodes;
    for(int i = 0; i < nodes.count(); i++) {
        nodes[i]->setParent(project);
        nodes[i]->polish();
    }

    int count;
    istream >> count;
    for(int c = 0; c < count; c++) {
        int i, p;
        istream >> i >> p;
        int sourceNodeIndex;
        istream >> sourceNodeIndex;
        int sourceNodePortIndex;
        istream >> sourceNodePortIndex;
        if(nodes[i] && nodes[sourceNodeIndex])
            nodes[i]->inputPorts()[p]->connect(nodes[sourceNodeIndex]->outputPorts()[sourceNodePortIndex]);
    }

    project->setSaved(true);
    return istream;
}

void Project::popularizeModelChange()
{
    if (_isSaved) {
        _isSaved = false;
        emit isSaveStatusChanged(false);
    }
    emit modelChanged();
}

void Project::popularizeNodesChange(QList<InputPort *> inputs)
{
    if (_isSaved) {
        _isSaved = false;
        emit isSaveStatusChanged(false);
    }
    emit nodesChanged(inputs);
}

QByteArray Project::magicNumber()
{
    return QByteArray("FancyMidiProjectFile");
}

QString Project::name() const
{
    if (!_projectPath) return "Untitled";

    return _projectPath->fileName();
}

void Project::stop()
{
    for (Node* node : _nodes) {
        node->stop();
    }
}

void Project::start()
{
    for (Node* node : _nodes) {
        node->start();
    }
}
