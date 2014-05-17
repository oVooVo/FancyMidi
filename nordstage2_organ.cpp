#include "nordstage2.h"

void NordStage2::setOrganPreset(Preset preset)
{
    midi->sendMidiControlCommand(channel(), 3, preset == PresetI ? 0 : 127);
}

//void NordStage2::setOrganSwell()  //TODO
void NordStage2::setOrganDrawBar(quint8 number, quint8 value)
{
    if (number >= 1 && number <= 9) {
        int drawbarkey = (number == 1 ? 9 : number + 12);
        midi->sendMidiControlCommand(channel(), drawbarkey, value);
    } else {
        qWarning() << "Expected drawbar number between 1 and 9 but got " << number << ".";
    }
}

void NordStage2::setOrganPercussionEnable(Status status)
{
    midi->sendMidiControlCommand(channel(), 22, status == On ? 127 : 0);
}

void NordStage2::setOrganModel(OrganModel model)
{
    midi->sendMidiControlCommand(channel(), 23, model == B3 ? 0 : model == Vox ? 64 : 127);
}

void NordStage2::setOrganVirbratoType(OrganVibratoType type)
{
    int type_code;
    switch (type) {
    case V1: type_code = 0; break;
    case V2: type_code = 51; break;
    case V3: type_code = 102; break;
    case C1: type_code = 26; break;
    case C2: type_code = 77; break;
    case C3: type_code = 127; break;
    }

    midi->sendMidiControlCommand(channel(), 24, type_code);
}

void NordStage2::setVibratoEnable(Status status)
{
    midi->sendMidiControlCommand(channel(), 25, status == On ? 127 : 0);
}

void NordStage2::setOrganPercussionHarmonic(Status status)
{
    midi->sendMidiControlCommand(channel(), 26, status == On ? 127 : 0);
}

void NordStage2::setOrganPercussionSpeed(Status status)
{
    midi->sendMidiControlCommand(channel(), 27, status == On ? 127 : 0);
}

void NordStage2::setOrganPercussionLevel(Status status)
{
    midi->sendMidiControlCommand(channel(), 28, status == On ? 127 : 0);
}

void NordStage2::setOrganOctaveShift(int shift)
{
    midi->sendMidiControlCommand(channel(), 99, encodeOctaveShift(shift));
}

void NordStage2::setOrganLevel(quint8 level)
{
    midi->sendMidiControlCommand(channel(), 100, level);
}

void NordStage2::setOrganEnabled(Status status)
{
    midi->sendMidiControlCommand(channel(), 101, status == On ? 127 : 0);
}

