#ifndef MEMORYMAPNODE_H
#define MEMORYMAPNODE_H

#include "node.h"

class MemoryMapNode : public Node
{
    Q_OBJECT
    QString category() const { return "Memory"; }
public:
    MemoryMapNode(QPoint position, Project* parent);
    MemoryMapNode(QDataStream& stream);

    void trigger(const TriggerInputPort *in);

private:
    QMap<int, QVariant> _data;
    int _readKey = 0;
    int _writeKey = 0;
    QVariant _writeValue;

    REGISTER_DECL_NODETYPE(MemoryMapNode);
};

#endif // MEMORYMAPNODE_H
