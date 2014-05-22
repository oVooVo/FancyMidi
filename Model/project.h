#pragma once

#include <QObject>
#include <QFileInfo>
#include <QGraphicsScene>   //substitute by GraphScene
#include <QMutex>
#include <QRunnable>
#include <QReadWriteLock>
#include "node.h"
#include "outputport.h"
#include "output.h"
#include "View/portitem.h"

class MainWindow;


/**
 * @brief The Project class is the model of the graph consisting out of nodes
 */
class Project : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Project Constructs a new Project with given parent.
     * @param parent the parent of this Project.
     */
    Project(QFileInfo *filepath = 0, QObject *parent = 0);

    /**
     * @brief projectPath returns the path this project is stored.
     * @return the path this project is stored.
     */
    QFileInfo* projectPath() const;

    /**
     * @brief setProjectPath sets the path this project is stored.
     * @param projectPath the path this project is stored.
     */
    void setProjectPath(QFileInfo *projectPath);

    /**
     * @brief isSaved returns whether this project was saved after last change.
     * @return whether this project was saved after last change.
     */
    bool isSaved() const;

    /**
     * @brief isStopped returns whether this project's calculation has stopped.
     * @return whether this project's calculation has stopped.
     */
    bool isStopped();

    /**
     * @brief nodes returns all nodes associated with this project.
     * @return all nodes associated with this project.
     */
    QSet<Node*> nodes() const;

    /**
     * @brief shows the next frame on each DisplayOutput.
     */
    void show();

    /**
     * @brief count returns the number of frames.
     * @return the number of frames.
     */
    int count();

    /**
     * @brief selfCheck checks the consistency of each node and their relationships.
     */
    void selfCheck();

    /**
     * @brief beginUpdate locks this project.
     */
    void beginUpdate();

    /**
     * @brief endUpdate unlocks this project.
     */
    void endUpdate();

    /**
     * @brief isStartupProject returns whether this project is a startup project.
     *  A startup project is the project opened at startup of video2k, when there is no project to restore.
     * @return whether this project is a startup project.
     */
    bool isStartupProject() const;

    /**
     * @brief setStartupProject defines this project as startup project.
     */
    void setStartupProject();
	
    /**
     * @brief isValid returns whether this project is valid.
     * @return whether this project is valid.
     */
    bool isValid() const;

    /**
     * @brief run starts the generation of the CURRENT frame (according to _currentFrameId)
     */
    void run();

    /**
     * @brief stops the calculation of the project
     */
    void stop();

    /**
     * @brief isComplete returns whether the calculation has stopped.
     * @return whether the calculation has stopped.
     */
    bool isComplete();

    /**
     * @brief setSaved sets or removes the saved flag.
     * @param isSaved whether this project is saved.
     */
    void setSaved(bool isSaved);

    /**
     * @brief abort aborts the calculation. Similar to stop but data isn't cleared.
     */
    void abort();

public slots:
    /**
     * @brief start starts the calculation of the project
     */
    void start();

    /**
     * @brief play starts the visualization.
     */
    void play();

    /**
     * @brief popularizeModelChange popularizes model changes.
     */
    void popularizeModelChange();

    /**
     * @brief popularizeNodesChange popularizes node changes.
     * @param inputs all inputs that have changed.
     */
    void popularizeNodesChange(QList<InputPort *> inputs = QList<InputPort*>());

signals:
    /**
     * @brief modelChanged signalizes changing of this project.
     */
    void modelChanged();

    /**
     * @brief calculationStopped signalize calculation stopped.
     */
    void calculationStopped();

    /**
     * @brief nodesChanged signalizes changing of a node.
     * @param input all inputs that have changed.
     */
    void nodesChanged(QList<InputPort*> input = QList<InputPort*>());

    /**
     * @brief settingsChanged signalizes changing of a setting.
     */
    void settingsChanged();

    /**
     * @brief isSaveStatusChanged signalizes this project was saved or changed.
     */
    void isSaveStatusChanged(bool);

    /**
     * @brief exception an exception occured.
     * @param exp the message that should become displayed.
     */
	void exception(QString exp);

protected:
    /**
     * @brief childEvent a child event occures.
     * @param event the event.
     */
    void childEvent(QChildEvent* event);

private:
	void clear();
    bool _update;
    bool isReady();
    bool _isStartupProject;
    QMutex _memoryTestMutex;
    bool _emergencyStopped;
	void dfs1();
	void dfs1(Port* p, QHash<Port*, int> &visited, QSet<Port*> &finalized);
	void dfs2();
	void dfs2(Node* n, QSet<Port*> &visited);
    /*
	static QSet<Port*> targets(QSet<Port*> ps);
	static QSet<Port*> targets(Node* n);
	static QSet<Port*> targets(QSet<Generator*> ns);
	static QSet<Port*> targets(Port* p);
	static QSet<Port*> targets(OutputPort* p);
    static QSet<Port*> toPortSet(QList<InputPort*> ps);
    */
    bool sufficientMemory();
    bool checkSufficientMemory();           // caches _checkSufficientMemory
    bool _checkSufficientMemory;            // whether memory check should be performed.
    bool _checkSufficientMemoryUpToDate;    // whether _checkSufficientMemory is uptodate
    bool _abort;                            // whether current calculation should be aborted.

    QSet<Node*> _nodes;                     //becomes generated by childEvent

    //QSet<Generator*> _generators;           //becomes generated by childEvent

    QSet<Output*> _outputs;   //becomes generated by childEvent
    QFileInfo* _projectPath;
    bool _isSaved;
    bool _hasCalculatedData;

    class GeneratorThread : public QRunnable
	{
        public:
            GeneratorThread(Project *project)
                : _project(project) {}
            void run() {
                _project->run();
            }
        private:
            Project *_project;
            
    };
};

QDataStream &operator << (QDataStream &ostream, const Project *project);
QDataStream &operator >> (QDataStream &istream, Project *&project);



