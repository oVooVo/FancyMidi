#ifndef TOINTEGERNODE_H
#define TOINTEGERNODE_H

#include "enableablenode.h"
#include "Settings/integersetting.h"

class ToIntegerNode : public EnableableNode
{
    Q_OBJECT
public:
    ToIntegerNode(QDataStream& stream);

    QString category() const { return "Math"; }

    REGISTER_DECL_NODETYPE(ToIntegerNode);
};

#endif // TOINTEGERNODE_H
