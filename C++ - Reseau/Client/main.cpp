#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include "sock.h"
#include "sockdist.h"

#include "BaseController.h"

using namespace std;

int     main(int argc, char **argv)
{
  cout << "Debut client" << endl;
  //char adresse[100];
  BaseController bc;
  char adresse[100];
  int port = 3001;
  if(argc>3)
  {
	cout << "trop d'arguments" << endl;
	return -1;
  }
  
  if(argc>1)
  {
	strcpy(adresse, argv[1]);
	if(argc>2)
	  port = atoi(argv[2]);
  }
  else
  {
	strcpy(adresse, "127.0.0.1");
  }

 cout << "Connection a " << adresse << " sur le port " << port << endl;
  if(bc.connection(adresse, port)==-1)
  	return -1;
  bc.attenteCommande();
  bc.attenteFinThreads();
    return 0;
}
