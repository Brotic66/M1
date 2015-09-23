#include <string.h>
#include <dirent.h>
#include "ThreadUpController.h"
#include "../fonction.h"

Sock *socke = NULL;

ThreadUpController::ThreadUpController(pthread_mutex_t *v, Client *c)
{
    this->verrou = v;
    this->client = c;
    this->fichierEnUp = NULL;
}

Client              *ThreadUpController::getClient()
{
    return this->client;
}

pthread_mutex_t     *ThreadUpController::getVerrou()
{
    return this->verrou;
}

void                ThreadUpController::traitement()
{
    Message m;
    while (!this->client->isSupprimerClient())
    {
       recv(this->client->getSockClient(), &m, 516, 0);

       cout << "option :" << m.option << endl;

           pthread_mutex_lock(this->verrou);

            if (m.option == 'g')
                this->traiterGet(m);
            else if (m.option == 'p')
                this->traiterPut(m);
            else if (m.option == 'l')
                this->traiterLs();
            else if (m.option == 'q')
                this->traiterDeco();

            pthread_mutex_unlock(this->verrou);
    }
}

void            ThreadUpController::traiterGet(Message m)
{
    ifstream    *fichier =  new ifstream();

    fichier->open(m.data, ios::binary);

        this->client->setTelecharge(1);

        Fichier     *oFichier = new Fichier();

        oFichier->setNom(string(m.data));
        oFichier->setFichier(fichier);

        this->client->setFichierEnTelechargement(oFichier);
}

void            ThreadUpController::traiterPut(Message m)
{
    int                     sockClient;
    struct sockaddr_in      client;
    socklen_t               tailleClient = sizeof client;
    if (socke == NULL)
        socke = new Sock(SOCK_STREAM, 4411, 0);

    if (listen(socke->getsDesc(), 1) < 0)
        perror("");
    else
    {
        if (sockClient = accept(socke->getsDesc(), (struct sockaddr*)&client, &tailleClient))
        {
            pthread_t idThread;

cout << "coucou mon fils0" << endl;
            struct put *p = new struct put;
            p->sock = sockClient;

            for (int i = 0; i < 512; i++)
                p->data[i] = m.data[i];

            pthread_create(&idThread, NULL, mainPut,p);
        }
    }
}

void            ThreadUpController::traiterLs()
{
    cout << "envoyer LS" << endl;
    DIR             *repertoire = opendir(".");
    struct dirent   *dir = NULL;
    Message m;

    while ((dir = readdir(repertoire)) != NULL)
    {
        m.option = 'l';
        m.ctrl = 'e';
        m.taille = 256;

        for (int i = 0; i < 256; i++)
            m.data[i] = dir->d_name[i];

        send(this->client->getSockClient(), &m, 516, 0);
    }

    m.option = 'l';
    m.ctrl = 'f';
    m.taille = 0;

    if (send(this->client->getSockClient(), &m, 516, 0)  == -1)
        cout << "erreur2" << endl;

    cout << "fin" << endl;
}

void            ThreadUpController::traiterDeco()
{
    Message m = {'q', 'e', 0};
    if (send(this->client->getSockClient(), &m, 516, 0) == -1)
        cout << "ça buggg !!" << endl;
    this->client->supprimerClient();
    this->client->setTelecharge(0);
    cout << "déconexion du client." << endl;
}
