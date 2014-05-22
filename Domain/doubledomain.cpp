#include "doubledomain.h"

Domain* DoubleDomain::copy(Keyboard* keyboard) const
{
    return new DoubleDomain(midicode(), name(), min(), max(), value(), _encoder, _decoder, keyboard);
}
