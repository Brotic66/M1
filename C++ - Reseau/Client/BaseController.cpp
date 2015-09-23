
#define TAILLE_INITIALISATION 516
#define TAILLE_BUFFER_MAX 512
#define TAILLE_MESSAGE_MAX 516
#define PORT_PUT 4411

#define GET 'g'
#define PUT 'p'
#define LS 'l'
#define NOEXIST 'n'
#define EXIST 'e'
#define ENCOURS 'c'
#define FIN 'f'
#define QUIT 'q'

#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <stdio.h> // atoi
#include <stdlib.h> // perror
//#include <errno.h>
#include <pthread.h>
#include "sock.h"
#include "sockdist.h"
#include "BaseController.h"
#include <string.h>
#include <fstream>

using namespace std;

/*
typedef struct M{
  string option;
  string path;
}Message;

typedef struct PS{
  int descr;
  Message m;
  }ParamSocket;*/
int compteur=0;


void *threadGet(void *par)
{
    struct BIS *pp = (struct BIS*) par;
  Message m;

sleep(2);

    Sock *sock = new Sock(SOCK_STREAM, 0);
    SockDist *host = new SockDist(pp->ps->adresse, (short)pp->port);
    if (connect(sock->getsDesc(),(sockaddr*)host->getAdrDist(), host->getsLen()) < 0)
    {
      perror("erreur connection");
    }

  int sockBis = sock->getsDesc();
  char octet;
  recv(sockBis, &octet, 1, 0);
    if (octet == '0')
    {
        cout << "fichier inexistant" << endl;
      return NULL;
    }

    cout << "début du transfert" << endl;

  bool terminer = false;
  struct timeval tt;
  char buffer[TAILLE_BUFFER_MAX];


    while (!terminer)
    {
        int nbr = 0;
        int ret = 0;
        fd_set readfs;
	tt.tv_sec = 5;
	tt.tv_usec = 0;
        FD_ZERO(&readfs);
        FD_SET(sockBis, &readfs);

        ret = select(sockBis + 1, &readfs, NULL, NULL, &tt);


        if (FD_ISSET(sockBis, &readfs))
        {
            nbr = recv(sockBis, buffer, TAILLE_BUFFER_MAX, 0);
            pp->ps->fichierRecu.write(buffer, nbr);
        }

       if (ret <= 0)
        {
            pp->ps->fichierRecu.close();
            close(sockBis);
            delete sock;
            delete host;
            terminer = true;
            cout << "fin de Get" << endl;
        }
    }
  }



void *threadLire (void * par)
{
  ParamSocket *ps = ((ParamSocket*)(par));

  bool continuer = true;


while(continuer)
  {
Message m;

int r = recv(ps->descr, &m, TAILLE_MESSAGE_MAX, 0);

	cout << "reception" << endl;
 if(m.option == LS)
   {
     // On recupere la liste
	//if(m.ctrl==FIN)

     cout << m.data << endl;
   }
 else if(m.option == QUIT)
   {
	continuer = false;
   }

  }

	cout << "c" << endl;
  pthread_exit(NULL);

}

void *threadUpload (void * par)
{
  ParamSocket *ps = ((ParamSocket*)(par));
  //char messageRecu[TAILLE_MESSAGE_MAX];
  // On attends que le serveur recoive notre message de depart
  sleep(1);

  Sock *sock = new Sock(SOCK_STREAM, 0);
  SockDist *host = new SockDist(ps->adresse, (short)PORT_PUT);
  if (connect(sock->getsDesc(),(sockaddr*)host->getAdrDist(), host->getsLen()) < 0)
    {
      perror("erreur connection");
    }

  int sockBis = sock->getsDesc();

  char *buffer = new char[TAILLE_BUFFER_MAX];
  bool continuer=true;
  cout << "départ" << endl;
  while(continuer)
    {
    Message m;
    m.option = PUT;
    m.ctrl = ENCOURS;


        if(ps->fichierEnvoye.good())
        {

            ps->fichierEnvoye.read(buffer, TAILLE_BUFFER_MAX);
            int nbrCaracteresLu = ps->fichierEnvoye.gcount();
            if (nbrCaracteresLu < 512)
            {

     cout << "fini" << endl;
                m.ctrl = FIN;
                continuer = false;
            }

            m.taille = nbrCaracteresLu;

            //strcpy(m.data, buffer);
for(int i=0;i<nbrCaracteresLu;i++)
	m.data[i] = buffer[i];

            send(sockBis, buffer, nbrCaracteresLu, 0);

        }

    }

	delete buffer;
    delete sock;
    delete host;

    ps->fichierEnvoye.close();
    pthread_exit(NULL);

}

