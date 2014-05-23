#ifndef DOUBLEDOMAIN_H
#define DOUBLEDOMAIN_H

#include "continousdomain.h"
#include <QString>

class DoubleDomain : public ContinousDomain<double>
{
public:
    DoubleDomain(MidiKey midiKey, QString name,
                 double min, double max, Encoder(double) encoder, Decoder(double) decoder,
                 Keyboard* keyboard = 0)
        : ContinousDomain(midiKey, name, min, max, encoder, decoder, keyboard) {}
    DoubleDomain(MidiKey midiKey, QString name,
                 double min, double max, double value, Encoder(double) encoder, Decoder(double) decoder,
                 Keyboard* keyboard = 0)
        : ContinousDomain(midiKey, name, min, max, value, encoder, decoder, keyboard) {}
    Type type() const { return Double; }
    Domain* copy(Keyboard *keyboard) const;

protected:

};


#endif // DOUBLEDOMAIN_H
