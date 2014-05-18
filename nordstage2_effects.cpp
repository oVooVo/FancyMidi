#include <nordstage2.h>

void NordStage2::setEffect1Type(Effect1Type type)
{
    sendMidiControlCommand(60, type);
}

void NordStage2::setEffect1Source(EffectSource source)
{
    sendMidiControlCommand(61, source);
}

void NordStage2::setEffect1Amount(double amount)
{
    sendMidiControlCommand(62, encode_0_10(amount));
}

void NordStage2::setEffect1Rate(quint8 rate)
{
    sendMidiControlCommand(63, rate);
}

void NordStage2::setEffect1Enable(Status status)
{
    sendMidiControlCommand(69, status);
}

void NordStage2::setEffect1MstClk(Status status)
{
    sendMidiControlCommand(117, status);
}

void NordStage2::setEffect2Type(Effect2Type type)
{
    sendMidiControlCommand(70, type);
}

void NordStage2::setEffect2Source(EffectSource source)
{
    sendMidiControlCommand(71, source);
}

void NordStage2::setEffect2Amount(double amount)
{
    sendMidiControlCommand(72, encode_0_10(amount));
}

void NordStage2::setEffect2Rate(quint8 rate)
{
    sendMidiControlCommand(73, rate);
}

void NordStage2::setEffect2Enable(Status status)
{
    sendMidiControlCommand(74, status);
}

void NordStage2::setEffect2MstClk(Status status)
{
    sendMidiControlCommand(118, status);
}

void NordStage2::setDelayDestination(EffectSource destination)
{
    sendMidiControlCommand(75, destination);
}

void NordStage2::setDelayAmount(double amount)
{
    sendMidiControlCommand(76, encode_0_10(amount));
}

void NordStage2::setDelayRate(quint8 rate)
{
    sendMidiControlCommand(77, rate);
}

void NordStage2::setDelayFeedback(double feedback)
{
    sendMidiControlCommand(78, encode_0_10(feedback));
}

void NordStage2::setDelayPingPongOnOff(Status status)
{
    sendMidiControlCommand(79, status);
}

void NordStage2::setDelayEnable(Status status)
{
    sendMidiControlCommand(80, status);
}

void NordStage2::setDelayMstClk(Status status)
{
    sendMidiControlCommand(119, status);
}

void NordStage2::setAmpSimType(AmpSimType type)
{
    sendMidiControlCommand(81, type);
}

void NordStage2::setAmpSimDrive(double drive)
{
    sendMidiControlCommand(83, drive);
}

void NordStage2::setAmpSimDestination(EffectSource source)
{
    sendMidiControlCommand(81, source);
}

void NordStage2::setAmpSimBassEQ(double dB)
{
    sendMidiControlCommand(84, encode_m15_15(dB));
}

void NordStage2::setAmpSimMidEQ(double dB)
{
    sendMidiControlCommand(85, encode_m15_15(dB));
}

void NordStage2::setAmpSimMidRange(double range)
{
    sendMidiControlCommand(6, encodeHighFreq(range));
}

void NordStage2::setAmpSimTrebleEQ(double dB)
{
    sendMidiControlCommand(86, encode_m15_15(dB));
}

void NordStage2::setAmpSimEnabled(Status status)
{
    sendMidiControlCommand(87, status);

}

void NordStage2::setRotorDestination(EffectSource source)
{
    sendMidiControlCommand(88, source);
}

void NordStage2::setRotorDrive(double drive)
{
    sendMidiControlCommand(89, encode_m10_10(drive));
}

void NordStage2::setRotorSpeed(RotorSpeed speed)
{
    sendMidiControlCommand(82, speed);
}

void NordStage2::setRotorStop(Status status)
{
    sendMidiControlCommand(91, status);
}

void NordStage2::setRotorEnable(Status status)
{
    sendMidiControlCommand(92, status);
}

void NordStage2::setCompressorAmount(double amount)
{
    sendMidiControlCommand(93, encode_0_10(amount));
}

void NordStage2::setCompressorEnable(Status status)
{
    sendMidiControlCommand(94, status);
}

void NordStage2::setReverbAmount(double amount)
{
    sendMidiControlCommand(95, amount);
}

void NordStage2::setReverbSize(ReverbSize size)
{
    sendMidiControlCommand(96, size);
}

void NordStage2::setReverbEnabled(Status status)
{
    sendMidiControlCommand(97, status);
}
