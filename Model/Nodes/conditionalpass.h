#ifndef CONDITIONALPASS_H
#define CONDITIONALPASS_H

#include "node.h"
#include "../datainputport.h"
#include "../triggerinputport.h"


class ConditionalPass : public Node
{
    Q_OBJECT
public:
    ConditionalPass(QDataStream& stream);

    void trigger(const TriggerInputPort *in);
    void notify(const DataInputPort *in, const QVariant &data);

private:
    bool pass() const;

    REGISTER_DECL_NODETYPE(ConditionalPass);
};

#endif // CONDITIONALPASS_H
