#ifndef FICHIER_H
#define FICHIER_H

#include <string>
#include <iostream>
#include "AbstractElement.h"

using namespace std;

class Fichier : public AbstractElement
{
 private :
  string type;

 public :
  Fichier();
  Fichier(string type);
  string getType();
  void setType(string type);

};


#endif
