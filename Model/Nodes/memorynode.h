#ifndef MEMORYNODE_H
#define MEMORYNODE_H

#include "node.h"
#include <QQueue>

class MemoryNode : public Node
{
    Q_OBJECT
public:
    MemoryNode(QDataStream& stream);

    QString category() const { return "Memory"; }

    void trigger(const TriggerInputPort *in);

private:
    QList<QVariant> _datas;
    REGISTER_DECL_NODETYPE(MemoryNode);
};

#endif // MEMORYNODE_H
