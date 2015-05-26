#include "Liaisons.h"

Liaisons::Liaisons():Aretes()
{
}

void Liaisons::setSommets(Atomes *s1, Atomes *s2)
{
    Aretes::setSommets(s1, s2);
}

Liaisons::~Liaisons()
{
}