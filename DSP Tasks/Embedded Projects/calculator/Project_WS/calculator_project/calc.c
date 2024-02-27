/*
 * calc.c
 *
 *  Created on: 5 Oct 2023
 *      Author: maria
 */



/****global arrays for storing and displaying the characters pressed by the keypad to*************
*************************** perform calculations on *********************************************/
/*************************************************************************************************
 *                         Important Includes
************************************************************************************************/
#include"keypad.h"
#include"lcd.h"
#include<util/delay.h>
#include"std_types.h"
#include<stdio.h>



/************************************************************************************************
                Important global initialization
 **********************************************************************************************/
/*variable to store in the 1st operand range from  -32768 .. +32767 which is 5 digit number*/
 sint16 operand1=0;

/*variable to store in the 2nd operand  range from  -32768 .. +32767 which is 5 digit number */
 sint16 operand2=0;

/* you can store more than 1 operator in that array */
 uint8 operator;



 /*************************************************************************************************
  *                            Important  Function Definition
  ************************************************************************************************/

 /*description : fn the perform the calculation based on the input from the user */
 void perform_calculation (sint16 *op1,uint8 *operation,sint16 * op2);
 #define SIZE_OPERAND   5
 #define SIZE_OPERATOR  3

int main ()
{

	 LCD_init();
	 LCD_displayStringRowColumn(0,3,"Welcome to");
   	 LCD_displayStringRowColumn(1 ,0, "Edges Calculator");
   	 _delay_ms(500);
   	 LCD_clearScreen();

   	/*variable to count number of digits of both operands */
	 uint8 i=0;
	 /* variable to know if the number is +ve or -Ve by storing in it the polarity */
	 sint8 sign=1;

	/*store in it the pressed key */
	 uint8 key=0;

	while(i<SIZE_OPERAND){
		/* variable to store in the pressed key ,char as we will take digit by digit
		 and unsigned as the digits are unsigned*/
		key= KEYPAD_getPressedKey(); /* take the pressed key */

		/* to store the sign of first digit the input is +/- */
		if ((i== 0)&&((key=='-')||(key=='+'))){
			if (key=='-')
				sign *=-1;
				LCD_sendCharacter(key);

				}

		/* if equal operand is pressed and there is a number stored in operand then raise
		 a flag and return to the main */
		 else if((key == '=' )&& (i>0)){
			LCD_sendCharacter('=');

			perform_calculation (&operand1,&operator,&operand2);

			}

		/* if the pressed is not a digit */
		else if((key =='%')||(key =='*')||(key=='-')||(key=='+') ){

		/* in this case the user only entered a bunch of operands without any number */
			if(i==0){
                /*do nothing*/
			}

		    else {
				operator=key;//operator is entered
				 LCD_sendCharacter(key);

				_delay_ms(500);
				break;
			    }
			}
			/* if equal operand is pressed and there is a number stored in operand then raise
			 a flag and return to the main */
		else {
			operand1 =((operand1*10)+key)*sign;
			/*if +ve then display it as integer */
			LCD_integerToString(key);

			 i++;

	   }

			 _delay_ms(500);
	}

   	 while(1){
label:
   		 /*initialize them from the begaining */
   		i=0;
   		key=0;
   		sign=1;

   		if(operator==0){
   			while(1){
   				if(((key=='+')||(key=='-')||(key=='%')||(key=='*'))){
   					operator=key;
   					LCD_sendCharacter(key);
   					_delay_ms(500);
   					break;
   				}
   				else {
   					key=KEYPAD_getPressedKey();
   				}
   				}

   			 }

   		while(i<SIZE_OPERAND){
   			key=KEYPAD_getPressedKey();
   			 /* to store the sign of first digit the input is +/- */
   			 if ((i== 0)&&((key=='-')||(key=='+'))){
   				if (key=='-')
   					sign *=-1;
   				LCD_sendCharacter(key);
   			}

   			/* if equal operand is pressed and there is a number stored in operand then raise
   			a flag and return to the main */
   			else if((key == '=' )&& (i>0)){
   				LCD_sendCharacter('=');

   				perform_calculation (&operand1,&operator,&operand2);
   				goto label;
   			 }
   			else if((key =='%')||(key =='*')||(key=='-')||(key=='+') ){
   			/* in this case the user only entered a bunch of operands without any number */
   			 if(i==0){
   				/*do nothing*/
   			}

   			 else {

   				perform_calculation (&operand1,&operator,&operand2);
   				operator=key;
   				goto label;

   				}
   			}
   			else {
   				operand2 =((operand2*10)+key)*sign;
   				 /*if +ve then display it as integer */
   				LCD_integerToString(key);

   				i++;

   			}

   			   _delay_ms(500);

   			}



   		 _delay_ms(500);/*delay for processing */

   		 LCD_sendCharacter('=');

   		 perform_calculation (&operand1,&operator,&operand2);

   	}
}


 /*description : fn the perform the calculation based on the input from the user */
 void  perform_calculation (sint16 * op1,uint8 *operation,sint16 *op2){
	 sint16 result=0;


	 switch(*operation){
	 case '%':
	 	 result= (*op1)/ (*op2);
	 	 break;
	 case '*':
 	 	 result= (*op1)*(*op2);
	 	 break;
	 case '+':
		 result =(*op1)+(*op2);
		 break;
	 case '-':
		  result=(*op1)-(*op2);
		  break;
	 default:
		 result=*op1;
		 break;
	 }
	 LCD_clearScreen();
	 if(result<0){
		 LCD_sendCharacter('-');
		 LCD_integerToString(-result);
	 }
	 else {

		 LCD_integerToString(result);
	 }

	 *op1=result;
	 *op2=0;
	 *operation=0;


	 _delay_ms(250);

 }

