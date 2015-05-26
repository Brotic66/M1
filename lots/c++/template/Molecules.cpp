#include "Molecules.h"
#include "Liaisons.h"

Molecules::Molecules():Graphes<Molecules,Atomes,Liaisons>(){}

string Molecules::toString(){
    return "Nom de la molécule :  "+Graphes::nom+", liste des Atomes : "+
    Graphes::listeSommets()+",et des Liaisons : "+Graphes::listeAretes();
}


Molecules::~Molecules(){}