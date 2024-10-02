#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>	
#define master_device "/dev/i2c-1"
//#define I2C_SLAVE "0xFE"
//smb://172.16.10.3/
//I2C_slave 0xFE
int main(int argc, char *argv[])
{
	int fd;
	//unsigned long int I2C_SLAVE = 0xFE;
	unsigned int address = 0x60;
	float freq;
	unsigned int frequencyB;
	unsigned char frequencyH; 
	unsigned char frequencyL;
	char command[5];
	//
	//test pour savoir si il y'a le bon passage de paramètres
	if(argc != 2){
		printf("Erreur, mettre 1 paramètres:./programe, (votre nom) \n");
		exit(1);
	}
	//
	//ouverture du périphérique maître
	fd=open(master_device, O_RDWR | O_NOCTTY | O_NDELAY);
	if(fd<0)

	{
		printf("L'ouverture du Peripherique Master I2C /dev/i2c a echoue\n");
		exit(0);
	}
	else
	{
		printf("L'ouverture du Peripherique Master I2C /dev/i2c a reussi\n");
		//
		//ouverture du périphérique esclave
		if(ioctl(fd, I2C_SLAVE, address)<0)
		{
			perror("IOCTL");
			printf("Impossible de communiquer avec le périphérique Esclave I2C 0x\n");
			exit(1);
		}
		else{
			printf("Communication avec le peripherique esclave I2C 0x60\n");
		}
	}

	//pour vous aider voici la commande que j'envoie pour changer la fréquence  (freq est la frequence que l'on veut ecouter) :
	//calculating PLL word
	freq = atof(argv[1]);
	frequencyB=4*(freq*1000000+225000)/32768;  
	frequencyH=frequencyB>>8;
	frequencyL=frequencyB&0XFF;
	//printf ("Frequency = %fMhz\n",freq);
	// Mise en forme de la commande
	command[0]=frequencyH; //FREQUENCY H
	command[1]=frequencyL; //FREQUENCY L mute off
	command[2]=0xB0; //3d byte (0xB0): high side LO injection is on,.
	command[3]=0x10; //4th byte (0x10) : Xtal is 32.768 kHz
	command[4]=0x00; //5th byte (0x00)
	//
	//écriture 0
	if (write(fd,command,5)== -1)
	{
		printf("Error writing to I2C slave\n");
		return -1;
	}
	else
	{
		printf("écriture réussi\n");
	}
	
	command[0]=frequencyH|0X80;
	if (write(fd,command,5)== -1)
	{
		printf("Error writing to I2C slave\n");
		return -1;
	}
	else
	{
		printf("écriture réussi\n");
	}
	sleep(5);
	command[0]=frequencyH&0X7F;
	if (write(fd,command,5)== -1)
	{
			printf("Error writing to I2C slave\n");
			return -1;
	}
	else
	{
			printf("écriture réussi\n");	
	}
	return(0);
}