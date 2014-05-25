#ifndef TRIGGERNODE_H
#define TRIGGERNODE_H

#include "../Nodes/enableablenode.h"

#include <QTimer>
#include "Settings/integersetting.h"

class TriggerNode : public EnableableNode
{
    Q_OBJECT
public:
    TriggerNode(QPoint position, Project* parent);
    QString category() const { return "Generator"; }


private:
    REGISTER_DECL_NODETYPE(TriggerNode);
    QTimer _timer;
    int _time = 0;
};

#endif // TRIGGERNODE_H
