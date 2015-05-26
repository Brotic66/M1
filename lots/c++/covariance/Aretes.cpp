#include "includes.h"
#include "Aretes.h"
#include "Graphes.h"
#include "Sommets.h"

using namespace std;

int Aretes::num;

Aretes::Aretes()
{
    Aretes::num++;
    stringstream s;
    s << "Arete " << num;

    this->nom=s.str();
	this->graphe =NULL;
    this->s1=NULL;
    this->s2=NULL;
}

Aretes::Aretes(Graphes *graphes, Sommets *sommets1, Sommets *sommets2)
{
    Aretes::num++;
    stringstream s;
    s << "Arete " << num;

    this->nom = s.str();
    this->graphe = graphes;
    this->s1= sommets1;
    this->s2 = sommets2;
}

/**
 * \fn setSommets
 * \param Sommets *s1
 * \param Sommets *s2
 *
 * \brief Ajout de 2 sommets à l'arete
 */
void Aretes::setSommets(Sommets * s1,Sommets * s2)
{
    this->s1 = s1;
    this->s2 = s2;
}

Graphes* Aretes::getGraphe()
{
    return graphe;
}


void Aretes::setGraphe(Graphes * a)
{
	graphe = a;
}

string Aretes::toString()
{
	return nom;
}

Aretes::~Aretes()
{
}