#include "includes.h"
#include "Sommets.h"
#include "Aretes.h"

using namespace std;

int Sommets::num;

Sommets::Sommets()
{
    Sommets::num++;
    stringstream s;
    s << "Sommet " << num;

	this->nom = s.str();
    this->graphe = NULL;
	this->listeAretes =set<Aretes*>();
}

string Sommets::toString()
{
	return this->nom;
}

/**
 * \fn addArete
 * \param Aretes *arete
 *
 * \brief Ajout d'une arete
 */
void Sommets::addArete(Aretes * arete)
{
	this->listeAretes.insert(arete);
}

void Sommets::setGraphe(Graphes *g)
{
	this->graphe = g;
}


Graphes* Sommets::getGraphe()
{
	return this->graphe;
}

Sommets::~Sommets()
{
}