#ifndef MEMORYNODE_H
#define MEMORYNODE_H

#include "../node.h"

class MemoryNode : public Node
{
    Q_OBJECT
public:
    MemoryNode(QPoint position, Project* parent);
    MemoryNode(QDataStream& stream);

private:
    QMap<int, QVariant> _data;
    int _readKey = 0;
    int _writeKey = 0;
    QVariant _writeValue;

private slots:
    void write();
    void read();


    REGISTER_DECL_NODETYPE(MemoryNode);
};

#endif // MEMORYNODE_H
