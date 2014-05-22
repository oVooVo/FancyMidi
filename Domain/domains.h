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

    static Domain* PresetDomain(quint8 midicode, QString name);
    static Domain* StatusDomain(quint8 midicode, QString name);
    static Domain* OrganModelDomain(quint8 midicode, QString name);
    static Domain* OrganVibratoTypeDomain(quint8 midicode, QString name);
    static Domain* PianoTypeDomain(quint8 midicode, QString name);
    static Domain* ClavinetEq1Domain(quint8 midicode, QString name);
    static Domain* ClavinetEq2Domain(quint8 midicode, QString name);
    static Domain* PianoAcousticsDomain(quint8 midicode, QString name);
    static Domain* PianoDynamicsDomain(quint8 midicode, QString name);
    static Domain* SynthArpeggioPatterDomain(quint8 midicode, QString name);
    static Domain* SynthVoiceModeDomain(quint8 midicode, QString name);
    static Domain* SynthUnisonoDomain(quint8 midicode, QString name);
    static Domain* SynthVibratoModeDomain(quint8 midicode, QString name);
    static Domain* SynthWaveFormDomain(quint8 midicode, QString name);
    static Domain* SynthOscillatorModeDomain(quint8 midicode, QString name);
    static Domain* SynthFilterTypeDomain(quint8 midicode, QString name);
    static Domain* Effect1TypeDomain(quint8 midicode, QString name);
    static Domain* Effect2TypeDomain(quint8 midicode, QString name);
    static Domain* EffectSourceDomain(quint8 midicode, QString name);
    static Domain* RotorSpeedDomain(quint8 midicode, QString name);
    static Domain* ReverbSizeDomain(quint8 midicode, QString name);
    static Domain* AmpSimTypeDomain(quint8 midicode, QString name);
    static Domain* SlotDomain(quint8 midicode, QString name);

    static Domain* Domain_0_1(quint8 midicode, QString name);
    static Domain* Domain_0_10(quint8 midicode, QString name);
    static Domain* Domain_m10_10(quint8 midicode, QString name);
    static Domain* Domain_m15_15(quint8 midicode, QString name);
    static Domain* Domain_03_45k(quint8 midicode, QString name);
    static Domain* Domain_5_45k(quint8 midicode, QString name);
    static Domain* Domain_20_21k(quint8 midicode, QString name);
    static Domain* Domain_200_8k(quint8 midicode, QString name);
    static Domain* Domain_003_523(quint8 midicode, QString name);

    static Domain* Domain_m7_6(quint8 midicode, QString name);
    static Domain* Domain_0_127(quint8 midicode, QString name);
    static Domain* Domain_1_52(quint8 midicode, QString name);
    static Domain* Domain_0_4(quint8 midicode, QString name);
    static Domain* Domain_80_128x32(quint8 midicode, QString name);
    static Domain* Domain_1_128(quint8 midicode, QString name);
    //void setSynthGlideRate(quint8 rate);    //TODO
};

#endif // DOMAINS_H
