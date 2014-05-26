#ifndef PERSISTENTNODE_H
#define PERSISTENTNODE_H

#include "../Nodes/enableablenode.h"
#include "Settings/boolsetting.h"


class PersistentNode : public EnableableNode
{
    Q_OBJECT
    REGISTER_DECL_NODETYPE(PersistentNode);
public:
    PersistentNode(QDataStream& stream);
    QString category() const { return "General"; }

private:
    BoolSetting* _boolSetting;
};

#endif // PERSISTENTNODE_H
