#include "Reseaux.h"
#include "Liens.h"

Reseaux::Reseaux():Graphes()
{

}

string Reseaux::toString()
{
    return "Nom du réseau :  "+ Graphes::nom_graphe +", liste des noeuds : "+
    Graphes::listeSommets() +",et des liens : "+ Graphes::listeAretes();
}

void Reseaux::addArete(Liens * arete, Noeuds * s1, Noeuds * s2)
{
    Graphes::addArete(arete, s1, s2);
}

void Reseaux::addSommet(Noeuds * sommet)
{
    Graphes::addSommet(sommet);
}

void Reseaux::deleteArete(Liens * arete)
{
    Graphes::deleteArete(arete);
}

void Reseaux::deleteSommet(Noeuds * sommet)
{
    Graphes::deleteSommet(sommet);
}

Reseaux::~Reseaux()
{

}