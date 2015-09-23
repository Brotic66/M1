#include <string.h>
#include <dirent.h>
#include "ThreadDownController.h"
#include "../fonction.h"

int cpt = 0;

ThreadDownController::ThreadDownController(pthread_mutex_t *v, MyThread *t)
{
    this->verrou = v;
    this->thread = t;
}

MyThread    *ThreadDownController::getThread()
{
    return this->thread;
}

pthread_mutex_t    *ThreadDownController::getVerrou()
{
    return this->verrou;
}

void                ThreadDownController::traitement()
{
    bool terminer = false;
    while (!terminer)
    {
        pthread_mutex_lock(this->verrou);

        if (this->thread->getTabClient().size() == 0)
            terminer = true;
        else
        {
            for (int i = 0; i < this->thread->getTabClient().size(); i++)
            {
                if ((this->thread->getTabClient()[i]->telecharge() == 1) && !this->thread->getTabClient()[i]->isSupprimerClient() && this->thread->getTabClient()[i]->isConnect() == false)
                {
                    this->envoyerFichier(this->thread->getTabClient()[i]);
                }
                else if ((this->thread->getTabClient()[i]->telecharge() == 2) && !this->thread->getTabClient()[i]->isSupprimerClient())
                        this->envoyerLs(this->thread->getTabClient()[i]);
               else if (!this->thread->getTabClient()[i]->isSupprimerClient() && this->thread->getTabClient()[i]->isConnect() == true)
                    envoyerFichierSuite(this->thread->getTabClient()[i]);
            }
        }

        pthread_mutex_unlock(this->verrou);
    }
}

void                ThreadDownController::envoyerLs(Client *c)
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

        send(c->getSockClient(), &m, 516, 0);
    }

    m.option = 'l';
    m.ctrl = 'f';
    m.taille = 0;

    if (send(c->getSockClient(), &m, 516, 0)  == -1)
        cout << "erreur2" << endl;

    c->setTelecharge(0);
    cout << "fin" << endl;
}

void                ThreadDownController::envoyerFichierSuite(Client *c)
{
    ifstream *fichier= c->getFichierEnTelechargement()->getFichier();
    char buffer[512];

    if (c->telecharge() == 3)
    {
        cout << "démarage transfert" << endl;
        char octet = '1';
        send(c->getSockGet(), &octet, 1, 0);
        c->setTelecharge(0);
        sleep(2);
        return;
    }

    if (fichier->fail())
    {
        char octet = '0';
        send(c->getSockGet(), &octet, 1, 0);
        c->setTelecharge(0);
        c->setConnecteGet(false);
        return;
    }

/*    if (fichier->eof())
    {
        cout << "Fin du transfert" << endl;
        c->removeFichierEnTelechargement();
        c->setConnecteGet(false);
    }
    else
    {*/
        fichier->read(buffer, 512);
        int count = fichier->gcount();
        if (count < 512)
        {
        cout << "Fin du transfert" << endl;
        c->removeFichierEnTelechargement();
        c->setConnecteGet(false);
        }
            send(c->getSockGet(), &buffer, count, 0);
    //}
}

bool                ThreadDownController::envoyerFichier(Client* c)
{
    Message     m = {'g', 'e', 0};

    if (c == NULL || c->getFichierEnTelechargement() == NULL || c->getFichierEnTelechargement()->getFichier() == NULL)
    {
        return false;
    }

    send(c->getSockClient(), &m, 516, 0);

    pthread_t idThreadGet;

    pthread_create(&idThreadGet, NULL, mainGet, c);

    c->setTelecharge(3);


 /*   if (c->telecharge() == 1)
        c->setTelecharge(3);
    else
        m.ctrl = 'c';

    if (!c->getFichierEnTelechargement()->getFichier()->eof())
    {
        fichier->read(buffer, 512);
        if (fichier->gcount() < 512)
            m.ctrl = 'f';

        for (int i = 0; i < 512; i++)
            m.data[i] = buffer[i];

        m.taille = fichier->gcount();

        if (send(c->getSockClient(), &m, 516, 0) != -1)
        {
            cpt++;

            if (m.ctrl == 'f')
            {
                cout << "on a fini !" << endl;
                c->setTelecharge(0);
                c->removeFichierEnTelechargement();
            }

            return true;
        }
        else
        {
            c->setTelecharge(0);
            c->removeFichierEnTelechargement();

            return false;
        }
    }
    else
    {
        cout << "c'est la fin !" << endl;
        m.ctrl = 'f';
        m.taille = 0;

        if (send(c->getSockClient(), &m, 516, 0) != -1)
            return true;
        else
            return false;
    }
*/

}

bool                ThreadDownController::envoyerErreur(Client *c, string s)
{
    Message m = {'g', 'n', 0};

    send(c->getSockClient(), &m, 516, 0);

    c->setTelecharge(0);
}

ThreadDownController::~ThreadDownController()
{

}
