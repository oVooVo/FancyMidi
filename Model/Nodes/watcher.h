#ifndef WATCHER_H
#define WATCHER_H

#include "node.h"

class Watcher : public Node
{
    Q_OBJECT
public:
    Watcher(QDataStream& stream);

    QString category() const { return "General"; }

    void notify(const DataInputPort *in, const QVariant &);

    REGISTER_DECL_NODETYPE(Watcher);
};

#endif // WATCHER_H
