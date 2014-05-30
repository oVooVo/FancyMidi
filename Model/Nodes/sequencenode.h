#ifndef SEQUENCENODE_H
#define SEQUENCENODE_H

#include "node.h"

class SequenceNode : public Node
{
    Q_OBJECT
public:
    SequenceNode(QDataStream& stream);

    QString category() const { return "Notes"; }

private:
    int note(int key);
    int makeAbsolute(double relative);
    int overallLength();

private slots:
    void updateOverallLength();

    REGISTER_DECL_NODETYPE(SequenceNode);
};

#endif // SEQUENCENODE_H
