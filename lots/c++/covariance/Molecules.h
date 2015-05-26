#include "includes.h"
#include "Graphes.h"
class Atomes;
class Liaisons;
using namespace std;

#ifndef _Molecules
#define _Molecules

class Molecules: public Graphes
{
    public:
        Molecules();

        string toString();
        void addArete(Liaisons*,Atomes*,Atomes*);
        void addSommet(Atomes*);
        void deleteArete(Liaisons*);
        void deleteSommet(Atomes*);

        virtual ~Molecules();
};

#endif
