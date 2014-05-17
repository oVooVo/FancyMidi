#ifndef NORDSTAGE2_H
#define NORDSTAGE2_H
#include "keyboard.h"
#include <QDebug>
#include <QTimer>

class NordStage2 : public Keyboard
{
    Q_OBJECT
public:
    enum Preset { PresetI, PresetII };
    enum Status { On, Off };
    enum OrganModel { B3, Vox, Farfisa };
    enum OrganVibratoType { C1, C2, C3, V1, V2, V3 };
    NordStage2();

public slots:

    //=====  Effects ================================
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
    void setOrganPercussionHarmonic(Status status);
    void setOrganPercussionSpeed(Status status);
    void setOrganPercussionLevel(Status status);
    void setOrganOctaveShift(int shift);
    void setOrganLevel(quint8 level);
    void setOrganEnabled(Status status);


private:
    quint8 encodeOctaveShift(int shift);
    QTimer* _timer = 0;
    quint8 _time = 0;
};

#endif // NORDSTAGE2_H
