#ifndef DOMAINS_H
#define DOMAINS_H

#include "domain.h"
#include "discretedomain.h"
#include "doubledomain.h"
#include "integerdomain.h"

class Domains
{
public:
    Domains();

    static Domain* PresetDomain(MidiKey midiKey, QString name);
    static Domain* StatusDomain(MidiKey midiKey, QString name);
    static Domain* OrganModelDomain(MidiKey midiKey, QString name);
    static Domain* OrganVibratoTypeDomain(MidiKey midiKey, QString name);
    static Domain* PianoTypeDomain(MidiKey midiKey, QString name);
    static Domain* ClavinetEq1Domain(MidiKey midiKey, QString name);
    static Domain* ClavinetEq2Domain(MidiKey midiKey, QString name);
    static Domain* PianoAcousticsDomain(MidiKey midiKey, QString name);
    static Domain* PianoDynamicsDomain(MidiKey midiKey, QString name);
    static Domain* SynthArpeggioPatterDomain(MidiKey midiKey, QString name);
    static Domain* SynthVoiceModeDomain(MidiKey midiKey, QString name);
    static Domain* SynthUnisonoDomain(MidiKey midiKey, QString name);
    static Domain* SynthVibratoModeDomain(MidiKey midiKey, QString name);
    static Domain* SynthWaveFormDomain(MidiKey midiKey, QString name);
    static Domain* SynthOscillatorModeDomain(MidiKey midiKey, QString name);
    static Domain* SynthFilterTypeDomain(MidiKey midiKey, QString name);
    static Domain* Effect1TypeDomain(MidiKey midiKey, QString name);
    static Domain* Effect2TypeDomain(MidiKey midiKey, QString name);
    static Domain* EffectSourceDomain(MidiKey midiKey, QString name);
    static Domain* RotorSpeedDomain(MidiKey midiKey, QString name);
    static Domain* ReverbSizeDomain(MidiKey midiKey, QString name);
    static Domain* AmpSimTypeDomain(MidiKey midiKey, QString name);
    static Domain* SlotDomain(MidiKey midiKey, QString name);

    static Domain* Domain_0_1(MidiKey midiKey, QString name);
    static Domain* Domain_0_10(MidiKey midiKey, QString name);
    static Domain* Domain_m10_10(MidiKey midiKey, QString name);
    static Domain* Domain_m15_15(MidiKey midiKey, QString name);
    static Domain* Domain_03_45k(MidiKey midiKey, QString name);
    static Domain* Domain_5_45k(MidiKey midiKey, QString name);
    static Domain* Domain_20_21k(MidiKey midiKey, QString name);
    static Domain* Domain_200_8k(MidiKey midiKey, QString name);
    static Domain* Domain_003_523(MidiKey midiKey, QString name);

    static Domain* Domain_m7_6(MidiKey midiKey, QString name);
    static Domain* Domain_0_127(MidiKey midiKey, QString name);
    static Domain* Domain_1_52(MidiKey midiKey, QString name);
    static Domain* Domain_0_4(MidiKey midiKey, QString name);
    static Domain* Domain_80_128x32(MidiKey midiKey, QString name);
    static Domain* Domain_1_128(MidiKey midiKey, QString name);
    //void setSynthGlideRate(quint8 rate);    //TODO
};

#endif // DOMAINS_H
