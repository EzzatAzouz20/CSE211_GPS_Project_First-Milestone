#include "stdint.h"
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
#define RED 0x02
#include <math.h>
#define PI  3.14159265358 
#define R   6371 
void SystemInit(){}
// Function to initialize port F 
void init(){
SYSCTL_RCGCGPIO_R	|= 0x20;
while ((SYSCTL_PRGPIO_R&0x20)==0){};
GPIO_PORTF_LOCK_R = 0x4C4F434B;
GPIO_PORTF_CR_R = 0x1F;
GPIO_PORTF_DIR_R = 0x0E;
GPIO_PORTF_DEN_R = 0x1F;
GPIO_PORTF_AMSEL_R = 0;
GPIO_PORTF_AFSEL_R = 0;
GPIO_PORTF_PCTL_R = 0;
GPIO_PORTF_PUR_R = 0x11;
}




//LCD Delay and Command and Data
void LCD_command(unsigned char command)
{
	GPIO_PORTA_DATA_R =0x00;
  GPIO_PORTB_DATA_R =command;
  GPIO_PORTA_DATA_R |=0x80;
  GPIO_PORTA_DATA_R =0x00;
}

//delay function in milli seconds
void delay_millisec( int time)
{
	int i,j;
  for(i=0;i<time;i++)
  for(j=0;j<3180;j++);
}

void LCD_data(unsigned char data)
{
	GPIO_PORTA_DATA_R =0x20;
  GPIO_PORTB_DATA_R =data;
  GPIO_PORTA_DATA_R |=0x80;
  GPIO_PORTA_DATA_R =0x00;
}


void LCD_init(){
SYSCTL_RCGCGPIO_R|= 0x03;//Enable port A & port B
while ((SYSCTL_PRGPIO_R&0x03)==0){};
	
	//INITIALIZATION OF PORT A
GPIO_PORTA_DIR_R |= 0xE0;//set A5,A6 & A7 pins to be output
GPIO_PORTA_DEN_R |= 0xE0;//set A5,A6 & A7 pins to be digital
GPIO_PORTA_AMSEL_R =0x00;
GPIO_PORTA_AFSEL_R =0x00;
GPIO_PORTA_PCTL_R =0x00;
GPIO_PORTA_PUR_R =0x00;
	
//INITIALIZATION OF PORT B
  GPIO_PORTB_DIR_R = 0xFF;//set all pins to be output
  GPIO_PORTB_DEN_R = 0xFF;//set all pins to be gigital
  GPIO_PORTB_AMSEL_R =0x00;
  GPIO_PORTB_AFSEL_R =0x00;
  GPIO_PORTB_PCTL_R =0x00;
  GPIO_PORTB_PUR_R =0x00;
	LCD_command(0x0F);//turn on display
	LCD_command(0x38);//2 lines (8 bits data)
	LCD_command(0x01);//ciear display
}


//Function to turn on the red led if the distance exceeds 100 meters
void Turn_Led(void){             
if((GPIO_PORTF_DATA_R&0x11)==0x10) //IF distance >100
    {
    GPIO_PORTF_DATA_R = RED;
    }

    else
    {
  GPIO_PORTF_DATA_R = 0;
    }
}







