#include "packet.h"

Packet::Packet(int id)
{
    _id = id;
}

Packet::~Packet()
{
}

int Packet::getId()
{
    return _id;
}

void Packet::setId(int id)
{
    _id = id;
}









