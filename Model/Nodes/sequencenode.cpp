#include "sequencenode.h"
#include "Settings/sequencesetting.h"
#include "../inputport.h"
#include "../outputport.h"
#include "Settings/integersetting.h"
#include "Settings/infosetting.h"
#include "../dataoutputport.h"

REGISTER_DEFN_NODETYPE(SequenceNode);

SequenceNode::SequenceNode(QDataStream &stream) : Node(stream)
{
    setName("Sequence");
    addSetting(new SequenceSetting(this, "Sequence", ""));
    addSetting(new IntegerSetting(this, "Octave Range", "", 1, 10, 1, 1, true));
    addSetting(new IntegerSetting(this, "Octave Shift", "", -10, 10, 0, 0, true));
    addSetting(new IntegerSetting(this, "Octave" , "", 0, 48, 12, 12, true));
    addSetting(new InfoSetting(this, "Overall Length", "", "", true));

    addPort(new DataInputPort(this, "Absolute Key", ""));
    addPort(new DataInputPort(this, "Relative Key", ""));
    addPort(new DataInputPort(this, "Octave Range", "", false));
    addPort(new DataInputPort(this, "Octave Shift", "", false));
    addPort(new DataInputPort(this, "Octave", "", false));
    addPort(new DataOutputPort(this, "Note", ""));



    setting<SequenceSetting>("Octave Range")->connectPort(dataInputPort("Octave Range"));
    setting<SequenceSetting>("Octave Shift")->connectPort(dataInputPort("Octave Shift"));
    setting<SequenceSetting>("Octave")->connectPort(dataInputPort("Octave"));

    updateOverallLength();
}

int SequenceNode::makeAbsolute(double relative)
{
    return relative * (overallLength() - 1.0);
}

int SequenceNode::note(int key)
{
    int length = setting<SequenceSetting>("Sequence")->length();
    int note = setting<SequenceSetting>("Sequence")->note(length == 0 ? 1 : length);
    int octave = key / setting<SequenceSetting>("Sequence")->length();

    octave %= setting<IntegerSetting>("Octave Range")->value();
    octave += setting<IntegerSetting>("Octave Shift")->value();
    return note + octave * setting<IntegerSetting>("Octave")->value();
}

int SequenceNode::overallLength()
{
    int length = setting<SequenceSetting>("Sequence")->length();
    return length * setting<IntegerSetting>("Octave Range")->value();
}

void SequenceNode::updateOverallLength()
{
    setting<InfoSetting>("Overall Length")->setString(QString("Overall Length: %1").arg(overallLength()));
}

void SequenceNode::notify(const DataInputPort *in, const QVariant &data)
{
    if (in == dataInputPort("Absolute Key")) {
        dataOutputPort("Note")->setData(note(data.value<int>()));
    } else if (in == dataInputPort("Relative Key")) {
        dataOutputPort("Note")->setData(note(makeAbsolute(data.value<double>())));
    }
}
