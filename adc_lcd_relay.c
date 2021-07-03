#include<LPC17xx.h>
#define RS 0x01;
#define RW 0x02;
#define En 0x04;
void delay(unsigned long int x);
void lcdwrt(unsigned char y);
int main()
{
    unsigned char cmd[] = {0x38,0x0E,0x06,0x01,0x80};
    char msg[] = "Realy is";
    char msg1[] = "ON";
    char msg2[] = "OFF";
    unsigned int i,result;
    SystemInit();
    //ADC Initialisation
		LPC_SC->PCONP |= 0x00001000;
    LPC_PINCON->PINSEL3= 0xC0000000;
		LPC_ADC->ADCR = 0x00210320;
		
    //Relay Initialisation
		LPC_GPIO0->FIOMASK2 = 0xBF;
    LPC_GPIO0->FIODIR2 = 0x40;
		
		//LCD Initialisation
    LPC_GPIO2->FIOMASK0 = 0x00;
    LPC_GPIO2->FIODIR0 = 0xFF;
    LPC_GPIO1->FIOMASK1 = 0xF8;
    LPC_GPIO1->FIODIR1 = 0x07;
    LPC_GPIO1->FIOCLR1 = RS;
    LPC_GPIO1->FIOCLR1 = RW;
    for(i=0;i<5;++i)
    {
        lcdwrt(cmd[i]);
    }
    LPC_GPIO1->FIOSET1 = RS;
    for(i=0;msg[i]!='\0';++i)
    {
        lcdwrt(msg[i]);
    }
    while(1)
    {
        while((LPC_ADC->ADSTAT & 0x00000020) != 0x00000020){}
        result = (LPC_ADC->ADDR5 >> 4) & 0x00000fff;
        if(result > 0x000004D9)
        {
            LPC_GPIO0->FIOSET2 = 0x40;
            LPC_GPIO1->FIOCLR1 = RS;
            lcdwrt(0x89);
            LPC_GPIO1->FIOSET1 = RS;
            for(i=0;msg1[i]!='\0';++i)
                lcdwrt(msg1[i]);
        }
        else
        {
            LPC_GPIO0->FIOCLR2 = 0x40;
            LPC_GPIO1->FIOCLR1 = RS;
            lcdwrt(0x89);
            LPC_GPIO1->FIOSET1 = RS;
            for(i=0;msg2[i]!='\0';++i)
                lcdwrt(msg2[i]);
 
        }
    }
		//return 0;
}
void lcdwrt(unsigned char y)
{
    LPC_GPIO2->FIOPIN0 = y;
    LPC_GPIO1->FIOSET1 = En;
    delay(0x50000);
    LPC_GPIO1->FIOCLR1 = En;
    //delay(0x50000);
}
void delay(unsigned long int x)
{
    unsigned long int i;
    for(i=0;i<x;++i);
}