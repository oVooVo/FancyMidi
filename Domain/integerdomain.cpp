#include "integerdomain.h"

Domain* IntegerDomain::copy(Keyboard* keyboard) const
{
    return new IntegerDomain(midicode(), name(), min(), max(), value(), _encoder, _decoder, keyboard);
}


