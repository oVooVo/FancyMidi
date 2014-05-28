#ifndef SWITCH_H
#define SWITCH_H

#include "node.h"

class Switch : public Node
{
    Q_OBJECT
public:
    Switch(QDataStream& stream);



    REGISTER_DECL_NODETYPE(Switch);
};

#endif // SWITCH_H
