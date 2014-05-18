#ifndef NORDSTAGE2_H
#define NORDSTAGE2_H
#include "keyboard.h"
#include <QDebug>
#include <QTimer>

class NordStage2 : public Keyboard
{
    Q_OBJECT
public:
    enum Preset { PresetI = 0, PresetII = 127 };
    enum Status { On = 0, Off = 127 };
    enum OrganModel { B3 = 0, Vox = 64, Farfisa = 127 };
    enum OrganVibratoType { C1 = 0, C2 = 51, C3 = 102, V1 = 26, V2 = 77, V3 = 127 };
    enum PianoType { Grand = 0, Upright = 26, EPiano1 = 51, EPiano2 = 77, Clavinet = 102, Harpsi = 127 };
    enum ClavinetEq1 { NoEq1 = 0, Treb = 43, Brill = 85, BrillTreb = 127 };
    enum ClavinetEq2 { NoEq2 = 0, Soft = 43, Med = 85, SoftMed = 127 };
    enum PianoAcoustics { NoAcoustic = 0, StringRes = 43, LongRelease = 85, StringResLongRelease = 127 };
    enum PianoDynamic { Dynamic0 = 0, Dynamic1 = 43, Dynamic2 = 85, Dynamic3 = 127 };
    enum SynthArpPattern { Up = 0, Down = 43, UpDown = 85, Random = 127 };
    enum SynthVoiceMode { NoGlide = 0, Legato = 64, Mono = 127 };
    enum SynthUnison { NoUnison = 0, Unison1 = 22, Unison2 = 43, Unison3 = 64,
                       MultiUnison1 = 85, MultiUnison2 = 106, MultiUnison3 = 127 };
    enum SynthVibratoMode { NoVibrato = 0, Dly1 = 26, Dly2 = 51, Dly3 = 77, Aftertouch = 102, Wheel = 127 };
    enum SynthWaveForm { LFOSquare = 0, LFOSawtooth = 43, LFOTriangle = 85, LFORandom = 127 };
    enum SynthOscillatorMode { Square = 0, Sawtooth = 26, Triangle = 51, Sample = 77,
                               FrequencyModulation = 102, WaveTable = 127 };
    enum SynthFilterType { LowPass12 = 0, LowPass24 = 32, HighPass = 64, Notch = 96, BandPass = 127 };
    enum Effect1Type { AutoPan = 0, Tremolo = 26, RingModulation = 51, WaWa = 77, AWha1 = 102, AWha2 = 127 };
    enum Effect2Type { Phaser1 = 0, Phaser2 = 26, Flanger = 51, Vibe = 77, Chorus1 = 102, Chorus2 = 127 };
    enum EffectSource { Organ = 0, Piano = 64, Synth = 127 };
    enum RotorSpeed { Slow = 0, Fast = 127 };
    enum ReverbSize { Room1 = 0, Room2 = 26, Stage1 = 51, Stage2 = 77, Hall1 = 102, Hall2 = 127 };
    enum AmpSimType { Small = 0, JC = 64, Twin = 127 };
    enum Slot { SlotA = 0, SlotB = 127 };

    NordStage2(quint8 channel = 0, QObject* parent = 0);

public slots:

    //=====  SpecialEffects =========================
    void stopEffects();
    void sineWaveDrawbar(int speed, int freq, int intervall);

    //=====  Organ ==================================
    void setOrganPreset(Preset preset);
    //void setOrganSwell()  //TODO
    void setOrganDrawBar(quint8 number, quint8 value);
    void setOrganPercussionEnable(Status status);
    void setOrganModel(OrganModel model);
    void setOrganVirbratoType(OrganVibratoType type);
    void setVibratoEnable(Status status);
    void setOrganPercussionHarmonicThird(Status status);
    void setOrganPercussionFastDecay(Status status);
    void setOrganPercussionVolumeSoft(Status status);
    void setOrganOctaveShift(int shift);                    // -7 - 6
    void setOrganLevel(double level);                       // 0 - 1
    void setOrganEnabled(Status status);

    //=====  Piano ==================================
    void setPianoType(PianoType type);
    void setPianoModel(int model);                          // 0 - 51
    void setPianoSlotDetune(int detune);                    // 0 - 4
    void setClavEQ1(ClavinetEq1 eq);
    void setClavEQ2(ClavinetEq2 eq);
    void setClavModelType(int model);                       // 0 - 51
    void setPianoDynamics(PianoDynamic dyn);
    void setPianoAcoustic(PianoAcoustics pa);
    void setPianoOctaveShift(int shift);                    // -7 - 6
    void setPianoLevel(double level);                       // 0 - 1
    void setPianoEnable(Status status);
    void setPianoPedalNoise(Status status);