BaseController::BaseController()
{
  //tailleClient = sizeof client;
   sock = new Sock(SOCK_STREAM, 0);
   if (sock->good()){
     sockClient = sock->getsDesc();
     // On enregistre le descripteur dans la structure
     ps.descr=sockClient;

   }
   tailleClient = sizeof client;
   host = NULL;
}

BaseController::~BaseController()
{cout << "a" << endl;
  if(host != NULL)
    delete host;
cout << "b" << endl;
}

int BaseController::connection(const char* adresse, int port)
{
  host = new SockDist(adresse, (short)port);
  if (connect(sockClient,(sockaddr*)host->getAdrDist(), host->getsLen()) < 0)
    {
      perror("erreur connection");
      return -1;
    }

    recv(ps.descr, &this->portGet, sizeof(int), 0);
    cout << portGet << endl;

  cout << "Vous etes connecte sur le reseaux de la NASA !" << endl;
   // On lance le thread de reception
  strcpy(ps.adresse, adresse);

  pthread_create(&idThreadLire, NULL, threadLire, &ps);
  return 0;
}

 void BaseController::attenteCommande()
 {
   bool connecte = true;
   string com, param;

       while (connecte)
    {
        cout << "veuillez entrer une commande(help pour voir liste des commandes) : ";
        cin >> com;
        if (com == "get")
        {
cout << "veuillez entrer un nom de fichier " << endl;
            cin >> param;
            if (param.size() != 0)
            downloadGet(param);
            else
                cout << "veuillez entrer un nom de fichier ( help pour plus d'informations )." << endl;
        }
        else if (com == "put")
        {
            cin >> param;
            if (param.size() != 0)
            upload(param);
            else
                cout << "veuillez entrer un nom de fichier ( help pour plus d'informations )." << endl;
        }
        else if (com == "ls")
            afficherContenu();
        else if (com == "help"){
	  	  help();
	}
        else if (com == "exit" || com == "Exit" || com == "e" || com == "E" || com == "q" || com == "Q")
        {
	  // deco(socke);
	  cout << "bye" << endl;
            connecte = false;
            deconnection();
        }
        else
            cout << "Commande inconnu ! Pour plus d'information tapper \"help\"." << endl;

        com.erase(com.begin(), com.end());
    }
}

void BaseController::downloadGet(string param)
{

  // On enregistre l'option et le nom du fichier dans la structure
  Message m;
  m.option=GET;
  m.ctrl = ENCOURS;
  m.taille = param.length()+1;
  for(int i=0;i<param.length();i++)
    {
      m.data[i]=param[i];
    }
  m.data[param.length()] = '\0';


  struct BIS   *pp = new struct BIS;
  pp->port = this->portGet;
  pp->ps = &this->ps;
    pp->ps->fichierRecu.open (m.data, ios::out | ios::binary | ios::trunc );
  send(ps.descr,&m,TAILLE_INITIALISATION, 0);
  pthread_t idThread;

  pthread_create(&idThread, NULL, threadGet, pp);

}

void BaseController::upload(string param)
{

  // On enregistre l'option et le nom du fichier dans la structure
  Message m;
  m.option=PUT;
  m.ctrl = ENCOURS;
  m.taille = param.length();
  for(int i=0;i<param.length();i++)
    {
      m.data[i]=param[i];
    }
  m.data[param.length()] = '\0';
  // strcpy(m.data, param);


  send(ps.descr,&m,sizeof(m), 0);

  // on ouvre le fichier
    ps.fichierEnvoye.open(m.data, ios::binary);
    // On lance le thread d'upload
    pthread_create(&idThreadUpload, NULL, threadUpload, &ps);
}

void  BaseController::afficherContenu()
{
  Message m;
  m.option=LS;
  m.ctrl=EXIST;

  send(ps.descr,&m,TAILLE_INITIALISATION, 0);
}

/*
void BaseController::viderTampon(char *buffer, int size)
{
    bzero(buffer, size);
}
*/
void BaseController::deconnection()
{
    Message m;

    m.option = QUIT;
	cout << "envoi" << endl;
    send(ps.descr, &m, TAILLE_MESSAGE_MAX, 0);
}


int BaseController::attenteFinThreads()
{
  int res = pthread_join(idThreadUpload, NULL);
  int res2 = pthread_join(idThreadLire, NULL);
  return 1;
}

void BaseController::help()
{
    cout << "aff : Affiche le contenu du repertoire." << endl
        << "get <nom du fichier> : Recupere le fichier." << endl
        << "put <nom du fichier> : Envoie le fichier." << endl
        << "e | exit | E | Exit | Q | q : Ferme la connection et ferme le programme." << endl;
}
