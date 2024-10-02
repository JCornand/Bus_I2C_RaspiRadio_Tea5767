#include "tea5767.h"

Tea5767::Tea5767()
{
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
    //etat_son = ON;
}

void Tea5767::set_freq(char* buff)
{
	//87.5 MHz to 108 MHz
	freq = atof(buff);
	//calculating PLL word
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
	//envoie de la chaine
	if (write(fd,command,5)== -1)
	{
		printf("Error writing to I2C slave\n");
		exit (-1);
	}
	else
	{
		printf("écriture réussi\n");
	}
	
	//
	//hopla muted
	command[0]=frequencyH|0X80;
	if (write(fd,command,5)== -1)
	{
		printf("Error writing to I2C slave\n");
		exit (-1);
	}
	else
	{
		printf("écriture réussi\n");
	}
	sleep(5);
	//hopla demuted
	command[0]=frequencyH&0X7F;
	if (write(fd,command,5)== -1)
	{
			printf("Error writing to I2C slave\n");
			exit (-1);
	}
	else
	{
			printf("écriture réussi\n");	
	}
	
}

// etat_son=def_don; selon ce que le main envoie