#ifndef SWITCH_H
#define SWITCH_H

#include "node.h"

class Switch : public Node
{
    Q_OBJECT
public:
    Switch(QDataStream& stream);

    QString category() const { return "Logic"; }

    void trigger(const TriggerInputPort *);


    REGISTER_DECL_NODETYPE(Switch);
};

#endif // SWITCH_H
