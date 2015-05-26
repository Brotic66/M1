#include "Aretes.h"
#include "Molecules.h"
#include "Atomes.h"

#ifndef _Liaisons
#define _Liaisons

class Liaisons: public Aretes
{
    public:
        Liaisons();

        void setSommets(Atomes*,Atomes*);

        virtual ~Liaisons();
};

#endif
