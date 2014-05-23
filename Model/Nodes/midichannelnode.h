#ifndef MIDICHANNELNODE_H
#define MIDICHANNELNODE_H

#include "../node.h"
#include "Settings/integersetting.h"

class MidiChannelNode : public Node
{
public:
    MidiChannelNode(QPoint position, Project* parent, QString name, QString tooltip = "");
    void setChannel(int channel);
    int channel() const { return _channelSetting->value(); }

private:
    IntegerSetting* _channelSetting;
};

#endif // MIDICHANNELNODE_H
