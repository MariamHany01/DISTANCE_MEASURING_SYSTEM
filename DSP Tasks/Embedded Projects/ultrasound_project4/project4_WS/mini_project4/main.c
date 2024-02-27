/*
 * main.c
 *
 *  Created on: 18 Oct 2023
 *      Author: maria
 */
#include "lcd.h"
#include "us.h"
#include "icu.h"
#include <util/delay.h>
#include<avr/io.h>


int main (){

	LCD_init();
	Ultrasonic_init();
	uint16 distance =0;
	SREG|=(1<<7);
	LCD_displayString("Distance=   cm");
	while (1){
		LCD_moveCursor(0,9);
		distance =Ultrasonic_readDistance();
		if (distance>=100)
			LCD_intgerToString(distance);
		else {
			LCD_intgerToString(distance);
			LCD_displayCharacter(' ');
		}

	}
	return 0;

}

