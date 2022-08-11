/*
 * GPIO.h
 *
 * Created: 10/26/2021 3:28:43 PM
 *  Author: ADMIN
 */ 

#ifndef GPIO_H_
#define GPIO_H_

#define HIGH 1
#define LOW 0

#define In 0
#define Out 1

void Init (char port,char pin,char mode);
void Output (char port,char pin,char val);
char Input (char port,char pin);

#endif /* GPIO_H_ */