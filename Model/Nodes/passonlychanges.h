#ifndef PASSONLYCHANGES_H
#define PASSONLYCHANGES_H

#include "node.h"

class PassOnlyChanges : public Node
{
    Q_OBJECT
public:
    PassOnlyChanges(QDataStream &stream);

    QString category() const { return "Logic"; }

private:
    QVariant _data;
    REGISTER_DECL_NODETYPE(PassOnlyChanges);
};

#endif // PASSONLYCHANGES_H
