#ifndef TIMERNODE_H
#define TIMERNODE_H

#include <QTimer>
#include "Settings/integersetting.h"

#include "../triggeroutputport.h"
#include "../triggerinputport.h"
#include "../datainputport.h"

class TimerNode : public Node
{
    Q_OBJECT
public:
    TimerNode(QDataStream& stream);
    QString category() const { return "Time"; }

    void trigger(const TriggerInputPort *in);

    void notify(const DataInputPort* in, const QVariant &data);


private:
    REGISTER_DECL_NODETYPE(TimerNode);
    QTimer _timer;
};

#endif // TIMERNODE_H
