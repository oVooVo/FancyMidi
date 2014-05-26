#ifndef MEMORYNODE_H
#define MEMORYNODE_H

#include "node.h"

class MemoryNode : public Node
{
    Q_OBJECT
public:
    MemoryNode(QDataStream& stream);

    QString category() const { return "Memory"; }

private:
    QVariant _data;
    REGISTER_DECL_NODETYPE(MemoryNode);
};

#endif // MEMORYNODE_H
