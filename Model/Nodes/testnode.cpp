#include "testnode.h"

REGISTER_DEFN_NODETYPE(TestNode);

TestNode::TestNode(QDataStream &stream) : Node(stream)
{
}
