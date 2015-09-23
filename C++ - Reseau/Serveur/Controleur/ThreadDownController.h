#ifndef THREADDOWNCONTROLLER
#define THREADDOWNCONTROLLER

/*!
 * \file ThreadDownController.h
 * \class ThreadDownController
 * \brief Classe controleur principale des thread de download
 * \author Brice VICO
 * \date 19/12/2014
 */

#include <vector>
#include <pthread.h>
#include "../Modele/Client.h"
#include "../Modele/MyThread.h"

using namespace std;

class ThreadDownController
{
    private :

        pthread_mutex_t     *verrou;
        MyThread            *thread;

    public :

        /*!
         * \brief Constructeur
         */
        ThreadDownController(pthread_mutex_t*, MyThread*);

        /*!
         * \brief traitement
         *
         * Fonction traitant les clients à traiter par ce thread
         */
        void        traitement();
        bool        envoyerFichier(Client*);
        void        envoyerFichierSuite(Client*);
        void        envoyerLs(Client*);
        bool        envoyerErreur(Client*, string);

        MyThread        *getThread();
        pthread_mutex_t *getVerrou();

        ~ThreadDownController();
};

#endif
