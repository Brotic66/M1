#ifndef MYTHREAD
#define MYTHREAD

/*!
 * \file MyThread.h
 * \class MyThread
 * \brief Classe MyThread permettant d'obtenir des renseignement sur les thread d'envois du serveur.
 * \author Brice VICO
 * \date 12/12/2014
 */


#include <vector>
#include <pthread.h>
#include <sys/types.h>
#include "Client.h"

using namespace std;

class MyThread
{
    private :

        pthread_t       id;             /*!< Identifiant du thread de type pthread_t */
        vector<Client*> tabClient;      /*!< Vector contenant des pointeur sur les Client traité par ce MyThread et donc le thread pthread_t */
        bool            supprimer;      /*!< Boolean permettant de savoir si on doit supprimer ce MyThread */

    public :

        MyThread(pthread_t);

        void            setId(pthread_t);
        pthread_t       getId();

        void            addClient(Client*);
        const vector<Client*> &getTabClient() const;

        void            removeClient(int);

        ~MyThread();
};

#endif
