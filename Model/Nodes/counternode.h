#ifndef COUNTERNODE_H
#define COUNTERNODE_H

#include "node.h"

class CounterNode : public Node
{
    Q_OBJECT
public:
    CounterNode(QDataStream &stream);

    QString category() const { return "Logic"; }

private:
    int _currentCount = 0;

    REGISTER_DECL_NODETYPE(CounterNode);
};

#endif // COUNTERNODE_H
