#ifndef MIDICHANNELNODE_H
#define MIDICHANNELNODE_H

#include "../Nodes/enableablenode.h"
#include "Settings/integersetting.h"

class MidiChannelNode : public EnableableNode
{
public:
    MidiChannelNode(QPoint position, Project* parent, QString name, QString tooltip = "");
    void setChannel(int channel);
    int channel() const { return setting<IntegerSetting>("Channel")->value(); }
};

#endif // MIDICHANNELNODE_H
