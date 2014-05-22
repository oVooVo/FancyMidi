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
    _hasCalculatedData = false;
    _projectPath = filepath;
    _isSaved = true;
    _update = false;
    _isStartupProject = false;
    _emergencyStopped = false;
    _checkSufficientMemoryUpToDate = false;
}

void Project::childEvent(QChildEvent *event)
{
    if (event->polished()) { // event->added() ||
        Node* node = qobject_cast<Node *>(event->child());
        if(node != NULL) {
            _nodes += node;
            Output* output = qobject_cast<Output *>(event->child());
            if(output != NULL) {
                _outputs += output;
            }
            /*Generator* generator = qobject_cast<Generator *>(event->child());
            if(generator != NULL) {
                _generators += generator;
            }
            */
            popularizeModelChange();
        }
    } else if (event->removed()) {
        if(_nodes.contains((Node*)event->child()))
            _nodes -= (Node*)event->child();
        if(_outputs.contains((Output*)event->child()))
            _outputs -= (Output*)event->child();
        /*
        if(_generators.contains((Generator*)event->child())) {
			_generators -= (Generator*)event->child();
        }*/
        popularizeModelChange();
    }
}

bool Project::isComplete()
{
    if (_abort) return true;
    if (checkSufficientMemory() && !sufficientMemory()) {
        _memoryTestMutex.lock();
        if (!_emergencyStopped) {
            emit exception(QString(tr("Insufficient Memory. Emergency stop.")));
            _emergencyStopped = true;
        }
        _memoryTestMutex.unlock();
        return true;
    }
	if(!_hasCalculatedData) { // We define a empty project as completed project.
        return true;
	}

    foreach(Output *dpo, _outputs)    {
        if (!dpo->isComplete() && dpo->getState() == Node::GOOD) {
            return false;
		}
    }
    return true;
}

bool Project::sufficientMemory()
{
    unsigned long limit = 1024 * 1024 * 200; // 200 MB
    unsigned long free = 0;

#ifdef __linux__
    //qDebug() << "you are running linux!";
    static struct sysinfo info;
    sysinfo(&info);
    free = info.mem_unit * (info.freeram);
#elif _WIN32
    //qDebug() << "you are running Windows!";
    /*MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
	free = status.ullAvailVirtual;*/
	return true;
#else
    //qDebug() << "Warning: OS not supported. No memorycheck available.";
    return true;
#endif

    if (free < limit) {
        //qDebug() << "free space: " << free/1024/1024 << "MB, limit: " << limit/1024/1024 << "MB, false";
        return false;
    } else {
        //qDebug() << "free space: " << free/1024/1024 << "MB, limit: " << limit/1024/1024 << "MB, true";
        return true;
    }
}

void Project::run()
{/*
    //qDebug() << "run";
    while (!isComplete())
        foreach (Generator *g, _generators)
			try {
				g->run();
			} catch(Exception e) {
				_memoryTestMutex.lock();
				if (!_emergencyStopped) {
					emit exception(QString(tr("Insufficient Memory. Emergency stop.")));
					_emergencyStopped = true;
					_abort = true;
				}
				_memoryTestMutex.unlock();
			}
	qDebug() << "Thread done";
    */
}

void Project::start()
{
    if (!_hasCalculatedData) {
        _abort = false;
        _emergencyStopped = false;
        _hasCalculatedData = true; // soon ;-)
        _checkSufficientMemoryUpToDate = false;
        int idealTCount = (QThread::idealThreadCount() > 0) ? QThread::idealThreadCount() : 1;
        //int idealTCount = 1;
        for (int i = 0; i < idealTCount; ++i)
        {
            GeneratorThread *t = new GeneratorThread(this);
            t->setAutoDelete(true);
            QThreadPool::globalInstance()->start(t);
        }
    }
}

void Project::stop()
{
	qDebug() << "stop called";
    if (_hasCalculatedData) {
        _hasCalculatedData = false; // This will couse the run method to stop.
        QThreadPool::globalInstance()->waitForDone();
		clear();
    }
    selfCheck();
}


void Project::play()
{
    start();
}

QFileInfo *Project::projectPath() const
{
    return _projectPath;
}

void Project::setProjectPath(QFileInfo* projectPath)
{
    _projectPath = projectPath;
}

bool Project::isSaved() const
{
    return _isSaved;
}

void Project::setSaved(bool isSaved) {
    if (isSaved != _isSaved) {
        _isSaved = isSaved;
        _isStartupProject = false;
        emit isSaveStatusChanged(isSaved);
    }
}

bool Project::isStartupProject() const
{
    return _isStartupProject;
}


QSet<Node *> Project::nodes() const
{
    return _nodes;
}

QDataStream &operator << (QDataStream &ostream, const Project *project)
{
    QList<Node*> nodeList = project->nodes().toList();
    ostream << nodeList;
    int count = 0;
    for(int i = 0; i < nodeList.count(); i++)
        for(int p = 0; p < nodeList[i]->getOutputs().count(); p++)
            count += nodeList[i]->getOutputs()[p]->getTargets().count();
    ostream << count;
    for(int i = 0; i < nodeList.count(); i++)
    {
        for(int p = 0; p < nodeList[i]->getInputs().count(); p++) {
            OutputPort* source = nodeList[i]->getInputs()[p]->getSource();
            if(source) {
                ostream << i << p;
                int sourceNodeIndex = nodeList.indexOf(source->getNode());
                ostream << sourceNodeIndex;
                int sourceNodePortIndex = source->getNode()->getOutputs().indexOf(source);
                ostream << sourceNodePortIndex;
            }
        }
    }

    return ostream;
}

