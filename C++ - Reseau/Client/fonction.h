
#ifndef FONCTION
#define FONCTION

// Affiche la liste des commandes
void    help();

// fonction assurant la reception des fichiers
void    reception(Sock*, string);

// fonction assurant l'affichage du contenu du dossier sur le serveur.
void    afficherContenu(Sock*);

void    viderTampon(char*, int);

//fonction envoyant l'information de deconnection au serveur.
void    deco(Sock*);

#endif
