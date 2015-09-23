#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string>
#include <string.h>
#include "sock.h"
#include "sockdist.h"
#include "fonction.h"

using namespace std;


void    help()
{
    cout << "aff : Affiche le contenu du repertoire." << endl;
    cout << "get [chemin+nom du fichier | nom du fichier] : Recupere un fichier." << endl;
    cout << "e | exit | E | Exit : Ferme la connection et ferme le programme." << endl;
}

void    reception(Sock *socke, string param)
{
    int         test = 1;
    char        msg[1] = "";
    char        buffer[1024] = "";
    char        verif[1] = "";
    char        *octet = new char[2];
    string      cheminEtName;
    ofstream    file;

    msg[0] = 's';

    send(socke->getsDesc(), msg, 1, 0);
    strcpy(buffer, param.c_str());
    send(socke->getsDesc(), buffer, 1024, 0);
    recv(socke->getsDesc(), verif, 1, 0);

    if (verif[0] == '0')
        cout << "fichier introuvable sur le serveur" << endl;
    else
    {
        cout << "reception du fichier en cours..." << endl;

        cheminEtName = "files/" + param;

        file.open(cheminEtName.c_str(), ios::out | ios::trunc | ios::binary);
        while (test)
        {
            if (octet[1] != '1')
            {
                recv(socke->getsDesc(), octet, 2, 0);
                file << octet[0];
            }
            else
                test = 0;
        }

        cout << "fichier recu." << endl;

        file.close();
    }
    viderTampon(buffer, 1024);
}

void    afficherContenu(Sock *socke)
{
    char    msg[1] = "";
    char    verif[1]= "";
    char    buffer[256] = "";
    int     cpt = 1;
    string  repe;

    msg[0] = 'l';
    send(socke->getsDesc(), msg, 1, 0);
    recv(socke->getsDesc(), verif, 1, 0);

    if (verif[0] == '0')
    {
        cout << "Repertoire inexistant !" << endl;
    }
    else
    {
        while (cpt)
        {
            recv(socke->getsDesc(), buffer, 256, 0);
            repe = buffer;
            if (repe == "EOD")
                cpt = 0;
            else
                cout << repe << endl;

            repe.erase(repe.begin(), repe.end());
            viderTampon(buffer, 256);
        }
    }
    repe.erase(repe.begin(), repe.end());
    viderTampon(buffer, 256);
}

void    viderTampon(char *buffer, int size)
{
    bzero(buffer, size);
}

void    deco(Sock *socke)
{
    char *msg = new char[1];

    msg[0] = 'q';
    send(socke->getsDesc(), msg, 1, 0);
}
