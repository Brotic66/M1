#ifndef _Aretes
#define _Aretes

#include "includes.h"
using namespace std;

template <class G,class S,class A>
class Aretes
{
    public:
        string nom;
        G* graphe;
        S* s1;
        S* s2;
        static int num;

        Aretes();

        void setSommets(S*,S*);
        G* getGraphe();
        void setGraphe(G*);
        virtual string toString();

	    virtual ~Aretes();
};


template <class G,class S,class A>
int Aretes<G, S, A>::num;

template <class G,class S,class A>
Aretes<G,S,A>::Aretes()
{
    Aretes::num++;
    stringstream s;
    s << "Arete " << num;

	this->nom = s.str();
	this->graphe = NULL;
    this->s1 = NULL;
    this->s2 = NULL;
}

//Ajout de 2 sommets à une arrete
template <class G,class S,class A>
void Aretes<G,S,A>::setSommets(S* s1,S* s2)
{
    this->s1 = s1;
    this->s2 = s2;
}

template <class G,class S,class A>
G* Aretes<G,S,A>::getGraphe()
{
    return this->graphe;
}

template <class G,class S,class A>
void Aretes<G,S,A>::setGraphe(G* graphe)
{
	this->graphe = graphe;
}

template <class G,class S,class A>
string Aretes<G,S,A>::toString()
{
	return this->nom;
}

template <class G,class S,class A>
Aretes<G,S,A>::~Aretes<G, S, A>()
{
}


#endif
