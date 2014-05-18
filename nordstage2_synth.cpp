#include "nordstage2.h"

void NordStage2::setSynthOctaveShift(int shift)
{
    sendMidiControlCommand(111, encodeOctaveShift(shift));
}

void NordStage2::setSynthLevel(double level)
{
    sendMidiControlCommand(112, encodeLevel(level));
}

void NordStage2::setSynthEnable(Status status)
{
    sendMidiControlCommand(113, status);
}

void NordStage2::setSynthGlideRate(quint8 rate)
{
    sendMidiControlCommand(34, rate);
}

void NordStage2::setSynthArpOnOff(Status status)
{
    sendMidiControlCommand(109, status);
}

void NordStage2::setSynthArpMstClk(Status status)
{
    sendMidiControlCommand(12, status);
}

void NordStage2::setSynthArpRate(int rate)
{
    sendMidiControlCommand(102, encodeRate(rate));
}

void NordStage2::setSynthArpPattern(SynthArpPattern pattern)
{
    sendMidiControlCommand(103, pattern);
}

void NordStage2::setSynthArpRange(int range)
{
    quint8 code = 0;
    switch (range) {
    case 1: code = 0; break;
    case 2: code = 43; break;
    case 3: code = 85; break;
    case 4: code = 127; break;
    default:
        qWarning() << "Expected synth arpeggiator range between 1 and 4 (was" << range << ").";
    }
    sendMidiControlCommand(104, code);
}

void NordStage2::setSynthVoiceMode(SynthVoiceMode mode)
{
    sendMidiControlCommand(36, mode);
}

void NordStage2::setSynthUnison(SynthUnison mode)
{
    sendMidiControlCommand(37, mode);
}

void NordStage2::setSynthVibratoMode(SynthVibratoMode mode)
{
    sendMidiControlCommand(38, mode);
}

void NordStage2::setSynthModEnvelopeAttack(double attack)
{
    sendMidiControlCommand(38, encodeAttack(attack));
}

void NordStage2::setSynthModEnvelopeDecay(double decay)
{
    sendMidiControlCommand(40, encodeDecayOrRelease(decay));

}

void NordStage2::setSynthModEnvelopeRelease(double release)
{
    sendMidiControlCommand(41, encodeDecayOrRelease(release));
}

void NordStage2::setSynthModEnvelopeVelocity(Status on)
{
    sendMidiControlCommand(42, on);
}

void NordStage2::setSynthLFORate(double freq)
{
    sendMidiControlCommand(115, encodeLowFreq(freq));
}

void NordStage2::setSynthLFOWaveform(SynthWaveForm waveform)
{
    sendMidiControlCommand(116, waveform);
}

void NordStage2::setSynthLFOMasterClk(Status status)
{
    sendMidiControlCommand(13, status);
}

void NordStage2::setSynthLFOMasterClk(SynthOscillatorMode mode)
{
    sendMidiControlCommand(43, mode);
}

void NordStage2::setSynthWaveformSelect(int number)
{
    int n = limit(1, number, 128, "synth waveform");
    sendMidiControlCommand(44, n - 1);
}

void NordStage2::setSynthOscillatorShape(double shape)
{
    double n = limit(0.0, shape, 10.0, "synth oscillator shape");
    sendMidiControlCommand(45, encode_0_10(n));
}

void NordStage2::setSynthOscillatorSkipSampleAttack(Status status)
{
    sendMidiControlCommand(45, status);

}

void NordStage2::setSynthOscillatorShapeMod(double mod)
{
    double m = limit(-10.0, mod, 10.0, "synth oscillator shape mod");
    sendMidiControlCommand(46, encode_m10_10(m));
}

void NordStage2::setSynthFilterFrequency(double freq)
{
    sendMidiControlCommand(48, encodeMidFreq(freq));
}

void NordStage2::setSynthFilterResonance(double res)
{
    sendMidiControlCommand(49, encode_0_10(res));
}

void NordStage2::setSynthFilterVelocityEnvelopeMod(double ve)
{
    sendMidiControlCommand(2, encode_m10_10(ve));
}

void NordStage2::setSynthFilterLFOMod(double mod)
{
    sendMidiControlCommand(51, encode_0_10(mod));
}

void NordStage2::setSynthFilterKeyboardTrack(Status status)
{
    sendMidiControlCommand(52, status);
}

void NordStage2::setSynthFilterType(SynthFilterType type)
{
    sendMidiControlCommand(53, type);
}

void NordStage2::setSynthAmpEnvelopeAttack(double attack)
{
    sendMidiControlCommand(54, encodeAttack(attack));
}

void NordStage2::setSynthAmpEnvelopeDecay(double decay)
{
    sendMidiControlCommand(55, encodeDecayOrRelease(decay));
}

void NordStage2::setSynthAmpEnvelopeRelease(double release)
{
    sendMidiControlCommand(56, encodeDecayOrRelease(release));
}

void NordStage2::setSynthAmpEnvelopeVelocity(Status status)
{
    sendMidiControlCommand(57, status);
}
