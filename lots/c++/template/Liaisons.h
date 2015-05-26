#include "Aretes.h"
#include "Molecules.h"
#include "Atomes.h"

#ifndef _Liaisons
#define _Liaisons

class Liaisons:public Aretes<Molecules,Atomes,Liaisons>{
public:
    Liaisons();

    using Aretes::setGraphe;
    using Aretes::setSommets;

    virtual ~Liaisons();
};

#endif /* defined(_Liaisons) */
