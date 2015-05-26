#include "Sommets.h"
#include "Molecules.h"

#ifndef _Atomes
#define _Atomes


class Atomes:public Sommets<Molecules,Atomes,Liaisons>{
public:
    Atomes();
    virtual ~Atomes();

    using Sommets::addArete;
};

#endif
