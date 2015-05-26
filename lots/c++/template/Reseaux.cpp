#include "Reseaux.h"
#include "Liens.h"

Reseaux::Reseaux():Graphes<Reseaux,Noeuds,Liens>(){}

string Reseaux::toString()
{
    return "Nom du réseau :  "+Graphes::nom+", liste des noeuds : "+
    Graphes::listeSommets()+",et des liens : "+Graphes::listeAretes();
}

Reseaux::~Reseaux(){}