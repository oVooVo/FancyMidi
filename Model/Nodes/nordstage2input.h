#ifndef NORDSTAGE2INPUT_H
#define NORDSTAGE2INPUT_H
#include "../Nodes/enableablenode.h"
#include "Settings/midifiltersetting.h"

class NordStage2Input : public EnableableNode
{
    Q_OBJECT
public:
    NordStage2Input(QDataStream& stream);

    QString category() const { return "Input"; }

private:
    REGISTER_DECL_NODETYPE(NordStage2Input);

private slots:
    void filter(int channel, MidiKey key, QVariant data);
};

#endif // NORDSTAGE2INPUT_H
