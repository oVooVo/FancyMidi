#ifndef TRIGGERNODE_H
#define TRIGGERNODE_H

#include "../node.h"

#include <QTimer>

class TriggerNode : public Node
{
    Q_OBJECT
public:
    TriggerNode(QPoint position, Project* parent);
    QString category() const { return "Generator"; }

    QTimer timer;

private:
    REGISTER_DECL_NODETYPE(TriggerNode);
};

#endif // TRIGGERNODE_H
