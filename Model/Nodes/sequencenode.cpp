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

    addPort(new DataOutputPort(this, "Absolute Key", ""));
    addPort(new DataOutputPort(this, "Relative Key", ""));
    addPort(new DataOutputPort(this, "Note", ""));
    /*
    connect(dataInputPort("Absolute Key"), &DataInputPort::receivedData, [this](QVariant data) {
        if (!data.canConvert<int>()) return;

        int key = data.value<int>();
        if (setting<SequenceSetting>("Sequence")->length() > 0)
            outputPort("Note")->send(note(key));
    });

    connect(inputPort("Relative Key"), &InputPort::receivedData, [this](QVariant data) {
        if (!data.canConvert<double>()) return;

        double key = data.value<double>();
        if (setting<SequenceSetting>("Sequence")->length() > 0)
            outputPort("Note")->send(note(makeAbsolute(key)));
    });*/

    connect(setting<IntegerSetting>("Octave Range"), SIGNAL(changed()), this, SLOT(updateOverallLength()));
    connect(setting<IntegerSetting>("Octave Shift"), SIGNAL(changed()), this, SLOT(updateOverallLength()));
    connect(setting<SequenceSetting>("Sequence"), SIGNAL(changed()), this, SLOT(updateOverallLength()));
    updateOverallLength();
}

int SequenceNode::makeAbsolute(double relative)
{
    return relative * (overallLength() - 1.0);
}

int SequenceNode::note(int key)
{
    int note = setting<SequenceSetting>("Sequence")->note(key % setting<SequenceSetting>("Sequence")->length());
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
