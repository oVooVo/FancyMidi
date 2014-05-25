#ifndef ENABLEABLENODE_H
#define ENABLEABLENODE_H

#include "../node.h"
#include "Settings/boolsetting.h"

class EnableableNode : public Node
{
public:
    EnableableNode(QDataStream& stream);

};

#endif // ENABLEABLENODE_H
