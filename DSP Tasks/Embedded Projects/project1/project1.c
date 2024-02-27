/*
 * project1.c
 *
 *  Created on: 13 Aug 2023
 *      Author: Mariam Hany Nabil Bestawrous
 */
#include<stdio.h>


typedef enum state//enum to store the state of engine and AC
	{   OFF,
	    ON
	}state;
char STATE[2][4]={"OFF","ON"};//array to display value of enum

typedef struct vehicle //struct that contain vehicle's data
    {  state engine_state;
    	state AC_state;
		int vehicle_speed;//int as the float point will not affect the process of the program
		float room_temp;
		state engine_temp_controller;
		float engine_temp;
	} vehicle;

vehicle	v1={OFF,OFF,100,27,OFF,90};//initializing the members of vehicle v1

void main_window(void);//main window of the vehicle system
void sensor_set_menu(void);//set menu should always be displayed while running the program
void display(void);//displaying the vehicle data
void set_traffic_color(void);//readding traffic light color to change the speed of vehicle
void set_room_temp(void);//reading the room temp to change state of AC
void set_engine_temp(void);//reading the  engine temp to change state of engine temp controller
void check_speed(void);//fn to adjust some members of the vehicle based on speed value


int main(){
	printf("Welcome to VEHICLE CONTROL SYSTEM! \n \n");
	fflush(stdout);
	main_window();

	return 0;

}
void main_window(void){
	char choice ;//variable to store in the choice from the user

	//display the options
	printf("a-Turn on the vehicle engine \nb-Turn off the "
			"vehicle engine \nc-Quit the system \n\n");
	fflush(stdout);
	scanf(" %c",&choice);//input the option from the user

	switch (choice) {

			case 'A':
	        case 'a'://if the user chose turn on he will go to set menu
	            sensor_set_menu();
	            break;

	        case 'B':
	        case 'b'://if the user chose turn off he will go back to main window
	            printf("Turn off the vehicle system \n \n");
	            fflush(stdout);
	            main_window();
	            break;

	        case 'C':
	        case 'c':
	        	printf("Quit the system!\n");//if the user choose quit the program will return
	        	fflush(stdout);
	            return;

	        default://for unsupported choices :
	            printf("Unsupported choice. Please choose 'a', 'b', OR 'c'. \n\n");//display an alert
	            fflush(stdout);
	            main_window();//back to main window
	            break;
	    }

	}
void sensor_set_menu(void){
	char choice; //variable to store in the choice of the user


	//display the options
	printf("a-Turn off the engine \nb-Set the traffic color\n"
			"c-Set the room temperature(temperature sensor)\n"
			"d-Set the engine temperature(engine temperature) \n\n");
	fflush(stdout);
	scanf(" %c",&choice);//input the option from the user

	switch(choice){

	case 'A'://a->turn off the engine
	case 'a':
		printf("Turn off the engine \n \n");//display the choice
	    fflush(stdout);
	    main_window();//back to the main window
	    break;

	case 'B'://b->set traffic light(change speed)
	case 'b':
		set_traffic_color();
		break;

	case 'C'://c->set room temp(change the state of AC and value of room temp
	case 'c':
		set_room_temp();
		break;

	case 'D'://d->set engine temp(change the engine temp controller state and engine temp)
	case 'd':
		set_engine_temp();
		break;

	default:
		break;
	}

}

void set_traffic_color(void){
	v1.engine_state=1;//activating the engine

	char choice ;//variable to store in the choice of the user

	printf("enter the traffic color (R:Red , O:Orange , G:Green) \n");
	fflush(stdout);
	scanf(" %c",&choice);

	switch(choice){

	case 'G':
	case 'g':
		v1.vehicle_speed=100;//green means vehicle moving with 100 km/hr speed
		break;

	case 'O':
	case 'o':
		v1.vehicle_speed=30;//orange means the vehicle is moving with 30 km/hr speed
		break;

	case 'R':
	case 'r':
		v1.vehicle_speed=0;//read means the veaicle is at rest
		break;

	default: //Unsupported colors
		printf("unsupported color \n\n");//display alert
		fflush(stdout);
		set_traffic_color();//back to set traffic color
		break;
	}
	display();//display the state of the vehicle
}
void set_room_temp(void){
	v1.engine_state=ON;//activating the engine

	float temp=0;//variable that will store and read in the temperature of room

	printf("Enter the temperature of the room in degree celsius\n");
	fflush(stdout);
	scanf(" %f",&temp);//read temperature

	if(temp<10||temp>30){
	v1.AC_state=ON;//turning on the AC
	v1.room_temp=20;//setting room temp to 20 degrees
	}
	else {
		v1.AC_state=OFF;//turning off the AC
		v1.room_temp=temp;//room temp = the value read by the sensor
	}
	display();//display the state of the vehicle
}
void set_engine_temp(void){
	v1.engine_state=ON;//activating the engine

	float temp=0;//variable that will store and read in the temperature of engine

	printf("Enter the temperature of the engine in degree celsius\n");
	fflush(stdout);
	scanf(" %f",&temp);//read temperature

	if(temp<100||temp>150){
		v1.engine_temp_controller=ON;//turning on the controller
		v1.engine_temp=125;//setting engine temp to 125
	}
	else {
		v1.engine_temp_controller=OFF;//turning off the controller
		v1.engine_temp=temp;//setting the engine temp to the value read by the sensor
	}
	display();//display the state of the vehicle

}



void display(void){
	check_speed();//check before display

	printf ("\n \nCUURENT VEHICLE STATE:\n");
	printf("Engine state : %s \n",STATE[v1.engine_state]);
	printf("AC : %s \n",STATE[v1.AC_state]);
	printf("Vehicle speed : %d km/hr \n",v1.vehicle_speed);
	printf("Room temperature : %f C \n",v1.room_temp);
	printf("Engine temperature controller state : %s \n",STATE[v1.engine_temp_controller]);
	printf("Engine temperature : %f C \n\n\n",v1.engine_temp);
	fflush(stdout);

	sensor_set_menu();//go back to set menu
}

void check_speed(void){
	if(v1.vehicle_speed==30){
		v1.AC_state=ON;//turning AC on
		v1.room_temp =v1.room_temp*(5.0/4)+1;//adjusting room temp

		v1.engine_temp_controller=ON;//turning the engine temp controller
		v1.engine_temp=v1.engine_temp*(5.0/4)+1;//adjusting the engine temp

	}
}
