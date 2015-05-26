#include "Molecules.h"
#include "Liaisons.h"

Molecules::Molecules():Graphes(){}

string Molecules::toString()
{
    return "Nom de la molécule :  "+ Graphes::nom_graphe+", liste des Atomes : "+
    Graphes::listeSommets() +",et des Liaisons : "+ Graphes::listeAretes();
}

void Molecules::addArete(Liaisons * arete, Atomes * s1, Atomes * s2)
{
    Graphes::addArete(arete, s1, s2);
}

void Molecules::addSommet(Atomes * sommet)
{
    Graphes::addSommet(sommet);
}

void Molecules::deleteArete(Liaisons * arete)
{
    Graphes::deleteArete(arete);
}

void Molecules::deleteSommet(Atomes * somm)
{
    Graphes::deleteSommet(somm);
}

Molecules::~Molecules()
{
}