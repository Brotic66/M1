#include "includes.h"
#include "Graphes.h"
class Noeuds;
class Liens;
using namespace std;

#ifndef _Reseaux
#define _Reseaux

class Reseaux: public Graphes<Reseaux,Noeuds,Liens>{
public:

	Reseaux();
    string toString();

    using Graphes::addArete;
    using Graphes::addSommet;
    using Graphes::deleteArete;
    using Graphes::deleteSommet;

    virtual ~Reseaux();
};

#endif
