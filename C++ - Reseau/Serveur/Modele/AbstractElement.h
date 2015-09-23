#ifndef ABSTRACTELEMENT_H
#define ABSTRACTELEMENT_H

#include <string>
#include <fstream>

using namespace std;

class AbstractElement
{
 protected :
  int id;
  string nom;
  string path;
  ifstream *fichier = NULL;

 public :
  AbstractElement();
  int getId();
  void setId(int id);
  string getNom();
  void setNom(string nom);
  string getPath();
  void setPath(string path);

    void        setFichier(ifstream*);
    ifstream    *getFichier();

    ~AbstractElement();

};


#endif
