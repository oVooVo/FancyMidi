#ifndef NORDSTAGE2INPUT_H
#define NORDSTAGE2INPUT_H
#include "../node.h"
#include "Settings/midifiltersetting.h"

class NordStage2Input : public Node
{
    Q_OBJECT
public:
    NordStage2Input(QPoint position, Project *parent);

    QString category() const { return "Input"; }

private:
    MidiFilterSetting* _midiFilter;
    REGISTER_DECL_NODETYPE(NordStage2Input);

private slots:
    void filter(int channel, MidiKey key, QVariant data);
};

#endif // NORDSTAGE2INPUT_H
