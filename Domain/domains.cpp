#include "domains.h"
#include <QDebug>

const double AttackSamples[128] = {
    0.5,   0.6,   0.7,   0.9,   1.1,   1.3,   1.5,   1.8,   2.1,   2.5,             // 0  - 9
    3.0,   3.5,   4.0,   4.7,   5.5,   6.3,   7.3,   8.4,   9.7,    11,             // 10 - 19
     13,    14,    16,    19,    21,    24,    27,    31,    34,    39,             // 20 - 29
     41,    49,    54,    61,    68,    75,    84,    93,   103,   114,             // ...
    126,   139,   153,   169,   186,   204,   224,   246,   269,   295,
    322,   252,   384,   419,   456,   496,   540,   586,   636,   690,
    748,   810,   876,   947,  1020,  1100,  1190,  1280,  1380,  1490,
   1600,  1720,  1850,  1990,  2130,  2280,  2450,  2620,  2810,  3000,
   3210,  3430,  3660,  3910,  4170,  4450,  4740,  5050,  5370,  5720,
   6080,  6470,  6870,  7300,  7750,  8220,  8720,  9250,  9800, 10000,
  11000, 12000, 12400, 13000, 14000, 15000, 15400, 16000, 17000, 18000,             // 12400 15400 are guessed since they are displayed as 12s, 15s.
  19000, 20000, 21000, 22000, 24000, 25000, 26000, 27000, 29000, 30000,
  32000, 34000, 35000, 37000, 39000, 41000, 43000, 45000                            // 120 - 127
};


const double DecayReleaseSamples[128] = {
        3,   3.5,    4,    4.6,   5.3,    6,    6.9,   7.9,     9,    10,
       12,    13,    15,    17,    19,    21,    23,    26,    29,    33,
       36,    41,    45,    50,    55,    61,    68,    75,    82,    91,
      100,   110,   120,   132,   144,   158,   173,   188,   206,   224,
      244,   265,   288,   313,   340,   368,   399,   432,   467,   505,
      545,   588,   634,   683,   736,   792,   851,   915,   983,  1050,
     1130,  1210,  1300,  1390,  1490,  1590,  1790,  1820,  1940,  2070,
     2210,  2360,  2510,  2670,  2850,  3030,  3220,  3420,  3640,  3860,
     4100,  4350,  4610,  4890,  5180,  5490,  5810,  6150,  6500,  6880,
     7270,  7680,  8110,  8570,  9040,  9540, 10000, 11000, 11300, 12000,
    12300, 13000, 14000, 14400, 15000, 16000, 17000, 18000, 19000, 20000,
    /*!*/25000/*!*/, 22000, 23000, 24000, 25000, 26000, 27000, 29000, 30000, 31000,   //TODO non-monotone!
    33000, 34000, 36000, 38000, 39000, 41000, 43000, 45000
};

const double LowFreqSamples[128] = {
    0.03, 0.03, 0.03, 0.04, 0.04, 0.04, 0.04, 0.05, 0.05, 0.06,
    0.06, 0.07, 0.07, 0.08, 0.09, 0.09, 0.01, 0.11, 0.12, 0.13,
    0.14, 0.15, 0.16, 0.17, 0.19, 0.20, 0.22, 0.24, 0.26, 0.28,
    0.30, 0.32, 0.35, 0.38, 0.41, 0.44, 0.47, 0.51, 0.55, 0.60,
    0.64, 0.70, 0.75, 0.81, 0.88, 0.95, 1.00, 1.10, 1.20, 1.30,
    1.40, 1.50, 1.60, 1.80, 1.90, 2.00, 2.20, 2.40, 2.60, 2.80,
    3.00, 6.50, 7.00, 7.60, 8.20, 8.80, 9.50,   10,   12,   13,
      14,   15,   16,   18,   19,   21,   22,   24,   26,   28,
      30,   33,   35,   38,   41,   45,   48,   52,   56,   61,
      65,   71,   76,   82,   89,   96,  104,  112,  121,  131,
     141,  135,  165,  173,  192,  208,  224,  242,  262,  283,
     305,  330,  356,  385,  415,  449,  484,  523
};

