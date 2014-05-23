#ifndef INTEGERDOMAIN_H
#define INTEGERDOMAIN_H

#include "continousdomain.h"
#include <QString>

class IntegerDomain : public ContinousDomain<int>
{
public:
    IntegerDomain(MidiKey midiKey, QString name,
                  int min, int max, Encoder(int) encoder, Decoder(int) decoder,
                  Keyboard* keyboard = 0)
        : ContinousDomain(midiKey, name, min, max, encoder, decoder, keyboard) {}
    IntegerDomain(MidiKey midiKey, QString name,
                  int min, int max, int value, Encoder(int) encoder, Decoder(int) decoder,
                  Keyboard* keyboard = 0)
        : ContinousDomain(midiKey, name, min, max, value, encoder, decoder, keyboard) {}
    Type type() const { return Integer; }

    Domain* copy(Keyboard *keyboard) const;



};

#endif // INTEGERDOMAIN_H
