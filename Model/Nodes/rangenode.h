#ifndef RANGENODE_H
#define RANGENODE_H

#include "node.h"

class RangeNode : public Node
{
    Q_OBJECT
public:
    RangeNode(QDataStream& stream);

    QString category() const { return "Math"; }
    void notify(const DataInputPort *in, const QVariant &);

private:
    void calculate() const;

    REGISTER_DECL_NODETYPE(RangeNode);
};

#endif // RANGENODE_H