const double MidFreqSamples[128] = {
      20,    21,    22,    24,    25,    26,    28,    29,    31,    33,
      35,    37,    39,    41,    43,    45,    48,    51,    54,    57,
      60,    63,    67,    70,    74,    79,    83,    88,    93,    98,
     103,   109,   115,   112,   129,   136,   144,   152,   160,   169,
     179,   189,   200,   211,   223,   235,   248,   262,   277,   293,
     309,   327,   345,   365,   385,   407,   430,   454,   479,   506,
     535,   565,   597,   631,   666,   704,   743,   758,   829,   876,
     925,   977,  1000,  1100,  1200,  1200,  1300,  1400,  1400,  1500,
    1600,  1700,  1800,  1900,  2000,  2100,  2200,  2300,  2500,  2600,
    2800,  2900,  3100,  3300,  3400,  3600,  3800,  4100,  4300,  4500,
    4800,  5100,  5300,  5600,  6000,  6300,  6600,  7000,  7400,  7800,
    8300,  8700,  9200, 10000, 10000, 11000, 11000, 12000, 13000, 14000,
   14000, 15000, 16000, 17000, 18000, 19000, 20000, 21000
};

const double HighFreqSamples[128] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0
};


auto encode_0_1 = [](double level, bool &ok)
{
    ok = false;
    double l = qBound(0.0, level, 1.0);
    if (level != l) {
        ok = false;
#ifdef VERBOSE
        qWarning() << "Limited value to" << l << "between 0 and 1 (was" << level << ").";
#endif
    }
    return 127 * level;
};

auto decode_0_1 = [](quint8 code, bool &ok)
{
    ok = code < 128;
    return code / 127.0;
};

auto encodeAttack = [](double attack, bool& ok) -> quint8
{
    ok = true;
    uint index;
    for (index = 0; index < 128; index++) {
        if (AttackSamples[index] > attack) break;
    }
    if (index == 0) return 0;

    double lower = AttackSamples[index - 1];
    double upper = AttackSamples[index];
    return attack - lower < upper - attack ? index - 1 : index;
};

auto encodeDecayOrRelease = [](double dr, bool& ok) -> quint8
{
    ok = true;
    uint index;
    for (index = 0; index < 128; index++) {
        if (DecayReleaseSamples[index] > dr) break;
    }
    if (index == 0) return 0;

    double lower = DecayReleaseSamples[index - 1];
    double upper = DecayReleaseSamples[index];
    return dr - lower < upper - dr ? index - 1 : index;
};

auto encodeLowFreq = [](double freq, bool& ok) -> quint8
{
    ok = true;
    uint index;
    for (index = 0; index < 128; index++) {
        if (LowFreqSamples[index] > freq) break;
    }
    if (index == 0) return 0;

    double lower = LowFreqSamples[index - 1];
    double upper = LowFreqSamples[index];
    return freq - lower < upper - freq ? index - 1 : index;
};

auto encodeMidFreq = [](double freq, bool& ok) -> quint8
{
    ok = true;
    uint index;
    for (index = 0; index < 128; index++) {
        if (MidFreqSamples[index] > freq) break;
    }
    if (index == 0) return 0;

    double lower = MidFreqSamples[index - 1];
    double upper = MidFreqSamples[index];
    return freq - lower < upper - freq ? index - 1 : index;
};

auto encodeHighFreq = [](double freq, bool& ok) -> quint8
{
    ok = false;
    qWarning() << "encodeHighFreq() is a stub!";
    // TODO: Sample MIDI-knob 6 (AmpSimMidRange)

    uint index;
    for (index = 0; index < 128; index++) {
        if (HighFreqSamples[index] > freq) break;
    }
    if (index == 0) return 0;

    double lower = HighFreqSamples[index - 1];
    double upper = HighFreqSamples[index];
    return freq - lower < upper - freq ? index - 1 : index;
};

auto encode_0_10 = [](double nz, bool& ok)
{
    ok = nz >= 0.0 && nz <= 10.0;
    return 12.7 * nz;
};

auto decode_0_10 = [](quint8 code, bool &ok)
{
    ok = code < 128;
    return code / 12.7;
};

auto encode_m10_10 = [](double mzz, bool& ok)
{
    ok = mzz >= -10.0 && mzz <= 10.0;
    return 12.7 * (mzz/2.0-5.0);
};

auto encode_m15_15 = [](double mff, bool& ok)
{
    ok = mff >= -15.0 && mff <= 15.0;
    return 12.7 * (mff/3.0+5.0);
};



