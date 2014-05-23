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


private:
    REGISTER_DECL_NODETYPE(TriggerNode);
    QTimer _timer;
    int _time = 0;
    IntegerSetting* _durationSetting;
    IntegerSetting* _intervallSetting;
};

#endif // TRIGGERNODE_H
