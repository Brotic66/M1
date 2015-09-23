#include <stdio.h>
#include "BaseController.h"
#include "ThreadDownController.h"
#include "ThreadUpController.h"
#include "../fonction.h"

void            BaseController::ecouter()
{
    int                     sockClient;
    struct sockaddr_in      client;
    socklen_t               tailleClient = sizeof client;
    Sock                    *socke = new Sock(SOCK_STREAM, 3001, 0);

    pthread_t               threadUp;
    pthread_t               threadDown;

    int                     minClient = 4;
    vector<pair<int, int> > clientASupp;
    vector<int>             threadASupp;
    int                     nbClientCo = 0;
    Client                  *nClient = NULL;

    cout << "attente du premier client ..." << endl;

    if (listen(socke->getsDesc(), 16) < 0)
        perror("");
    else
    {
        while (1)
        {

            if (sockClient = accept(socke->getsDesc(), (struct sockaddr*)&client, &tailleClient))
            {
                clientASupp.clear();
                threadASupp.clear();
                nbClientCo = 0;
                minClient = 4;

                pthread_mutex_lock(&verrou);

                for (int cpt = 0; cpt < this->tabThread.size(); cpt++)
                {
                    for (int cl = 0; cl < this->tabThread[cpt]->getTabClient().size(); cl++)
                    {
                        nbClientCo++;

                        if (this->tabThread[cpt]->getTabClient()[cl]->isSupprimerClient())
                        {
                            clientASupp.push_back(make_pair(cpt, cl));
                        }
                    }
                }

                for (int j = 0; j < clientASupp.size(); j++)
                {
                    nbClientCo--;
                    this->tabThread[clientASupp[j].first]->removeClient(clientASupp[j].second);
                }

                for (int f = 0; f < this->tabThread.size(); f++)
                    if (this->tabThread[f]->getTabClient().size() == 0)
                        threadASupp.push_back(f);

                for (int k = 0; k < threadASupp.size(); k++)
                {
                    delete this->tabThread[threadASupp[k]];
                    this->tabThread.erase(this->tabThread.begin() + threadASupp[k]);
                }

            pthread_mutex_unlock(&verrou);

            cout << "nbClient co avant le dernier: " << nbClientCo << endl;

                if (nbClientCo >= 16)
                    close(sockClient);
                else
                {
                    cout << "il y a moins de 16 clients alors on accepte la connexion." << endl;

                    nClient = NULL;
                    nClient = new Client(sockClient);
                    nClient->setIdentSockClient(client);
                    nClient->setTailleClient(tailleClient);
                    nClient->setTelecharge(0);

                    cout << "socketClient :" << nClient->getSockClient() << endl;

                    int portGet = 4420 + nClient->getSockClient();
                    cout << portGet << endl;
                    send(nClient->getSockClient(), &portGet, sizeof(int), 0);

                    pthread_mutex_lock(&verrou); // Verrouillage mutex !

                    if (this->tabThread.size() < 4)
                    {
                        threadDown = creerThreadDown();
                    }
                    else
                    {
                        for (int i = 0; i < this->tabThread.size(); i++)
                        {
                            if (this->tabThread[i]->getTabClient().size() < minClient)
                            {
                                minClient = this->tabThread[i]->getTabClient().size();
                                threadDown = this->tabThread[i]->getId();
                            }
                        }
                    }

                    for (int it = 0; it < this->tabThread.size(); it++)
                    {
                        if (pthread_equal(this->tabThread[it]->getId(), threadDown) != 0)
                        {
                            this->tabThread[it]->addClient(nClient);
                        }
                    }

                    this->creerThreadUp(nClient);

                    pthread_mutex_unlock(&verrou); // Déverrouillage mutex !
                }
            }
        }
    }
}

pthread_t       BaseController::creerThreadUp(Client *c)
{
    pthread_t           idThread;

    cout << "Création du thread d'écoute" << endl;

    ThreadUpController *threadController = new ThreadUpController(&verrou, c);

    pthread_create(&idThread, NULL, mainThreadUp, threadController);

    return idThread;
}

pthread_t       BaseController::creerThreadDown()
{
    pthread_t idThread;

    cout << "Création d'un thread d'envoi et d'un objet MyThread." << endl;

    MyThread *thread = new MyThread(0);

    this->tabThread.push_back(thread);

    ThreadDownController *threadController = new ThreadDownController(&verrou, thread);
    pthread_create(&idThread, NULL, mainThreadDown, threadController);

    thread->setId(idThread);

    return idThread;
}

vector<MyThread*> BaseController::getTabThread()
{
    return this->tabThread;
}
