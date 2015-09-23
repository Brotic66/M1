#ifndef CLIENT
#define CLIENT

/*!
 * \file Client.h
 * \class Client
 * \brief Classe Client de notre modèle
 * \author Brice VICO
 * \date 05/12/2014
 */


#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include "sock.h"
#include "sockdist.h"
#include "Fichier.h"

class   Client
{
    private :

        int                 id;                 /*!< Identifiant du client */
        int                 sockClient;         /*!< Socket attribué au client */
        struct sockaddr_in  identSockClient;    /*!< Structure identifiant le client */
        socklen_t           tailleClient;      /*!< Taille de la structure */
        int                 dl;                 /*!< 0 : pas de DL en cour, 1 : dl en cour, -1 : attend une réponse erreur (pas de fichier).)*/
        Fichier             *fichierEnDl;        /*!< fichier en cour de téléchargement, si dl = 1; */
        bool                supprimer;          /*!< Booléan permettant de savoir si le client doit être supprimer des listes du serveur (si il est déconnecté) */
        int                 sockGet;
        bool                connecteGet;


    public :

        Sock *bind;

        Client();
        Client(int);

        int                 getId();

        void                setSockClient(int);
        int                 getSockClient();

        void                setSockGet(int);
        int                 getSockGet();

        void                setConnecteGet(bool);
        bool                isConnect();

        void                setIdentSockClient(struct sockaddr_in);
        struct sockaddr_in  getIdentSockClient();

        void                setTailleClient(socklen_t);
        socklen_t           getTailleClient();

        void                setTelecharge(int);
        int                 telecharge();

        void                setFichierEnTelechargement(Fichier*);
        AbstractElement     *getFichierEnTelechargement();
        void                removeFichierEnTelechargement();

        bool                isSupprimerClient();
        void                supprimerClient();

        ~Client();
};

#endif
