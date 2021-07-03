#include<LPC17xx.h>
unsigned char h1[],z;
void lcdwrt(unsigned char y);
void hexatoascii(unsigned int h)

{ 
  int k;
	z=4;
	
	for(k=0;k<z;k++)
	{
		h1[k] = h%0x0A;
		h = h/0X0A;
	}
	
	for(k=z;k>=0;k--)
	{
		lcdwrt(h1[k]+0x30);
	}
}	
	