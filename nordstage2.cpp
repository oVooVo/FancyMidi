#include "nordstage2.h"
#include "midiinputhandler.h"
#include <QDebug>

NordStage2* NordStage2::CHANNELS[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

const QMap<QString, quint8> NordStage2::CODES = NordStage2::createProperties().codes;
const QMap<quint8, QString> NordStage2::NAMES = NordStage2::createProperties().names;
const QMap<quint8, Domain*> NordStage2::DOMAINS = NordStage2::createProperties().domains;

const QMap<QString, QStringList> NordStage2::PROPERTIES = NordStage2::calculateProperties();

void copy(const QMap<quint8, Domain*> src, QMap<quint8, Domain*> &dest, Keyboard* keyboard)
{
    dest.clear();
    for (quint8 key : src.keys()) {
        dest.insert(key, src[key]->copy(keyboard));
    }
}

NordStage2::NordStage2(int channel, QObject* parent) : Keyboard(channel, parent)
{
    copy(DOMAINS, _domains, this);
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
    QMap<QString, quint8> codes;
    QMap<quint8, QString> properties;
    QMap<quint8, Domain*> domains;

    auto reg = [&](Domain* domain)
    {
        codes.insert(domain->name(), domain->midicode());
        properties.insert(domain->midicode(), domain->name());
        domains.insert(domain->midicode(), domain);
    };

    reg(Domains::PresetDomain(3, "Organ.Preset"));
    //TODO reg("Organ.Swell", -1, 0);
    reg(Domains::Domain_0_127(9,   "Organ.Draw Bar 1"));
    reg(Domains::Domain_0_127(14,  "Organ.Draw Bar 2"));
    reg(Domains::Domain_0_127(15,  "Organ.Draw Bar 3"));
    reg(Domains::Domain_0_127(16,  "Organ.Draw Bar 4"));
    reg(Domains::Domain_0_127(17,  "Organ.Draw Bar 5"));
    reg(Domains::Domain_0_127(18,  "Organ.Draw Bar 6"));
    reg(Domains::Domain_0_127(19,  "Organ.Draw Bar 7"));
    reg(Domains::Domain_0_127(20,  "Organ.Draw Bar 8"));
    reg(Domains::Domain_0_127(21,  "Organ.Draw Bar 9"));
    reg(Domains::StatusDomain(22, "Organ.Percussion Enable"));
    reg(Domains::OrganModelDomain(23,  "Organ.Model"));
    reg(Domains::OrganVibratoTypeDomain(24,  "Organ.Vibrato Type"));
    reg(Domains::StatusDomain(25,  "Organ.Vibrato Enabled"));
    reg(Domains::StatusDomain(26,  "Organ.Percussion Harmonic Third"));
    reg(Domains::StatusDomain(27,  "Organ.Fast Decay"));
    reg(Domains::StatusDomain(28,  "Organ.Percussion Volume Soft"));
    reg(Domains::Domain_m7_6(99,  "Organ.Octave Shift"));
    reg(Domains::Domain_0_1(100, "Organ.Level"));
    reg(Domains::StatusDomain(101, "Organ.Enabled"));

    reg(Domains::PianoTypeDomain(8, "Piano.Type"));
    reg(Domains::Domain_1_52(29, "Piano.Model"));
    reg(Domains::Domain_0_4(5, "Piano.Slot Detune"));
    reg(Domains::ClavinetEq1Domain(30, "Piano.Clavinet Equalizer 1"));
    reg(Domains::ClavinetEq1Domain(31, "Piano.Clavinet Equalizer 2"));
    reg(Domains::Domain_1_52(65, "Piano.Clavinet Model"));
    reg(Domains::PianoDynamicsDomain(33, "Piano.Dynamics"));
    reg(Domains::PianoAcousticsDomain(98, "Piano.Acoustics"));
    reg(Domains::Domain_m7_6(105, "Piano.Octave Shift"));
    reg(Domains::Domain_0_1(106, "Piano.Level"));
    reg(Domains::StatusDomain(107, "Piano.Enabled"));
    reg(Domains::StatusDomain(108, "Piano.Pedal Noise"));

    reg(Domains::Domain_m7_6(111, "Synth.Octave Shift"));
    reg(Domains::Domain_0_1(112, "Synth.Level"));
    reg(Domains::StatusDomain(113, "Synth.Enabled"));
    reg(Domains::Domain_0_127(34, "Synth.Glide Rate"));
    reg(Domains::StatusDomain(109, "Synth.Arpeggiator"));
    reg(Domains::StatusDomain(12, "Synth.Arpeggiator Master Clock"));
    reg(Domains::Domain_80_128x32(102, "Synth.Arpeggiator Rate"));
    reg(Domains::SynthArpeggioPatterDomain(103, "Synth.Arpeggiator Pattern"));
    reg(Domains::Domain_0_4(104, "Synth.Arpeggiator Range"));
    reg(Domains::SynthVoiceModeDomain(36, "Synth.Voice Mode"));
    reg(Domains::SynthUnisonoDomain(27, "Synth.Unison"));
    reg(Domains::SynthVibratoModeDomain(38, "Synth.Vibrato Mode"));
    reg(Domains::Domain_03_45k(39, "Synth.Mod Envelope Attack"));
    reg(Domains::Domain_5_45k(40, "Synth.Mod Envelope Decay"));
    reg(Domains::Domain_5_45k(41, "Synth.Mod Envelope Release"));
    reg(Domains::StatusDomain(42, "Synth.Mod Envelope Velocity"));
    reg(Domains::Domain_003_523(115, "Synth.LFO Rate"));
    reg(Domains::SynthWaveFormDomain(116, "Synth.Wave Form"));
    reg(Domains::StatusDomain(13, "Synth.LFO Master Clock"));
    reg(Domains::SynthOscillatorModeDomain(43, "Synth.LFO Master Clocl"));
    reg(Domains::Domain_1_128(44, "Synth.Wave Form Select"));
    reg(Domains::Domain_0_10(45, "Synth.Oscillator Shape"));
    reg(Domains::StatusDomain(45, "Synth.Skip Attack Sample"));
    reg(Domains::Domain_m10_10(46, "Synth.Oscillator Shape Mod"));
    reg(Domains::Domain_20_21k(48, "Synth.Filter Frequency"));
    reg(Domains::Domain_0_10(49, "Synth.Filter Resonance"));
    reg(Domains::Domain_m10_10(2, "Synth.Filter Velocity Envelope Mod"));
    reg(Domains::Domain_0_10(51, "Synth.Filter, LFO Mod"));
    reg(Domains::StatusDomain(52, "Synth.Filter Keyboard Track"));
    reg(Domains::SynthFilterTypeDomain(53, "Synth.Filter Type"));
    reg(Domains::Domain_03_45k(54, "Synth.Amplifier Envelope Attack"));
    reg(Domains::Domain_5_45k(55, "Synth.Amplifier Envelope Decay"));
    reg(Domains::Domain_5_45k(56, "Synth.Amplifier Envelope Release"));
    reg(Domains::StatusDomain(57, "Synth.Amplifier Envelope Velocity"));

    reg(Domains::Effect1TypeDomain(60, "Effect.Effect 1 Type"));
    reg(Domains::EffectSourceDomain(61, "Effect.Effect 1 Source"));
    reg(Domains::Domain_0_10(62, "Effect.Effect 1 Amount"));
    reg(Domains::Domain_0_127(63, "Effect.Effect 1 Rate"));
    reg(Domains::StatusDomain(69, "Effect.Effect 1 Enabled"));
    reg(Domains::StatusDomain(117, "Effect.Effect 1 Master Clock"));
    reg(Domains::Effect1TypeDomain(70, "Effect.Effect 2 Type"));
    reg(Domains::EffectSourceDomain(71, "Effect.Effect 2 Source"));
    reg(Domains::Domain_0_10(72, "Effect.Effect 2 Amount"));
    reg(Domains::Domain_0_127(73, "Effect.Effect 2 Rate"));
    reg(Domains::StatusDomain(74, "Effect.Effect 2 Enabled"));
    reg(Domains::StatusDomain(118, "Effect.Effect 2 Master Clock"));
    reg(Domains::EffectSourceDomain(75, "Delay.Destination"));
    reg(Domains::Domain_0_10(76, "Delay.Amount"));
    reg(Domains::Domain_0_127(77, "Delay.Rate"));
    reg(Domains::Domain_0_10(78, "Delay.Feedback"));
    reg(Domains::StatusDomain(80, "Delay.Enabled"));
    reg(Domains::StatusDomain(119, "Delay.Master Clock Enabled"));
    reg(Domains::AmpSimTypeDomain(81, "Amp.Simulation Type"));
    reg(Domains::Domain_0_10(83, "Amp.Simpulation Drive"));
    reg(Domains::EffectSourceDomain(81, "Amp.Simulation Destination"));
    reg(Domains::Domain_m15_15(84, "Amp.Simulation Bass Equalizer"));
    reg(Domains::Domain_m15_15(85, "Amp.Simulation Mid Equalizer"));
    reg(Domains::Domain_m15_15(86, "Amp.Simulation Treble Equalizer"));
    reg(Domains::Domain_200_8k(6, "Amp.Simulation Mid Range"));
    reg(Domains::StatusDomain(87, "Amp.Simulation Enabled"));
    reg(Domains::EffectSourceDomain(88, "Rotor.Destination"));
    reg(Domains::Domain_m10_10(89, "Rotor.Drive"));
    reg(Domains::RotorSpeedDomain(82, "Rotor.Speed"));
    reg(Domains::StatusDomain(91, "Rotor.Stop"));
    reg(Domains::StatusDomain(92, "Rotor.Enabled"));
    reg(Domains::Domain_0_10(93, "Compressor.Amount"));
    reg(Domains::StatusDomain(94, "Compressor.Enabled"));
    reg(Domains::Domain_0_10(95, "Reverb.Amount"));
    reg(Domains::ReverbSizeDomain(96, "Reverb.Size"));
    reg(Domains::StatusDomain(97, "Reverb.Enabled"));

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

