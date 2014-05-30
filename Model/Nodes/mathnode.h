#ifndef MATHNODE_H
#define MATHNODE_H

#include "node.h"

class MathNode : public Node
{
    Q_OBJECT
public:
    MathNode(QDataStream& stream);

    QString category() const { return "Math"; }

protected:
    void updateData(const DataOutputPort *port) const;

    REGISTER_DECL_NODETYPE(MathNode);
};

#endif // MATHNODE_H
