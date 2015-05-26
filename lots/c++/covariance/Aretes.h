#ifndef _Aretes
#define _Aretes

#include "includes.h"

class Sommets;
class Graphes;

using namespace std;

class Aretes
{
	public:
        string nom;
	    Graphes* graphe;
	    Sommets* s1;
	    Sommets* s2;
	    static int num;

    Aretes();
    Aretes(Graphes*,Sommets*,Sommets*);

        void setSommets(Sommets*,Sommets*);
        Graphes* getGraphe();
	    void setGraphe(Graphes*);
	    string toString();

	    virtual ~Aretes();
};

#endif
