#ifndef TIMERNODE_H
#define TIMERNODE_H

#include "../Nodes/enableablenode.h"

#include <QTimer>
#include "Settings/integersetting.h"

class TimerNode : public EnableableNode
{
    Q_OBJECT
public:
    TimerNode(QDataStream& stream);
    QString category() const { return "Time"; }


private:
    REGISTER_DECL_NODETYPE(TimerNode);
    QTimer _timer;
    int _time = 0;
};

#endif // TIMERNODE_H
