#ifndef THREADUPCONTROLLER
#define THREADUPCONTROLLER

/*!
 * \file ThreadUpController.h
 * \class ThreadUpController
 * \brief Classe controleur principale des thread de reception pour une boite réseau
 * \author Brice VICO
 * \date 19/12/2014
 */

#include <vector>
#include <pthread.h>
#include <fstream>
#include "../Modele/Client.h"
#include "../fonction.h"

using namespace std;

class ThreadUpController
{
    private :

        pthread_mutex_t     *verrou;
        Client              *client;
        ofstream            *fichierEnUp;

    public :

        /*!
         * \brief Constructeur
         */
        ThreadUpController(pthread_mutex_t*, Client*);

        /*!
         * \brief traitement
         *
         * Fonction traitant le client à traiter par ce thread
         */
        void        traitement();

        /*!
         * \brief traitementGet
         *
         * Fonction traitant une reception d'un get
         *
         * \param Message m : la structure reçu
         */
        void        traiterGet(Message);

        /*!
         * \brief traitementPut
         *
         * Fonction traitant une reception d'un put et donc d'un upload de fichier sur le serveur.
         *
         * \param Message m : la structure reçu
         */
        void        traiterPut(Message);

        /*!
         * \brief traitementLs
         *
         * Fonction traitant une reception d'un ls pour avoir la liste des fichiers présent sur le serveur.
         */
        void        traiterLs();

        /*!
         * \brief traitementDeco
         *
         * Fonction traitant une reception d'une demande de déconnexion
         */
        void        traiterDeco();

        Client          *getClient();
        pthread_mutex_t *getVerrou();

        ~ThreadUpController();
};

#endif
