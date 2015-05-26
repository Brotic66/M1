#include "Atomes.h"
#include "Liaisons.h"

Atomes::Atomes(): Sommets()
{
}

void Atomes::addArete(Liaisons * arete)
{
    Sommets::addArete(arete);
}

Atomes::~Atomes()
{
}