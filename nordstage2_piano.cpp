#include "nordstage2.h"

void NordStage2::setPianoType(PianoType type)
{
    sendMidiControlCommand(8, type);
}

void NordStage2::setPianoModel(int model)
{
    sendMidiControlCommand(29, encodePianoModel(model));
}

void NordStage2::setPianoSlotDetune(int detune)
{
    if (detune < 0 || detune > 4) {
        qWarning() << "Expected slot detune between 0 and 4 but got " << detune << ".";
        return;
    }
    quint8 code = (32 * detune) - (detune / 4);
    sendMidiControlCommand(5, code);
}

void NordStage2::setClavEQ1(ClavinetEq1 eq)
{
    sendMidiControlCommand(30, eq);
}

void NordStage2::setClavEQ2(ClavinetEq2 eq)
{
    sendMidiControlCommand(31, eq);
}

void NordStage2::setClavModelType(int model)
{
    sendMidiControlCommand(65, encodePianoModel(model));
}

void NordStage2::setPianoDynamics(PianoDynamic dyn)
{
    sendMidiControlCommand(33, dyn);
}

void NordStage2::setPianoAcoustic(PianoAcoustics pa)
{
    sendMidiControlCommand(98, pa);
}

void NordStage2::setPianoOctaveShift(int shift)
{
    sendMidiControlCommand(105, encodeOctaveShift(shift));
}

void NordStage2::setPianoLevel(double level)
{
    sendMidiControlCommand(106, encodeLevel(level));
}

void NordStage2::setPianoEnable(Status status)
{
    sendMidiControlCommand(107, status);
}

void NordStage2::setPianoPedalNoise(Status status)
{
    sendMidiControlCommand(108, status);
}







