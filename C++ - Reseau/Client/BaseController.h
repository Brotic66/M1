/*!
 * \file BaseController.h
 * \class BaseController
 * \brief Classe controleur de base gerant la boite reseaux et commandes
 * \author Loïc MERCIER
 * \date 19/12/2014
 */

#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

using namespace std;

#include <fstream>

typedef struct M{
  char option; // g {get} p {put} l {ls}
  char ctrl; // n {noexist}  e {exist} c {encours} f {fini}
short int taille; // taille de la data
char data[512]; // donnees
}Message;

typedef struct PS{
  int descr;
  char adresse[100];
ofstream fichierRecu;
ifstream fichierEnvoye;
}ParamSocket;

struct BIS
{
    int port;
    ParamSocket *ps;
};

class BaseController
{
 private :

  int sockClient;
  struct sockaddr_in client;
  socklen_t tailleClient;
  Sock *sock;
  SockDist *host;

  pthread_t idThreadLire;
  pthread_t idThreadUpload;
  // pas forcemment utile de le metre en attribut
  ParamSocket ps;
  int       portGet;

//ofstream fichierRecu;
//ifstream fichierEnvoye;

 public:
  BaseController();
  ~BaseController();

  int connection(const char* adresse, int port);
  void attenteCommande();
  void download(string param);
  void downloadGet(string param);
  void upload(string param);
  void afficherContenu();
  void deconnection();
  void help();
  int attenteFinThreads();
  // void    viderTampon(char *buffer, int size);
  // void    deco();

};


#endif
