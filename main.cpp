#include "tea5767.h"

int main(int argc, char *argv[])
{
	//
	//test pour savoir si il y'a le bon passage de paramètres
	if(argc != 2){
		printf("Erreur, mettre 1 paramètres:./programe, (votre nom) \n");
		exit(1);
	}
	Tea5767 radio;
	radio.set_freq(argv[1]);
	return(0);
}