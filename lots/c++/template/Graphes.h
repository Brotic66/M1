#ifndef _Graphes
#define _Graphes

#include "includes.h"

using namespace std;

template <class G,class S,class A>
class Graphes {
    public:
        string nom;
        static int num;
        set<S*> sommets;
        set<A*> aretes;

        Graphes();

        virtual string toString();
        void addArete(A*,S*,S*);
        void addSommet(S*);
        void deleteArete(A*);
        void deleteSommet(S*);

        virtual ~Graphes();

    protected:
        string listeSommets();
        string listeAretes();

    private:
        typename set<S*>::iterator itS;
        typename set<A*>::iterator itA;

};



template <class G,class S,class A>
int Graphes<G, S, A>::num;

template <class G,class S,class A>
Graphes<G, S, A>::Graphes()
{
    Graphes::num++;
    stringstream s;
    s << "Graphe " << num;
	this->nom = s.str();
}

template <class G,class S,class A>
string Graphes<G, S, A>::toString()
{
	return "Nom du graphe :  "+ this->nom +", liste des sommets: "
    + this->listeSommets() +"et des arêtes:"+ this->listeAretes();
}

template <class G,class S,class A>
string Graphes<G, S, A>::listeSommets()
{
    string ret="";
	if (sommets.size()==0)
    {
		return "aucun sommet";
	}
    else
    {
		for (itS=sommets.begin(); itS!=sommets.end();itS++)
        {
			ret+=itS.operator*()->toString()+" ";
		}

		return ret;
	}
}

template <class G,class S,class A>
string Graphes<G, S, A>::listeAretes()
{
    string ret="";
    if (aretes.size()==0)
    {
        return "aucune arêtes";
    }
    else
    {
        for (itA=aretes.begin(); itA!=aretes.end();itA++)
        {
            ret+=itA.operator*()->toString()+"";
        }

        return ret;
    }
}

template <class G,class S,class A>
void Graphes<G, S, A>::addArete(A* arete,S* s1,S* s2)
{
	if (arete->getGraphe()==NULL)
    {
        arete->setGraphe(dynamic_cast<G*>(this));
    }

    s1->setGraphe(dynamic_cast<G*>(this));
	s2->setGraphe(dynamic_cast<G*>(this));
	s1->addArete(arete);
	s2->addArete(arete);
    arete->setSommets(s1, s2);
    aretes.insert(arete);
    
}

template <class G,class S,class A>
void Graphes<G, S, A>::addSommet(S* sommets)
{
	if (sommets->getGraphe() == NULL)
    {
        sommets->setGraphe(dynamic_cast<G*>(this));
    }

    this->sommets.insert(sommets);
}

template <class G,class S,class A>
void Graphes<G, S, A>::deleteArete(A* arete)
{
	if (aretes.erase(arete)==1)
    {
		arete->setGraphe(NULL);
		arete->setSommets(NULL, NULL);
	}
    else
    {
	}
}

template <class G,class S,class A>
void Graphes<G, S, A>::deleteSommet(S* p_sommet)
{
	if (sommets.erase(p_sommet)==1)
    {
		p_sommet->setGraphe(NULL);
		while (p_sommet->itAS!=p_sommet->liste_aretes.end())
        {
			deleteArete(*p_sommet->itAS);
            p_sommet->itAS++;
		}
	}
    else
    {
	}
}

template <class G,class S,class A>
Graphes<G, S, A>::~Graphes()
{
}

#endif
