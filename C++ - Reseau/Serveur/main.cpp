#include "Controleur/BaseController.h"
#include "Controleur/ThreadDownController.h"
#include "Controleur/ThreadUpController.h"
#include "fonction.h"
#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>


using namespace std;

void    *mainGet(void *par)
{
    Client *c = (Client*) par;

    int                     sockClient;
    struct sockaddr_in      client;
    socklen_t       tailleClient = sizeof client;

    if (c->bind  == NULL)
        c->bind = new Sock(SOCK_STREAM, 4420 + c->getSockClient(), 0);

    if (listen(c->bind->getsDesc(), 1) < 0)
        perror("");
    else
    {
        if (sockClient = accept(c->bind->getsDesc(), (struct sockaddr*)&client, &tailleClient))
        {
            c->setSockGet(sockClient);
            c->setConnecteGet(true);
        }
    }

    return NULL;
}

void    *mainPut(void *par)
{
    struct put *s = (struct put*) par;
    bool terminer = false;
    char buffer[512];
    struct timeval  tt;

    cout << "on ouvre le fichier" << endl;
    ofstream    *fichierEnUp = new ofstream();
    fichierEnUp->open(s->data, ios::out | ios::binary | ios::trunc);

    while (!terminer)
    {
        int nbr = 0;
        int ret = 0;
        fd_set readfs;
        tt.tv_sec = 5;
        tt.tv_usec = 0;

        FD_ZERO(&readfs);
        FD_SET(s->sock, &readfs);

        ret = select(s->sock + 1, &readfs, NULL, NULL, &tt);

        if (ret <= 0)
        {
            delete fichierEnUp;
            terminer = true;
        }
        else if(FD_ISSET(s->sock, &readfs))
        {
            nbr = recv(s->sock, buffer, 512, 0);
            fichierEnUp->write(buffer, nbr);
        }

    }

    cout << "on à fini" << endl;
    return NULL;
}

void    *mainThreadDown(void *par)
{
    ThreadDownController *threadController = (ThreadDownController*) par;

    threadController->traitement();


    return NULL;
}

void    *mainThreadUp(void *par)
{
    ThreadUpController *threadController = (ThreadUpController*) par;

    threadController->traitement();

    return NULL;
}

int     main(int argc, char **argv)
{
    BaseController *gestion = new BaseController();

    gestion->ecouter();

    delete gestion;

    return 0;
}
