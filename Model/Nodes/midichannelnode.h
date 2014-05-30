#ifndef MIDICHANNELNODE_H
#define MIDICHANNELNODE_H

#include "../Nodes/node.h"
#include "Settings/integersetting.h"

class MidiChannelNode : public Node
{
    Q_OBJECT
public:
    MidiChannelNode(QDataStream& stream);
    int channel() const;
};

#endif // MIDICHANNELNODE_H
