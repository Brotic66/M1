#include "includes.h"
#include "Graphes.h"
#include "Sommets.h"
#include "Aretes.h"

using namespace std;

int Graphes::num;

Graphes::Graphes()
{
    Graphes::num++;
    stringstream s;
    s << "Graphe " << num;
	nom_graphe=s.str();
}

string Graphes::toString()
{
	return "Nom du graphe :  "+nom_graphe+", liste des sommets: "
    +listeSommets()+"et des arêtes:"+listeAretes();
}


string Graphes::listeSommets()
{
    string ret="";
	if (sommets.size()==0)
    {
		return "aucun sommet";
	}
    else
    {
		for (itS=sommets.begin(); itS!=sommets.end();itS++)
			ret+=itS.operator*()->toString()+" ";

		return ret;
	}
}


string Graphes::listeAretes()
{
    string ret="";
    if (aretes.size()==0)
    {
        return "aucune arêtes";
    }else
    {
        for (itA=aretes.begin(); itA!=aretes.end();itA++)
            ret+=itA.operator*()->toString()+"";

        return ret;
    }
}

/**
 * \fn addArete
 * \param Arete *arete
 * \param Sommets *s1
 * \param Sommets *s2
 *
 * \brief Ajoute une arete ainsi que 2 sommet à cette arete et au graphe
 */
void Graphes::addArete(Aretes * arete, Sommets * s1,Sommets * s2)
{
    arete->setGraphe(this);
    s1->setGraphe(this);
	s2->setGraphe(this);
	s1->addArete(arete);
	s2->addArete(arete);
    arete->setSommets(s1, s2);
    aretes.insert(arete);
}

/**
 * \fn addSommet
 * \param Sommets *sommets
 *
 * \brief Ajoute un sommet au graphe
 */
void Graphes::addSommet(Sommets * sommets)
{
    sommets->setGraphe(this);
    this->sommets.insert(sommets);
}

/**
 * \fn deleteArete
 * \param Aretes *arete
 *
 * \brief Supprime une arete du graphe
 */
void Graphes::deleteArete(Aretes* arete)
{
	if (aretes.erase(arete) == 1)
    {
		arete->setGraphe(NULL);
		arete->setSommets(NULL, NULL);
	}
    else
    {
        cout << "Erreur : Impossible de supprimer l'arete" << endl;
	}
}

/**
 * \fn deleteSommet
 * \param Sommets *sommet
 *
 * \brief Supprime un sommet du graphe
 */
void Graphes::deleteSommet(Sommets* sommet)
{
	if (sommets.erase(sommet) == 1)
    {
		sommet->setGraphe(NULL);
		while (sommet->itAS != sommet->listeAretes.end())
        {
            sommet->itAS++;
		}
	}
    else
    {
        cout << "Erreur : Impossible de supprimer le sommet" << endl;
	}
}


Graphes::~Graphes()
{
}