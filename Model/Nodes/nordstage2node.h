#ifndef NORDSTAGE2NODE_H
#define NORDSTAGE2NODE_H

#include "../node.h"
#include "Settings/integersetting.h"
#include "Settings/midicommandselectsetting.h"

class NordStage2Node: public Node
{
    Q_OBJECT
public:
    NordStage2Node(QPoint position, Project *parent);
    int channel() const { return _intSetting->value(); }

    QString category() const { return "Keyboard"; }

private:
    IntegerSetting* _intSetting;
    MidiCommandSelectSetting* _midiSetting;
    REGISTER_DECL_NODETYPE(NordStage2Node);

public slots:
    void sendMidi();

signals:
    void channelChanged(int channel);


};

#endif // NORDSTAGE2NODE_H
