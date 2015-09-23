#ifndef BASECONTROLLER
#define BASECONTROLLER

/*!
 * \file BaseController.h
 * \class BaseController
 * \brief Classe controleur principale de notre application
 * \author Brice VICO
 * \date 12/12/2014
 */

#include <vector>
#include <pthread.h>
#include "../Modele/Client.h"
#include "../Modele/MyThread.h"

using namespace std;

class BaseController
{
    private :

        pthread_mutex_t verrou = PTHREAD_MUTEX_INITIALIZER;
        vector<MyThread*>    tabThread;

    public :

        /*!
         * \brief ecouter()
         *
         * Fonction principale permettant de gérer l'ensemble du serveur, créer les threads, supprimer les clients, etc..
         */
        void                ecouter();

        /*!
         * \brief CreerThreadUp
         *
         * Fonction permettant de créer un Thread d'écoute pour un client.
         *
         * \param Client *c : un pointeur sur client.
         * \return l'identifiant du thread.
         */
        pthread_t           creerThreadUp(Client*);

        /*!
         * \brief CreerThreadDown
         *
         * Fonction permettant de créer un Thread d'envoi pour 4 clients maximum ansi qu'un objet MyThread.
         *
         * \param Client *c : un pointeur sur client.
         * \return l'identifiant du thread.
         */
        pthread_t           creerThreadDown();

        vector<MyThread*>   getTabThread();
};

#endif
