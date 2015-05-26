#include "includes.h"
#include "Graphes.h"
#include "Sommets.h"
#include "Aretes.h"
#include "Reseaux.h"
#include "Noeuds.h"
#include "Liens.h"
#include "Molecules.h"
#include "Atomes.h"
#include "Liaisons.h"
using namespace std;

int main( int argc, const char* argv[] )
{
    cout << "========== Création d'un réseau informatique ==========" << endl;
    Reseaux *res = new Reseaux();
    Noeuds *n1 = new Noeuds();
    Noeuds *n2 = new Noeuds();
    Liens *l = new Liens();

    res->addSommet(n1);
    res->addSommet(n2);
    res->addArete(l, n1, n2);

    cout << res->toString() << endl;

    cout << "========== Création d'un réseau moléculaire ==========" << endl;
    Molecules *mol = new Molecules();
    Atomes *a1 = new Atomes();
    Atomes *a2 = new Atomes();
    Liaisons *l2 = new Liaisons();

    mol->addSommet(a1);
    mol->addSommet(a2);
    mol->addArete(l2, a1, a2);

    cout << mol->toString() << endl;

	return 0;
}