QDataStream &operator >> (QDataStream &istream, Project *&project)
{
    project = new Project();
    QList<Node*> nodes;
    istream >> nodes;
    for(int i = 0; i < nodes.count(); i++)
        nodes[i]->setParent(project);
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
            nodes[i]->getInputs()[p]->connect(nodes[sourceNodeIndex]->getOutputs()[sourceNodePortIndex]);
    }
    project->selfCheck();
    project->setSaved(true);
    return istream;
}

void Project::setStartupProject()
{
    _isStartupProject = true;
}

void Project::popularizeModelChange()
{
    Q_ASSERT_X(isStopped(), "popularizeModelChange", "Project");
    if (_isSaved) {
        _isSaved = false;
        emit isSaveStatusChanged(false);
    }
    if(!_update) {
        emit modelChanged();
    }
}

void Project::popularizeNodesChange(QList<InputPort *> inputs)
{
    if (!inputs.isEmpty())  { //  !inputs.isEmpty() <=> connection deleted/created
        Q_ASSERT_X(isStopped(), "popularizeNodesChange", "Project");
    }
    if (_isSaved) {
        _isSaved = false;
        emit isSaveStatusChanged(false);
    }
    if (!_update) {
        emit nodesChanged(inputs);
    }
}

int Project::count() {
	// Exact count
	int count = 0;
	foreach(Output* output, _outputs) {
		if(output->isComplete())
			count = qMax(count, output->exactCount());
		else
			count = qMax(count, output->count());
	}
	// Do not count missing packets.
	foreach(Output* output, _outputs)
		if(output->getState() == Node::GOOD && !output->isComplete())
			count = qMin(count, output->count());
	return count;
}

void Project::beginUpdate() {
    _update = true;
}

void Project::endUpdate() {
    _update = false;
}

void Project::clear() {
    qDebug() << "clear";
	foreach(Node* node, _nodes)
		node->clear();
}

bool Project::isValid() const
{
    foreach (Node* node, _nodes)
		if (node->getState() == Node::RED)
            return false;
    return true;
}

void Project::selfCheck() {
	// Prepare
	foreach(Node* n, _nodes) {
		n->setState(Node::DEAD);
		n->selfCheck();
	}

	// Cycle detection
    //dfs1();

	// Reachable nodes
    //dfs2();abstractgraphscene
}

bool Project::isStopped()
{
    return !_hasCalculatedData;
}
/*
void Project::dfs1() {
	QHash<Port*, int> visited;
	QSet<Port*> finalized;
	foreach(Port* p, targets(_generators))
		dfs1(p, visited, finalized);
}
*//*
void Project::dfs1(Port* p, QHash<Port*, int> &visited, QSet<Port*> &finalized) {
    if(!finalized.contains(p)) {
        if(visited.contains(p)) { // Cycle found
            for(int i = visited[p]; i < visited.count(); i++) { // Mark the cycle
                Port* portR = visited.key(i);
                if(!finalized.contains(portR)) {
                    portR->getNode()->setState(Node::RED);
                }
            }
        }
		else {
            visited[p] = visited.count();
			foreach(Port* t, targets(p))
                dfs1(t, visited, finalized);
            finalized += p;
		}
    }
}*//*

void Project::dfs2() {
	QSet<Port*> visited;
	foreach(Node* n, _generators)
		dfs2(n, visited);
}*//*
void Project::dfs2(Node* n, QSet<Port*> &visited) {
    if(n->getState() == Node::DEAD && visited.contains(toPortSet(n->getInputs()))) {
		n->setState(Node::GOOD); // Mark the reachable node
        foreach(Port* p, targets(targets(n))) {
            visited += p;
			dfs2(p->getNode(), visited);
		}
	}
}

QSet<Port *> Project::targets(QSet<Port *> ps) {
	QSet<Port*> re;
	foreach(Port* p, ps)
		re += targets(p);
	return re;
}

QSet<Port*> Project::targets(Node* n) {
	QSet<Port*> re;
	foreach(OutputPort* p, n->getOutputs())
		re += p;
	return re;
}

QSet<Port*> Project::targets(QSet<Generator*> ns) {
	QSet<Port*> re;
	foreach(Node* n, ns)
		re += targets(n);
	return re;
}

QSet<Port*> Project::targets(OutputPort* p) {
	QSet<Port*> re;
	foreach(Port* t, p->getTargets())
		re += t;
	return re;
}

QSet<Port*> Project::toPortSet(QList<InputPort*> ps) {
	QSet<Port*> re;
	foreach(Port* t, ps)
		re += t;
	return re;
}

QSet<Port*> Project::targets(Port* port) {
	return port->isInput() ? targets(((InputPort*)port)->getNode()) : targets((OutputPort*)port);
}*/

bool Project::checkSufficientMemory()
{
    if (!_checkSufficientMemoryUpToDate) {
        _checkSufficientMemoryUpToDate = true;
        QSettings settings;
        settings.beginGroup("MainWindow");
        _checkSufficientMemory = settings.value("MemoryCheck", true).toBool();
        settings.endGroup();
    }
    return _checkSufficientMemory;
}

void Project::abort()
{
    _abort = true;
}

