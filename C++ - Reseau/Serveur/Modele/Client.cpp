#include "Client.h"

Client::Client()
{
    this->id = -1;
    this->fichierEnDl = NULL;
    this->supprimer = false;
    this->connecteGet = false;
    this->bind = NULL;
}

Client::Client(int sock)
{
    this->sockClient = sock;
    this->fichierEnDl = NULL;
    this->supprimer = false;
    this->connecteGet = false;
    this->bind = NULL;
}

int                 Client::getId()
{
    return this->id;
}

void                Client::setSockClient(int sock)
{
    this->sockClient = sock;
}

int                 Client::getSockClient()
{
    return this->sockClient;
}

void                Client::setIdentSockClient(struct sockaddr_in ident)
{
    this->identSockClient = ident;
}

struct sockaddr_in  Client::getIdentSockClient()
{
    return this->identSockClient;
}

void                Client::setTailleClient(socklen_t tt)
{
    this->tailleClient = tt;
}

socklen_t  Client::getTailleClient()
{
    return this->tailleClient;
}

int                 Client::telecharge()
{
    return this->dl;
}

void                Client::setTelecharge(int d)
{
    this->dl = d;
}
void                Client::setFichierEnTelechargement(Fichier *file)
{
    this->fichierEnDl = file;
}

AbstractElement     *Client::getFichierEnTelechargement()
{
   return this->fichierEnDl;
}

void                Client::supprimerClient()
{
    this->supprimer = true;
}

bool                Client::isSupprimerClient()
{
    return this->supprimer;
}

void                Client::removeFichierEnTelechargement()
{
    delete this->fichierEnDl;

    this->fichierEnDl = NULL;
}

void                Client::setSockGet(int s)
{
    this->sockGet = s;
}

int                 Client::getSockGet()
{
    return this->sockGet;
}


void                Client::setConnecteGet(bool s)
{
    this->connecteGet = s;
}

bool                Client::isConnect()
{
    return this->connecteGet;
}

Client::~Client()
{
    if (this->fichierEnDl != NULL)
        this->removeFichierEnTelechargement();
}


