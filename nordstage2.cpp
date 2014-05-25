#include "nordstage2.h"
#include "midihandler.h"
#include <QDebug>

NordStage2* NordStage2::CHANNELS[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

const QMap<QString, MidiKey> NordStage2::CODES = NordStage2::createProperties().codes;
const QMap<MidiKey, QString> NordStage2::NAMES = NordStage2::createProperties().names;
const QMap<MidiKey, Domain*> NordStage2::DOMAINS = NordStage2::createProperties().domains;

const QMap<QString, QStringList> NordStage2::PROPERTIES = NordStage2::calculateProperties();

void copy(const QMap<MidiKey, Domain*> src, QMap<MidiKey, Domain*> &dest, Keyboard* keyboard)
{
    dest.clear();
    for (MidiKey key : src.keys()) {
        dest.insert(key, src[key]->copy(keyboard));
    }
}

NordStage2::NordStage2(int channel, QObject* parent) : Keyboard(channel, parent)
{
    copy(DOMAINS, _domains, this);
    installReceiver(channel);
}

NordStage2::~NordStage2()
{
    qDeleteAll(_domains.values());
}

Domain* NordStage2::getDomain(QString key)
{
    if (!CODES.keys().contains(key)) return 0;
    if (!_domains.keys().contains(CODES[key])) return 0;
    return _domains[CODES[key]];
}

QStringList NordStage2::getKeys()
{
    return CODES.keys();
}

NordStage2::Triple NordStage2::createProperties()
{
    QMap<QString, MidiKey> codes;
    QMap<MidiKey, QString> properties;
    QMap<MidiKey, Domain*> domains;

    auto reg = [&](Domain* domain)
    {
        codes.insert(domain->name(), domain->midiKey());
        properties.insert(domain->midiKey(), domain->name());
        domains.insert(domain->midiKey(), domain);
    };

    reg(Domains::PresetDomain(MidiKey(MidiKey::ControlChange, 3), "Organ.Preset"));
    //TODO reg(Domain::??(MidiKey(MidiKey::ControlChange, MidiCode), "Organ.Swell", -1, 0));
    reg(Domains::Domain_0_127(MidiKey(MidiKey::ControlChange, 9), "Organ.Draw Bar 1"));
    reg(Domains::Domain_0_127(MidiKey(MidiKey::ControlChange, 14), "Organ.Draw Bar 2"));
    reg(Domains::Domain_0_127(MidiKey(MidiKey::ControlChange, 15), "Organ.Draw Bar 3"));
    reg(Domains::Domain_0_127(MidiKey(MidiKey::ControlChange, 16), "Organ.Draw Bar 4"));
    reg(Domains::Domain_0_127(MidiKey(MidiKey::ControlChange, 17), "Organ.Draw Bar 5"));
    reg(Domains::Domain_0_127(MidiKey(MidiKey::ControlChange, 18), "Organ.Draw Bar 6"));
    reg(Domains::Domain_0_127(MidiKey(MidiKey::ControlChange, 19), "Organ.Draw Bar 7"));
    reg(Domains::Domain_0_127(MidiKey(MidiKey::ControlChange, 20), "Organ.Draw Bar 8"));
    reg(Domains::Domain_0_127(MidiKey(MidiKey::ControlChange, 21), "Organ.Draw Bar 9"));
    reg(Domains::StatusDomain(MidiKey(MidiKey::ControlChange, 22), "Organ.Percussion Enable"));
    reg(Domains::OrganModelDomain(MidiKey(MidiKey::ControlChange, 23), "Organ.Model"));
    reg(Domains::OrganVibratoTypeDomain(MidiKey(MidiKey::ControlChange, 24), "Organ.Vibrato Type"));
    reg(Domains::StatusDomain(MidiKey(MidiKey::ControlChange, 25), "Organ.Vibrato Enabled"));
    reg(Domains::StatusDomain(MidiKey(MidiKey::ControlChange, 26), "Organ.Percussion Harmonic Third"));
    reg(Domains::StatusDomain(MidiKey(MidiKey::ControlChange, 27), "Organ.Fast Decay"));
    reg(Domains::StatusDomain(MidiKey(MidiKey::ControlChange, 28), "Organ.Percussion Volume Soft"));
    reg(Domains::Domain_m7_6(MidiKey(MidiKey::ControlChange, 99), "Organ.Octave Shift"));
    reg(Domains::Domain_0_1(MidiKey(MidiKey::ControlChange, 100), "Organ.Level"));
    reg(Domains::StatusDomain(MidiKey(MidiKey::ControlChange, 101), "Organ.Enabled"));

    reg(Domains::PianoTypeDomain(MidiKey(MidiKey::ControlChange, 8), "Piano.Type"));
    reg(Domains::Domain_1_52(MidiKey(MidiKey::ControlChange, 29), "Piano.Model"));
    reg(Domains::Domain_0_4(MidiKey(MidiKey::ControlChange, 5), "Piano.Slot Detune"));
    reg(Domains::ClavinetEq1Domain(MidiKey(MidiKey::ControlChange, 30), "Piano.Clavinet Equalizer 1"));
    reg(Domains::ClavinetEq1Domain(MidiKey(MidiKey::ControlChange, 31), "Piano.Clavinet Equalizer 2"));
    reg(Domains::Domain_1_52(MidiKey(MidiKey::ControlChange, 65), "Piano.Clavinet Model"));
    reg(Domains::PianoDynamicsDomain(MidiKey(MidiKey::ControlChange, 33), "Piano.Dynamics"));
    reg(Domains::PianoAcousticsDomain(MidiKey(MidiKey::ControlChange, 98), "Piano.Acoustics"));
    reg(Domains::Domain_m7_6(MidiKey(MidiKey::ControlChange, 105), "Piano.Octave Shift"));
    reg(Domains::Domain_0_1(MidiKey(MidiKey::ControlChange, 106), "Piano.Level"));
    reg(Domains::StatusDomain(MidiKey(MidiKey::ControlChange, 107), "Piano.Enabled"));
    reg(Domains::StatusDomain(MidiKey(MidiKey::ControlChange, 108), "Piano.Pedal Noise"));

    reg(Domains::Domain_m7_6(MidiKey(MidiKey::ControlChange, 111), "Synth.Octave Shift"));
    reg(Domains::Domain_0_1(MidiKey(MidiKey::ControlChange, 112), "Synth.Level"));
    reg(Domains::StatusDomain(MidiKey(MidiKey::ControlChange, 113), "Synth.Enabled"));
    reg(Domains::Domain_0_127(MidiKey(MidiKey::ControlChange, 34), "Synth.Glide Rate"));
    reg(Domains::StatusDomain(MidiKey(MidiKey::ControlChange, 109), "Synth.Arpeggiator"));
    reg(Domains::StatusDomain(MidiKey(MidiKey::ControlChange, 12), "Synth.Arpeggiator Master Clock"));
    reg(Domains::Domain_80_128x32(MidiKey(MidiKey::ControlChange, 102), "Synth.Arpeggiator Rate"));
    reg(Domains::SynthArpeggioPatterDomain(MidiKey(MidiKey::ControlChange, 103), "Synth.Arpeggiator Pattern"));
    reg(Domains::Domain_0_4(MidiKey(MidiKey::ControlChange, 104), "Synth.Arpeggiator Range"));
    reg(Domains::SynthVoiceModeDomain(MidiKey(MidiKey::ControlChange, 36), "Synth.Voice Mode"));
    reg(Domains::SynthUnisonoDomain(MidiKey(MidiKey::ControlChange, 27), "Synth.Unison"));
    reg(Domains::SynthVibratoModeDomain(MidiKey(MidiKey::ControlChange, 38), "Synth.Vibrato Mode"));
    reg(Domains::Domain_03_45k(MidiKey(MidiKey::ControlChange, 39), "Synth.Mod Envelope Attack"));
    reg(Domains::Domain_5_45k(MidiKey(MidiKey::ControlChange, 40), "Synth.Mod Envelope Decay"));
    reg(Domains::Domain_5_45k(MidiKey(MidiKey::ControlChange, 41), "Synth.Mod Envelope Release"));
    reg(Domains::StatusDomain(MidiKey(MidiKey::ControlChange, 42), "Synth.Mod Envelope Velocity"));
    reg(Domains::Domain_003_523(MidiKey(MidiKey::ControlChange, 115), "Synth.LFO Rate"));
    reg(Domains::SynthWaveFormDomain(MidiKey(MidiKey::ControlChange, 116), "Synth.Wave Form"));
    reg(Domains::StatusDomain(MidiKey(MidiKey::ControlChange, 13), "Synth.LFO Master Clock"));
    reg(Domains::SynthOscillatorModeDomain(MidiKey(MidiKey::ControlChange, 43), "Synth.LFO Master Clocl"));
    reg(Domains::Domain_1_128(MidiKey(MidiKey::ControlChange, 44), "Synth.Wave Form Select"));
    reg(Domains::Domain_0_10(MidiKey(MidiKey::ControlChange, 45), "Synth.Oscillator Shape"));
    reg(Domains::StatusDomain(MidiKey(MidiKey::ControlChange, 45), "Synth.Skip Attack Sample"));
    reg(Domains::Domain_m10_10(MidiKey(MidiKey::ControlChange, 46), "Synth.Oscillator Shape Mod"));
    reg(Domains::Domain_20_21k(MidiKey(MidiKey::ControlChange, 48), "Synth.Filter Frequency"));
    reg(Domains::Domain_0_10(MidiKey(MidiKey::ControlChange, 49), "Synth.Filter Resonance"));
    reg(Domains::Domain_m10_10(MidiKey(MidiKey::ControlChange, 2), "Synth.Filter Velocity Envelope Mod"));
    reg(Domains::Domain_0_10(MidiKey(MidiKey::ControlChange, 51), "Synth.Filter, LFO Mod"));
    reg(Domains::StatusDomain(MidiKey(MidiKey::ControlChange, 52), "Synth.Filter Keyboard Track"));
    reg(Domains::SynthFilterTypeDomain(MidiKey(MidiKey::ControlChange, 53), "Synth.Filter Type"));
    reg(Domains::Domain_03_45k(MidiKey(MidiKey::ControlChange, 54), "Synth.Amplifier Envelope Attack"));
    reg(Domains::Domain_5_45k(MidiKey(MidiKey::ControlChange, 55), "Synth.Amplifier Envelope Decay"));
    reg(Domains::Domain_5_45k(MidiKey(MidiKey::ControlChange, 56), "Synth.Amplifier Envelope Release"));
    reg(Domains::StatusDomain(MidiKey(MidiKey::ControlChange, 57), "Synth.Amplifier Envelope Velocity"));

    reg(Domains::Effect1TypeDomain(MidiKey(MidiKey::ControlChange, 60), "Effect.Effect 1 Type"));
    reg(Domains::EffectSourceDomain(MidiKey(MidiKey::ControlChange, 61), "Effect.Effect 1 Source"));
    reg(Domains::Domain_0_10(MidiKey(MidiKey::ControlChange, 62), "Effect.Effect 1 Amount"));
    reg(Domains::Domain_0_127(MidiKey(MidiKey::ControlChange, 63), "Effect.Effect 1 Rate"));
    reg(Domains::StatusDomain(MidiKey(MidiKey::ControlChange, 69), "Effect.Effect 1 Enabled"));
    reg(Domains::StatusDomain(MidiKey(MidiKey::ControlChange, 117), "Effect.Effect 1 Master Clock"));
    reg(Domains::Effect1TypeDomain(MidiKey(MidiKey::ControlChange, 70), "Effect.Effect 2 Type"));
    reg(Domains::EffectSourceDomain(MidiKey(MidiKey::ControlChange, 71), "Effect.Effect 2 Source"));
    reg(Domains::Domain_0_10(MidiKey(MidiKey::ControlChange, 72), "Effect.Effect 2 Amount"));
    reg(Domains::Domain_0_127(MidiKey(MidiKey::ControlChange, 73), "Effect.Effect 2 Rate"));
    reg(Domains::StatusDomain(MidiKey(MidiKey::ControlChange, 74), "Effect.Effect 2 Enabled"));
    reg(Domains::StatusDomain(MidiKey(MidiKey::ControlChange, 118), "Effect.Effect 2 Master Clock"));
    reg(Domains::EffectSourceDomain(MidiKey(MidiKey::ControlChange, 75), "Delay.Destination"));
    reg(Domains::Domain_0_10(MidiKey(MidiKey::ControlChange, 76), "Delay.Amount"));
    reg(Domains::Domain_0_127(MidiKey(MidiKey::ControlChange, 77), "Delay.Rate"));
    reg(Domains::Domain_0_10(MidiKey(MidiKey::ControlChange, 78), "Delay.Feedback"));
    reg(Domains::StatusDomain(MidiKey(MidiKey::ControlChange, 80), "Delay.Enabled"));
    reg(Domains::StatusDomain(MidiKey(MidiKey::ControlChange, 119), "Delay.Master Clock Enabled"));
    reg(Domains::AmpSimTypeDomain(MidiKey(MidiKey::ControlChange, 81), "Amp.Simulation Type"));
    reg(Domains::Domain_0_10(MidiKey(MidiKey::ControlChange, 83), "Amp.Simpulation Drive"));
    reg(Domains::EffectSourceDomain(MidiKey(MidiKey::ControlChange, 81), "Amp.Simulation Destination"));
    reg(Domains::Domain_m15_15(MidiKey(MidiKey::ControlChange, 84), "Amp.Simulation Bass Equalizer"));
    reg(Domains::Domain_m15_15(MidiKey(MidiKey::ControlChange, 85), "Amp.Simulation Mid Equalizer"));
    reg(Domains::Domain_m15_15(MidiKey(MidiKey::ControlChange, 86), "Amp.Simulation Treble Equalizer"));
    reg(Domains::Domain_200_8k(MidiKey(MidiKey::ControlChange, 6), "Amp.Simulation Mid Range"));
    reg(Domains::StatusDomain(MidiKey(MidiKey::ControlChange, 87), "Amp.Simulation Enabled"));
    reg(Domains::EffectSourceDomain(MidiKey(MidiKey::ControlChange, 88), "Rotor.Destination"));
    reg(Domains::Domain_m10_10(MidiKey(MidiKey::ControlChange, 89), "Rotor.Drive"));
    reg(Domains::RotorSpeedDomain(MidiKey(MidiKey::ControlChange, 82), "Rotor.Speed"));
    reg(Domains::StatusDomain(MidiKey(MidiKey::ControlChange, 91), "Rotor.Stop"));
    reg(Domains::StatusDomain(MidiKey(MidiKey::ControlChange, 92), "Rotor.Enabled"));
    reg(Domains::Domain_0_10(MidiKey(MidiKey::ControlChange, 93), "Compressor.Amount"));
    reg(Domains::StatusDomain(MidiKey(MidiKey::ControlChange, 94), "Compressor.Enabled"));
    reg(Domains::Domain_0_10(MidiKey(MidiKey::ControlChange, 95), "Reverb.Amount"));
    reg(Domains::ReverbSizeDomain(MidiKey(MidiKey::ControlChange, 96), "Reverb.Size"));
    reg(Domains::StatusDomain(MidiKey(MidiKey::ControlChange, 97), "Reverb.Enabled"));
    reg(Domains::SlotDomain(MidiKey(MidiKey::ControlChange, 68), "Misc.Slot Focus"));
    reg(Domains::Domain_0_1(MidiKey(MidiKey::ControlChange, 64), "Pedal.Sustain Pedal"));
    //reg(Domains::Domain??(MidiKey(MidiKey::ControlChange, 66), "Pedal.Latch Pedal"));
    //reg(Domains::Domain??(MidiKey(MidiKey::ControlChange, 67), "Pedal.Soft Pedal"));
    //reg(Domains::Domain??(MidiKey(MidiKey::ControlChange,  4), "Pedal.Organ Swell Pedal"));
    //reg(Domains::Domain??(MidiKey(MidiKey::ControlChange, 11), "Pedal.Controll Pedal"));
    //reg(Domains::Domain??(MidiKey(MidiKey::ControlChange, 82), "Pedal.Rotor Speed Pedal"));
    //reg(Domains::Domain??(MidiKey(MidiKey::ControlChange, 67), "Pedal.Keyboard Gate Pedal"));
    //reg(Domains::Domain??(MidiKey(MidiKey::ControlChange, 7), "Misc.Master Level"));
    reg(Domains::Domain_0_1(MidiKey(MidiKey::ControlChange, 1), "Misc.Wheel"));





    reg(Domains::Domain_0_1(MidiKey(MidiKey::ControlChange, 64), "Pedal.Sustain Pedal"));

    reg(Domains::Domain_0_1(MidiKey(MidiKey::ControlChange, 64), "Pedal.Sustain Pedal"));


    return Triple(codes, properties, domains);
}

NordStage2* NordStage2::channel(int i)
{
    if (!CHANNELS[i]) CHANNELS[i] = new NordStage2(i);
    return CHANNELS[i];
}

QMap<QString, QStringList> NordStage2::calculateProperties()
{
    QMap<QString, QStringList> properties;
    for (QString string : NAMES.values()) {
        QString category = string.split('.', QString::SkipEmptyParts).first();
        QString property = string.split('.', QString::SkipEmptyParts).last();
        if (properties.keys().contains(category)) {
            properties[category].append(property);
        } else {
            properties.insert(category, QStringList() << property);
        }
    }
    return properties;
}

void NordStage2::installReceiver(int myChannel)
{
    connect(MidiHandler::singleton(), &MidiHandler::receivedMidiCommand,
            [this, myChannel](MidiKey key, int channel, quint8 data) {
        if (myChannel != channel) return;

        switch (key.type()) {
        case MidiKey::ControlChange:
            if (!DOMAINS.contains(key)) return;
            switch (DOMAINS[key]->type()) {
            case Domain::Discrete:
                emit midiInput(myChannel, key, ((DiscreteDomain*) DOMAINS[key])->decode(data));
                break;
            case Domain::Double:
                emit midiInput(myChannel, key, ((DoubleDomain*) DOMAINS[key])->decode(data));
                break;
            case Domain::Integer:
                emit midiInput(myChannel, key, ((IntegerDomain*) DOMAINS[key])->decode(data));
                break;
            }
            break;
        case MidiKey::NoteOn:
        case MidiKey::NoteOff:
            emit midiInput(myChannel, key, data);
            break;
        case MidiKey::Aftertouch:
            break;
        case MidiKey::PitchBend:
            emit midiInput(myChannel, key, Domains::decodePitch(key, data));
            break;
        case MidiKey::ProgramChange:
        case MidiKey::Unknown:
        default:
            break;
        }
    });
}

QStringList NordStage2::categories()
{
    return NordStage2::PROPERTIES.keys();
}

QStringList NordStage2::properties(int category)
{
    return NordStage2::PROPERTIES[NordStage2::PROPERTIES.keys()[category]];
}

int NordStage2::propertyIndex(MidiKey key)
{
    if (key.type() != MidiKey::ControlChange
            || !NAMES.contains(key))
        return -1;

    return properties(categoryIndex(key)).indexOf(NAMES[key].split('.').last());
}

int NordStage2::categoryIndex(MidiKey key)
{
    if (key.type() != MidiKey::ControlChange
            || !NAMES.contains(key))
        return -1;

    return categories().indexOf(NAMES[key].split('.').first());
}





