const int RateSamples[128] = {
      80,   82,   84,   86,   88,   90,   92,   94,   96,   98,
     100,  102,  104,  106,  108,  110,  112,  114,  116,  118,
     120,  122,  124,  126,  128,  130,  132,  134,  136,  138,
     140,  142,  144,  148,  152,  156,  160,  164,  168,  172,
     176,  180,  184,  188,  192,  196,  200,  204,  208,  212,
     216,  220,  224,  228,  232,  236,  240,  244,  248,  252,
     256,  260,  264,  268,  272,  280,  288,  296,  304,  312,
     320,  328,  336,  344,  352,  360,  368,  376,  384,  392,
     400,  408,  416,  424,  432,  440,  448,  456,  464,  472,
     480,  488,  496,  504,  512,  520,  528,  544,  560,  576,
     592,  608,  624,  640,  656,  672,  688,  704,  720,  736,
     752,  768,  784,  800,  816,  832,  848,  864,  880,  896,
     912,  928,  944,  960,  976,  992, 1008, 1024
};

const int DelayTimeSamples[128] = {
    750, 732, 714, 698, 682, 667, 652, 638, 625, 612,
    600, 588, 577, 566, 556, 545, 536, 526, 517, 508,
    500, 592, 584, 476, 469, 462, 455, 448, 441, 435,
    429, 423, 417, 411, 405, 400, 395, 390, 385, 380,
    375, 366, 357, 349, 341, 333, 326, 319, 313, 306,
    300, 294, 288, 283, 278, 273, 268, 263, 259, 254,
    250, 246, 242, 238, 234, 231, 227, 224, 221, 217,
    214, 211, 208, 205, 203, 200, 197, 195, 192, 190,
    187, 183, 179, 174, 170, 167, 163, 160, 156, 153,
    150, 147, 144, 142, 139, 134, 136, 132, 129, 127,
    125, 123, 121, 119, 117, 115, 114, 112, 110, 109,
    107,  99,  91,  81,  72,  65,  60,  55,  51,  47,
     42,  37,  33,  30,  28,  26,  24,  20
};

auto encodeOctaveShift = [](int shift, bool& ok)
{
    quint8 s = qBound(-7, shift, 6);
    ok = s == shift;
    quint8 value = 10 * (s + 7);
    value -= ((value-1)/ 40);
    return value;
};

auto encodePianoModel = [](int model, bool &ok)
{
    quint8 m = qBound(1, model, 52);
    ok = m == model;
    quint8 value = 3 * (m-1);
    value -= ((value-1) / 6);
    return value;
};

auto encodeDelayTime = [](int milliseconds, bool &ok) -> quint8
{
    ok = true;
    uint index;
    for (index = 0; index < 128; index++) {
        if (DelayTimeSamples[index] < milliseconds) break;
    }
    if (index == 0) return 0;

    double lower = DelayTimeSamples[index];
    double upper = DelayTimeSamples[index - 1];
    return milliseconds - lower < upper - milliseconds ? index - 1 : index;
};

auto encodeRate = [](int rate, bool& ok) -> quint8
{
    ok = true;
    uint index;
    for (index = 0; index < 128; index++) {
        if (RateSamples[index] > rate) break;
    }
    if (index == 0) return 0;

    double lower = RateSamples[index - 1];
    double upper = RateSamples[index];
    return rate - lower < upper - rate ? index - 1 : index;
};

auto encodeId = [](int i, bool& ok) -> quint8
{
    quint8 v = (quint8) i;
    ok = v == i;
    return v;
};

auto encodeIdm1 = [](int i, bool& ok) -> quint8
{
    quint8 v = (quint8) (i-1);
    ok = v == i-1;
    return v;
};

auto encodeDetune = [](int detune, bool& ok) -> quint8
{
    int d = qBound(0, detune, 4);
    ok = d == detune;
    return (32 * d) - (d / 4);
};

auto decodeId = [](quint8 code, bool& ok)
{
    return code;
};

auto decodeIdp1 = [](quint8 code, bool& ok)
{
    return code + 1;
};


auto decode = [](quint8, bool& ok) {
    qWarning() << "Decoding is not supported!";
    ok = false;
    return 0;
};

#define SL(X) QStringList() << X
#define TR(X) QObject::tr(X)

// discrete
Domain* Domains::PresetDomain(MidiKey midiKey, QString name) {
    return new DiscreteDomain(midiKey, name, SL(TR("Preset I") << TR("Preset II"))); }
Domain* Domains::StatusDomain(MidiKey midiKey, QString name) {
    return new DiscreteDomain(midiKey, name, SL(TR("off") << TR("on"))); }
