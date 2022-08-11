/*
 * Final Task.c
 *
 * Created: 10/26/2021 3:27:15 PM
 * Author : Mahmoud Ahmed Ibrahim
 * Post-curing box
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 4000000
#include <util/delay.h>
#include "GPIO.h"

#define Red 0
#define Green 1
#define Blue 2
#define UVLeds 5

char debounce(char last);
void OneStep (char mode);

int cntr=0;
int cntr_2=0;

int main(void)
{
	Init('D',2,In); //Set PD2 as input (Front Push Button)  //Active Low
	Init('D',3,In); //Set PD3 as input (protection button)  //Active Low
	
	Init('C',Red,Out); //Set PC0 as output (RedLed)
	Init('C',Green,Out); //Set PC1 as output (GreenLed)
	Init('C',Blue,Out); //Set PC2 as output (BlueLed)
	Init('C',UVLeds,Out); //Set PC5 as output (UVLeds)
	
	Init('D',4,Out);  //PD4,PD5,PD6,PD7 are outputs (stepper motor pins)
	Init('D',5,Out);
	Init('D',6,Out);
	Init('D',7,Out); 
	
	Output('D',4,LOW);
	Output('D',5,LOW);
	Output('D',6,LOW);
	Output('D',7,LOW);
	
	char protection=0; //state of the protection button
	char last=1;    // last state for the Front Push button
	char current=1; //current state of the Front Push button
	char state=0;   // state of the device
	
	TIMSK |=(1<<0); //Enable interrupt
	sei();
	
	while (1)
	{
	 current=debounce(last);
	 if (current==0 && last==1) // if the button pressed
	 {
		 state=state^(0x01);    //invert device state
		 if (state==1)
		 {
			 TCNT0=254;      //set intial value of Timer0 as 254
			 TCCR0 &=~(0x07);
			 TCCR0 |=(0x05);  //set prescaler /1024
		 }
	}  
	 last=current;
	 
	 protection=Input('D',3);
	 
	 if (cntr_2==5000)      //if 10 seconds passed
	 {
		 state=0;          // turn off UVLeds,RGB,Steppermotor
		 TCCR0 &=~(0x07);  //turn off the timer
		 cntr_2=0;    
	 }
	 
	 if (state==0)          //if device state is off
	 {
		 Output('c',Red,LOW);  //turn off everything
		 Output('c',Green,LOW);
		 Output('c',Blue,LOW);
		 Output('c',UVLeds,LOW);
		 OneStep(LOW);
	 } 
	 else if(state==1)    //if device state is on
	 {//check protection button
		 if (protection==0)   //if button is pressed  
		 {
			 Output('c',Red,LOW);
			 Output('c',Blue,HIGH);  //Make RGB blue
			 Output('c',UVLeds,HIGH);  //Turn on UVLeds
			 OneStep(HIGH);       //Turn on the stepper motor
		 }  
		 else if(protection==1)  //if button is unpressed
		 {
			 Output('c',Red,HIGH);  //Make RGB Red
			 Output('c',Blue,LOW);
			 Output('c',UVLeds,LOW);  //Turn off UVLeds
			 OneStep(LOW);       //Turn off the stepper motor
		 }
	 }
	
	}
}

ISR(TIMER0_OVF_vect)
{
	cntr++;
	if (Input('D',3)==0)
	{
		cntr_2++;
	}
	TCNT0=254;  //set intial value of Timer0 as 254
}
char debounce(char last)
{
	char read =Input('D',2);
	if (read!=last)
	{
		_delay_ms(5);
		read=Input('D',2);
	}
	return read;
}
void OneStep (char mode)
{
	if (mode==1)
	{
		if (cntr>3)
		{
			cntr=0;
		}
		switch(cntr)
		{
			case 0:
			Output('D',7,LOW);
			Output('D',4,HIGH);
			break;
			case 1:
			Output('D',4,LOW);
			Output('D',5,HIGH);
			break;
			case 2:
			Output('D',5,LOW);
			Output('D',6,HIGH);
			break;
			case 3:
			Output('D',6,LOW);
			Output('D',7,HIGH);
			break;
		}
	}
			
}