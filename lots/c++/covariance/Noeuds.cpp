#include "Noeuds.h"
#include "Liens.h"

Noeuds::Noeuds():Sommets()
{
}

void Noeuds::addArete(Liens * arete)
{
    Sommets::addArete(arete);
}

Noeuds::~Noeuds()
{
}