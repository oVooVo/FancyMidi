#ifndef COUNTERNODE_H
#define COUNTERNODE_H

#include "node.h"
#include "../triggerinputport.h"
#include "../triggeroutputport.h"
#include "../datainputport.h"
#include "../dataoutputport.h"

class CounterNode : public Node
{
    Q_OBJECT
public:
    CounterNode(QDataStream &stream);

    QString category() const { return "General"; }
    void trigger(const TriggerInputPort* in);

private:
    int _currentCount = 0;
    int _max = 1;

    REGISTER_DECL_NODETYPE(CounterNode);
};

#endif // COUNTERNODE_H
