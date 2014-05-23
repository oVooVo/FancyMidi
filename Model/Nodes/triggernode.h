#ifndef TRIGGERNODE_H
#define TRIGGERNODE_H

#include "../node.h"

#include <QTimer>
#include "Settings/integersetting.h"

class TriggerNode : public Node
{
    Q_OBJECT
public:
    TriggerNode(QPoint position, Project* parent);
    QString category() const { return "Generator"; }

    QTimer _timer;

private:
    REGISTER_DECL_NODETYPE(TriggerNode);
    IntegerSetting* _timeOutSetting;
};

#endif // TRIGGERNODE_H
