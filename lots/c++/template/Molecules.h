#include "includes.h"
#include "Graphes.h"
class Atomes;
class Liaisons;
using namespace std;

#ifndef _Molecules
#define _Molecules

class Molecules: public Graphes<Molecules,Atomes,Liaisons>{
public:

	Molecules();
    string toString();

    using Graphes::addArete;
    using Graphes::addSommet;
    using Graphes::deleteArete;
    using Graphes::deleteSommet;

    virtual ~Molecules();
};

#endif
