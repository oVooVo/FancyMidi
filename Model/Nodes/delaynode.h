#ifndef DELAYNODE_H
#define DELAYNODE_H

#include "Settings/boolsetting.h"
#include "../triggerinputport.h"
#include "../datainputport.h"

class DelayNode : public Node
{
    Q_OBJECT
public:
    DelayNode(QDataStream& stream);

    QString category() const { return "Time"; }

    void trigger(const TriggerInputPort *in);
    void notify(const DataInputPort *in, const QVariant &data);

    REGISTER_DECL_NODETYPE(DelayNode);
};

#endif // DELAYNODE_H
