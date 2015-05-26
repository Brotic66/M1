#ifndef _Sommets
#define _Sommets

#include "includes.h"
#include "Aretes.h"
using namespace std;

template <class G,class S,class A>
class Sommets
{
    public:
        string nom;
        G* graphe;
        set<A*> listeAretes;
        typename set<A*>::iterator itAS;
        static int num;

        Sommets();

        virtual void addArete(A*);
        G* getGraphe();
        void setGraphe(G*);
        string toString();

        virtual ~Sommets();
};

template <class G,class S,class A>
int Sommets<G, S, A>::num;

template <class G,class S,class A>
Sommets<G,S,A>::Sommets()
{
    Sommets::num++;
    stringstream s;
    s << "Sommet " << num;
	this->nom = s.str();
    this->graphe = NULL;
	this->listeAretes = set<A*>();
}

template <class G,class S,class A>
string Sommets<G,S,A>::toString()
{
	return this->nom;
}

template <class G,class S,class A>
void Sommets<G,S,A>::addArete(A* arete)
{
	this->listeAretes.insert(arete);
}

template <class G,class S,class A>
void Sommets<G,S,A>::setGraphe(G *graphe)
{
	this->graphe = graphe;
}

template <class G,class S,class A>
G* Sommets<G,S,A>::getGraphe()
{
	return this->graphe;
}

template <class G,class S,class A>
Sommets<G,S,A>::~Sommets()
{
}

#endif
