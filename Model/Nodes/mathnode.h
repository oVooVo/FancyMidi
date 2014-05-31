#ifndef MATHNODE_H
#define MATHNODE_H

#include "node.h"
#include "../datainputport.h"
#include "../dataoutputport.h"

class MathNode : public Node
{
    Q_OBJECT
public:
    MathNode(QDataStream& stream);

    QString category() const { return "Math"; }

protected:
    void notify(const DataInputPort *in, const QVariant &);


private:
    REGISTER_DECL_NODETYPE(MathNode);
    void calculate() const;

};

#endif // MATHNODE_H
