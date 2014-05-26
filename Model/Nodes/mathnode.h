#ifndef MATHNODE_H
#define MATHNODE_H

#include "enableablenode.h"

class MathNode : public EnableableNode
{
    Q_OBJECT
public:
    MathNode(QDataStream& stream);

    QString category() const { return "Math"; }

    REGISTER_DECL_NODETYPE(MathNode);

private slots:
    void calculate();
};

#endif // MATHNODE_H
