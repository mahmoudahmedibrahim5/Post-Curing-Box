/*
 * GPIO.c
 *
 * Created: 10/26/2021 3:29:20 PM
 *  Author: ADMIN
 */ 
#include <avr/io.h>

void Init (char port,char pin,char mode)
{
	if (mode==0)
	{
		if (port=='B' || port== 'b')
		{
			DDRB &= ~(1<<pin);
			PORTB |=(1<<pin);
		}
		else if (port=='C' || port== 'c')
		{
			DDRC &= ~(1<<pin);
			PORTC |=(1<<pin);
		}
		else if (port=='D' || port== 'd')
		{
			DDRD &= ~(1<<pin);
			PORTD |=(1<<pin);
		}
	}
	else if(mode==1)
	{
		if (port=='B' || port== 'b')
		{
			DDRB |= (1<<pin);
		}
		else if (port=='C' || port== 'c')
		{
			DDRC |= (1<<pin);
		}
		else if (port=='D' || port== 'd')
		{
			DDRD |= (1<<pin);
		}
	}
}
void Output (char port,char pin,char val)
{
	if (val==0)
	{
		if (port=='B' || port== 'b')
		{
			PORTB &= ~(1<<pin);
		}
		else if(port=='C' || port== 'c')
		{
			PORTC &= ~(1<<pin);
		}
		else if (port=='D' || port== 'd')
		{
			PORTD &= ~(1<<pin);
		}
	}
	else if(val==1)
	{
		if (port=='B' || port== 'b')
		{
			PORTB |= (1<<pin);
		}
		else if(port=='C' || port== 'c')
		{
			PORTC |= (1<<pin);
		}
		else if (port=='D' || port== 'd')
		{
			PORTD |= (1<<pin);
		}
	}
	
}
char Input (char port,char pin)
{
	char tmp;
	if (port=='B' || port== 'b')
	{
		tmp=(PINB & (1<<pin))>>pin;
	}
	else if(port=='C' || port== 'c')
	{
		tmp=(PINC & (1<<pin))>>pin;
	}
	else if (port=='D' || port== 'd')
	{
		tmp=(PIND & (1<<pin))>>pin;
	}
	return tmp;
}