    //====  Synth ===================================
    void setSynthOctaveShift(int shift);
    void setSynthLevel(double level);                       // 0 - 1
    void setSynthEnable(Status status);
    void setSynthGlideRate(quint8 rate);    //TODO
    void setSynthArpOnOff(Status status);
    void setSynthArpMstClk(Status status);
    void setSynthArpRate(int rate);                         //80 - 128 * 32
    void setSynthArpPattern(SynthArpPattern pattern);
    void setSynthArpRange(int range);                       // 1 - 4
    void setSynthVoiceMode(SynthVoiceMode mode);
    void setSynthUnison(SynthUnison mode);
    void setSynthVibratoMode(SynthVibratoMode mode);
    void setSynthModEnvelopeAttack(double attack);          // 0.5ms - 45s   nl
    void setSynthModEnvelopeDecay(double decay);            // 3.0ms - 45s   nl
    void setSynthModEnvelopeRelease(double release);        // 3.0ms - 45s   nl
    void setSynthModEnvelopeVelocity(Status on);
    void setSynthLFORate(double freq);
    void setSynthLFOWaveform(SynthWaveForm waveform);
    void setSynthLFOMasterClk(Status status);
    void setSynthLFOMasterClk(SynthOscillatorMode mode);
    void setSynthWaveformSelect(int number);                // 1 - 128   !decrease by one!
    void setSynthOscillatorShape(double shape);             // 0 - 10
    void setSynthOscillatorSkipSampleAttack(Status status);
    void setSynthOscillatorShapeMod(double mod);
    void setSynthFilterFrequency(double freq);              // 20Hz - 21kHz nl
    void setSynthFilterResonance(double res);               // 0 - 10
    void setSynthFilterVelocityEnvelopeMod(double ve);      // -10 - 10
    void setSynthFilterLFOMod(double mod);                  // 0 - 10
    void setSynthFilterKeyboardTrack(Status status);
    void setSynthFilterType(SynthFilterType type);
    void setSynthAmpEnvelopeAttack(double attack);          // 0 - 10
    void setSynthAmpEnvelopeDecay(double decay);            // 0 - 10
    void setSynthAmpEnvelopeRelease(double release);        // 0 - 10
    void setSynthAmpEnvelopeVelocity(Status status);

    //====  Effects =================================
    void setEffect1Type(Effect1Type type);
    void setEffect1Source(EffectSource source);
    void setEffect1Amount(double amount);                   // 0 - 10
    void setEffect1Rate(quint8 rate);                       // 0 - 127
    void setEffect1Enable(Status status);
    void setEffect1MstClk(Status status);
    void setEffect2Type(Effect2Type type);
    void setEffect2Source(EffectSource source);
    void setEffect2Amount(double amount);                   // 0 - 10
    void setEffect2Rate(quint8 rate);                       // 0 - 127
    void setEffect2Enable(Status status);
    void setEffect2MstClk(Status status);
    void setDelayDestination(EffectSource destination);
    void setDelayAmount(double amount);                     // 0 - 10
    void setDelayRate(quint8 rate);                         // 0 - 127
    void setDelayFeedback(double feedback);
    void setDelayPingPongOnOff(Status status);
    void setDelayEnable(Status status);
    void setDelayMstClk(Status status);
    void setAmpSimType(AmpSimType type);
    void setAmpSimDrive(double drive);                      // 0 - 10
    void setAmpSimDestination(EffectSource source);
    void setAmpSimBassEQ(double dB);                        // -15 - 15
    void setAmpSimMidEQ(double dB);                         // -15 - 15
    void setAmpSimMidRange(double range);                   //  200 - 8000
    void setAmpSimTrebleEQ(double db);                      // -15 - 15
    void setAmpSimEnabled(Status status);
    void setRotorDestination(EffectSource source);
    void setRotorDrive(double drive);                       // 0 - 10
    void setRotorSpeed(RotorSpeed speed);
    void setRotorStop(Status status);
    void setRotorEnable(Status status);
    void setCompressorAmount(double amount);                // 0 - 10
    void setCompressorEnable(Status status);
    void setReverbAmount(double amount);                    // 0 - 10
    void setReverbSize(ReverbSize size);
    void setReverbEnabled(Status status);
    void setSlotFocus(Slot slot);


    //==== General ==================================
    void setPedalSustain(quint8 sustain);                   // 0 - 127
    //TODO
    void setPedalLatch();
    void setPedalSoft();
    void setOrganSwellPedal();
    void setCtrlPedal();
    void setRotorSpeedPedal();
    void setKBGatePedal();
    void setMasterLevel();




public:
    static quint8 encodeOctaveShift(int shift);
    static quint8 encodePianoModel(int model);
    static quint8 encodeLevel(double level);
    static quint8 encodeAttack(double attack);
    static quint8 encodeDecayOrRelease(double dr);
    static quint8 encodeRate(int rate);
    static quint8 encodeLowFreq(double freq);
    static quint8 encodeMidFreq(double freq);
    static quint8 encodeHighFreq(double freq);
    static quint8 encode_0_10(double nz);
    static quint8 encode_m10_10(double mzz);
    static quint8 encode_m15_15(double mff);
    static quint8 encodeDelayTime(int milliseconds);
    QTimer* _timer = 0;
    quint8 _time = 0;
    static const double AttackSamples[128];         // map [0.5,45000] to [0, 127]
    static const double DecayReleaseSamples[128];   // map [  3,45000] to [0, 127]
    static const int RateSamples[128];              // map [80,  1024] to [0, 127]
    static const double LowFreqSamples[128];        // map [0.03, 523] to [0, 127]
    static const double MidFreqSamples[128];        // map [20, 21000] to [0, 127]
    static const double HighFreqSamples[128];       // map [200, 8000] to [0, 127]
    static const int DelayTimeSamples[128];         // map [750, 20]   to [0, 127]

    static double limit(double min, double value, double max, QString name);
    static int limit(int min, int value, int max, QString name);
};

#endif // NORDSTAGE2_H
