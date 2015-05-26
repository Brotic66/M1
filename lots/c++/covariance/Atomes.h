#include "Sommets.h"
#include "Molecules.h"

#ifndef _Atomes
#define _Atomes


class Atomes:public Sommets
{
    public:
        Atomes();

        void addArete(Liaisons*);

        virtual ~Atomes();
};

#endif