Domain* Domains::OrganModelDomain(MidiKey midiKey, QString name) {
    return new DiscreteDomain(midiKey, name, SL(TR("B3") << TR("Vox") << TR("Farfisa"))); }
Domain* Domains::OrganVibratoTypeDomain(MidiKey midiKey, QString name) { return new DiscreteDomain(
    midiKey, name, SL(TR("Chorus 1") << TR("Vibrato 1") << TR("Chorus 2") << TR("Vibrato 2") << TR("Chorus 3") << TR("Vibrato 3"))); }
Domain* Domains::PianoTypeDomain(MidiKey midiKey, QString name) { return new DiscreteDomain(
    midiKey, name, SL(TR("Grand") << TR("Upright") << TR("EPiano 1") << TR("EPiano 2") << TR("Clavinet") << TR("Harpsichord"))); }
Domain* Domains::ClavinetEq1Domain(MidiKey midiKey, QString name) { return new DiscreteDomain(
    midiKey, name, SL(TR("No Equalizer") << TR("Treble") << TR("Brilliant") << TR("Brilliant Treble"))); }
Domain* Domains::ClavinetEq2Domain(MidiKey midiKey, QString name) { return new DiscreteDomain(
    midiKey, name, SL(TR("No Equalizer") << TR("Soft") << TR("Medium") << TR("Soft Medium"))); }
Domain* Domains::PianoAcousticsDomain(MidiKey midiKey, QString name) { return new DiscreteDomain(
    midiKey, name, SL(TR("No Acoustics") << TR("String Resonance") << TR("Long Resonance") << TR("Long String Resonance"))); }
Domain* Domains::PianoDynamicsDomain(MidiKey midiKey, QString name) { return new DiscreteDomain(
    midiKey, name, SL(TR("Dynamic 0") << TR("Dynamic 1") << TR("Dynamic 2") << TR("Dynamic 3"))); }
Domain* Domains::SynthArpeggioPatterDomain(MidiKey midiKey, QString name) { return new DiscreteDomain(
    midiKey, name, SL(TR("Up") << TR("Down") << TR("UpDown") << TR("Random"))); }
Domain* Domains::SynthVoiceModeDomain(MidiKey midiKey, QString name) { return new DiscreteDomain(
    midiKey, name, SL(TR("No Glide") << TR("Legato") << TR("Mono"))); }
Domain* Domains::SynthUnisonoDomain(MidiKey midiKey, QString name) { return new DiscreteDomain(
    midiKey, name, SL(TR("No Unisono") << TR("Unisono 1") << TR("Unisono 2") << TR("Unisono 3") << TR("Multi Unisono 1")
        << TR("Multi Unisono 2") << TR("Multi Unisono 3"))); }
Domain* Domains::SynthVibratoModeDomain(MidiKey midiKey, QString name) { return new DiscreteDomain(
    midiKey, name, SL(TR("No Vibrato") << TR("Delay 1") << TR("Delay 2") << TR("Delay 3") << TR("Aftertouch") << TR("Wheel"))); }
Domain* Domains::SynthWaveFormDomain(MidiKey midiKey, QString name) { return new DiscreteDomain(
    midiKey, name, SL(TR("Square") << TR("Sawtooth") << TR("Triangle") << TR("Random"))); }
Domain* Domains::SynthOscillatorModeDomain(MidiKey midiKey, QString name) { return new DiscreteDomain(
    midiKey, name, SL(TR("Square") << TR("Sawtooth") << TR("Triangle") << TR("Random"))); }
Domain* Domains::SynthFilterTypeDomain(MidiKey midiKey, QString name) { return new DiscreteDomain(
    midiKey, name, SL(TR("Low Pass 12") << TR("Low Pass 24") << TR("High Pass") << TR("Notch") << TR("Band"))); }
Domain* Domains::Effect1TypeDomain(MidiKey midiKey, QString name) { return new DiscreteDomain(
    midiKey, name, SL(TR("Auto Pan") << TR("Tremolo") << TR("RingModulation") << TR("WaWa") << TR("AWha 1") << TR("AWha 2"))); }
Domain* Domains::Effect2TypeDomain(MidiKey midiKey, QString name) { return new DiscreteDomain(
    midiKey, name, SL (TR("Phaser 1") << TR("Phaser 2") << TR("Flanger") << TR("Vibe") << TR("Chorus 1") << TR("Chorus 2"))); }
