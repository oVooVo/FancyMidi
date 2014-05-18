#include "nordstage2.h"

void NordStage2::setOrganPreset(Preset preset)
{
    sendMidiControlCommand(3, preset == PresetI ? 0 : 127);
}

//void NordStage2::setOrganSwell()  //TODO
void NordStage2::setOrganDrawBar(quint8 number, quint8 value)
{
    if (value > 127) {
        qWarning() << "Expected level between 0 and 127 but got " << value << ".";
        return;
    }
    if (number >= 1 && number <= 9) {
        int drawbarkey = (number == 1 ? 9 : number + 12);
        sendMidiControlCommand(drawbarkey, value);
    } else {
        qWarning() << "Expected drawbar number between 1 and 9 but got " << number << ".";
    }
}

void NordStage2::setOrganPercussionEnable(Status status)
{
    sendMidiControlCommand(22, status);
}

void NordStage2::setOrganModel(OrganModel model)
{
    sendMidiControlCommand(23, model);
}

void NordStage2::setOrganVirbratoType(OrganVibratoType type)
{
    sendMidiControlCommand(24, (quint8) type);
}

void NordStage2::setVibratoEnable(Status status)
{
    sendMidiControlCommand(25, status);
}

void NordStage2::setOrganPercussionHarmonicThird(Status status)
{
    sendMidiControlCommand(26, status);
}

void NordStage2::setOrganPercussionFastDecay(Status status)
{
    sendMidiControlCommand(27, status);
}

void NordStage2::setOrganPercussionVolumeSoft(Status status)
{
    sendMidiControlCommand(28, status);
}

void NordStage2::setOrganOctaveShift(int shift)
{
    sendMidiControlCommand(99, encodeOctaveShift(shift));
}

void NordStage2::setOrganLevel(double level)
{
    sendMidiControlCommand(100, level);
}

void NordStage2::setOrganEnabled(Status status)
{
    sendMidiControlCommand(101, status);
}

