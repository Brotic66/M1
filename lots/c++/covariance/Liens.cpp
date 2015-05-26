#include "Liens.h"

Liens::Liens():Aretes(){}

void Liens::setSommets(Noeuds * s1, Noeuds * s2)
{
    Aretes::setSommets(s1, s2);
}

Liens::~Liens(){}