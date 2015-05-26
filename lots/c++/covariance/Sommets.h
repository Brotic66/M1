#include "includes.h"
class Graphes;
class Aretes;

using namespace std;

#ifndef _Sommets
#define _Sommets


class Sommets
{
    public:
        string nom;
        Graphes* graphe;
        set<Aretes*> listeAretes;
        typename set<Aretes*>::iterator itAS;
        static int num;

        Sommets();

        void addArete(Aretes*);
        Graphes* getGraphe();
        void setGraphe(Graphes*);
        string toString();

        virtual ~Sommets();
};

#endif
