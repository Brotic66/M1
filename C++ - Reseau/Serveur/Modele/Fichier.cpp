#include "Fichier.h"

using namespace std;

Fichier::Fichier()
{
}

Fichier::Fichier(string type)
{
  this->type = type;
}

string Fichier::getType()
{
  return type;
}

void Fichier::setType(string type)
{
  this->type = type;
}
