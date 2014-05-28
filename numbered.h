#ifndef NUMBERED_H
#define NUMBERED_H

class Numbered
{
public:
    Numbered() {}
    Numbered(int number);

    int number() const { return _number; }
    void setNumber(int number) { _number = number; }

private:
    int _number = -1;
};

#endif // NUMBERED_H
