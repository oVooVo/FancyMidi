#include "doubledomain.h"

Domain* DoubleDomain::copy(Keyboard* keyboard) const
{
    return new DoubleDomain(midiKey(), name(), min(), max(), value(), _encoder, _decoder, keyboard);
}