Domain* Domains::EffectSourceDomain(MidiKey midiKey, QString name) { return new DiscreteDomain(
    midiKey, name, SL(TR("Organ") << TR("Piano") << TR("Synth"))); }
Domain* Domains::RotorSpeedDomain(MidiKey midiKey, QString name) { return new DiscreteDomain(
    midiKey, name, SL(TR("Slow") << TR("Fast"))); }
Domain* Domains::ReverbSizeDomain(MidiKey midiKey, QString name) { return new DiscreteDomain(
    midiKey, name, SL(TR("Room 1") << TR("Room 2") << TR("Stage 1") << TR("Stage 2") << TR("Hall 1") << TR("Hall 2"))); }
Domain* Domains::AmpSimTypeDomain(MidiKey midiKey, QString name) { return new DiscreteDomain(
    midiKey, name, SL(TR("Small") << TR("JC") << TR("Twin"))); }
Domain* Domains::SlotDomain(MidiKey midiKey, QString name) { return new DiscreteDomain(
    midiKey, name, SL(TR("Slot A") << TR("Slot B"))); }


//double
Domain* Domains::Domain_0_1(MidiKey midiKey, QString name) {
        return new DoubleDomain(midiKey, name, 0, 1, encode_0_1, decode_0_1); }
Domain* Domains::Domain_0_10(MidiKey midiKey, QString name) {
        return new DoubleDomain(midiKey, name, 0, 10, encode_0_10, decode_0_10); }
Domain* Domains::Domain_m10_10(MidiKey midiKey, QString name) {
        return new DoubleDomain(midiKey, name, -10, 10, encode_m10_10, decode); }
Domain* Domains::Domain_m15_15(MidiKey midiKey, QString name) {
        return new DoubleDomain(midiKey, name, -15, 15, encode_m15_15, decode); }
Domain* Domains::Domain_03_45k(MidiKey midiKey, QString name) {
        return new DoubleDomain(midiKey, name, 0.3, 45000, encodeAttack, decode); }
Domain* Domains::Domain_5_45k(MidiKey midiKey, QString name) {
        return new DoubleDomain(midiKey, name, 5, 45000, encodeDecayOrRelease, decode); }
Domain* Domains::Domain_20_21k(MidiKey midiKey, QString name) {
        return new DoubleDomain(midiKey, name, 20, 21000, encodeMidFreq, decode); }
Domain* Domains::Domain_200_8k(MidiKey midiKey, QString name) {
        return new DoubleDomain(midiKey, name, 200, 8000, encodeHighFreq, decode); }
Domain* Domains::Domain_003_523(MidiKey midiKey, QString name) {
        return new DoubleDomain(midiKey, name, 0.03, 523, encodeLowFreq, decode); }


//integer
Domain* Domains::Domain_m7_6(MidiKey midiKey, QString name) {
        return new IntegerDomain(midiKey, name, -7, 6, encodeOctaveShift, decode); }
Domain* Domains::Domain_0_127(MidiKey midiKey, QString name) {
        return new IntegerDomain(midiKey, name, 0, 127, encodeId, decodeId); }
Domain* Domains::Domain_1_52(MidiKey midiKey, QString name) {
        return new IntegerDomain(midiKey, name, 1, 52, encodePianoModel, decode); }
Domain* Domains::Domain_0_4(MidiKey midiKey, QString name) {
        return new IntegerDomain(midiKey, name, 0, 4, encodeDetune, decode); }
Domain* Domains::Domain_80_128x32(MidiKey midiKey, QString name) {
        return new IntegerDomain(midiKey, name, 80, 128*32, encodeRate, decode); }
Domain* Domains::Domains::Domain_1_128(MidiKey midiKey, QString name) {
        return new IntegerDomain(midiKey, name, 1, 128, encodeIdm1, decodeIdp1); }


double Domains::decodePitch(MidiKey key, quint8 value)
{
    double v = value +  key.code() / 128.0;     // in [0, 127.75]
    v /= 127.75;                                // in [0, 1]
    v *= 4;
    return v - 2;                               // in [-2,2]
}

QPair<MidiKey, quint8> Domains::encodePitch(double value)
{
    value = qBound(-2.0, value, 2.0);
    value /= 2;
    value += 1;         // in [0,1];
    value *= 127.75;    // in [0, 127.5];
    quint8 ival = (quint8) value;
    quint8 code = qRound((value - ival) * 128);


    return qMakePair(MidiKey(MidiKey::PitchBend, code), ival);
}










