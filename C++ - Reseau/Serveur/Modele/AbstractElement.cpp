#include <string>
#include "AbstractElement.h"

using namespace std;

AbstractElement::AbstractElement()
{
}

int AbstractElement::getId()
{
  return id;
}

void AbstractElement::setId(int id)
{
  this->id = id;
}

string AbstractElement::getNom()
{
  return nom;
}

void AbstractElement::setNom(string nom)
{
  this->nom = nom;
}

string AbstractElement::getPath()
{
  return path;
}

void AbstractElement::setPath(string path)
{
  this->path = path;
}

void AbstractElement::setFichier(ifstream* f)
{
    this->fichier = f;
}

ifstream    *AbstractElement::getFichier()
{
    return this->fichier;
}

AbstractElement::~AbstractElement()
{
    delete this->fichier;
}
