#ifndef RESULT_H
#define RESULT_H

#include "node.h"
#include "../triggerinputport.h"
#include "QVariant"
#include "../datainputport.h"

class Result : public Node
{
    Q_OBJECT
public:
    Result(QDataStream& stream);

    void trigger(const TriggerInputPort *port);
    void notify(const DataInputPort *port, const QVariant &data);
    QString category() const { return "General"; }
    REGISTER_DECL_NODETYPE(Result);
};

#endif // RESULT_H
