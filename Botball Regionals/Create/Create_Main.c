// Created on Fri February 6 2015


#include "createDrive.h"
#include "generic.h"
#include "newmenu.h"

#define light_start_sensor 2 //random #, change later, light sensor not yet applied
#define touch_1 15
#define touch_2 14

#define main_arm_servo_1 2	//KIPR flipped 2 and 3 on the servo ports
//#define main_arm_servo_2 3
#define main_arm_pusher 1	//KIPR also flipped 0 and 1 on the servo ports
#define claw_servo 0


#define main_arm_up_servo_1 950
#define main_arm_mesa_forward 1160	//on top of mesa bulldozing in front
#define main_arm_mesa_behind 790	//on top of mesa bulldozing behind
#define main_arm_down_servo_1 1550	//picking up cubes
#define main_arm_default 100	//position of arm when driving
//#define main_arm_up_servo_2 
//#define main_arm_mid_servo_2 
//#define main_arm_down_servo_2 

#define pusher_down 2000
#define pusher_push 1350

#define claw_hold_cubes 475
#define claw_open_regular 700	//when the claw is not holding anything
#define claw_hold_botguy 340	//holding botguy
#define claw_bulldoze 1400


void start_function(int light_start_port_for_function_start); //function to start the robot

void end_program();

void create_move(int left_power, int right_power, int mm);

void create_turn_CW(int speed, int degrees);

void create_turn_CCW(int speed, int degrees);

void create_arm(int position_of_servo1);

void create_arm_default();

void create_end_function();

void create_squareup_wall(int power);


/** ======================================================= STATE MENU ===================================================== **/

//defining states
#define s_START 1
#define s_MID 2
#define s_FINAL 3
#define s_END 0


struct menuitem menu[]= {
	{s_START,"Start"},
	{s_MID,"Mid"},
	{s_FINAL,"Final"},
	{s_END,"END"}
};


/** ===================================================== END STATE MENU ===================================================== **/

//#define MAIN
#ifdef MAIN
void main()
{
	//while (currstate !
		//if (state == /*INSET STATE HERE*/) {
			create_arm(main_arm_down_servo_1 - 50);	//to get above the cubes when turned towards them
			set_servo_position(claw_servo, claw_open_regular);
			set_servo_position(main_arm_pusher, pusher_down); // pusher for arm not interferring with the beginning servo positions 
			start_function(light_start_sensor);
			
			
			msleep(100);
			create_drive_direct_dist(-10, -10, -5);	//get off the wall
			create_end_function();
		
			create_left(31, 0, 20); //turn to face cubes
			create_end_function();
			msleep(1000);
			set_servo_position(claw_servo, claw_open_regular + 50);
			msleep(300);
			
			
			create_arm(main_arm_down_servo_1);
			msleep(500);
			set_servo_position(claw_servo, claw_hold_cubes);
			msleep(700);
			create_arm(main_arm_up_servo_1);
			msleep(1); // make sure there is a stop in between
			set_servo_position(main_arm_pusher, pusher_push);
			msleep(1000);
			set_servo_position(main_arm_pusher, pusher_down);
			msleep(1000);
			create_left(17, 0, 15);	//turn to face caldera
		
		
			create_drive_direct_dist(-100, -100, -830);	//drive to caldera
			create_end_function();
			msleep(500);
		
			set_servo_position(claw_servo, claw_open_regular); //drop cubes
			msleep(500);
		//}
	
	end_program();
	//return 0; //It is a void main
}
#endif


/** CREATE STARTS IN BASE, FACING AWAY FROM THE MESA ABOUT TO DO A SQUARE-UP **/
#define ARMSWEEP
#ifdef ARMSWEEP
void main()
{
	create_arm_default();
	set_servo_position(claw_servo, claw_open_regular);
	set_servo_position(main_arm_pusher, pusher_down); // pusher for arm not interferring with the beginning servo positions 
	start_function(light_start_sensor);
	
	//squaring up
	create_squareup_wall(100);
	msleep(100);
	create_drive_direct_dist(100, 100, 50);
	create_end_function();
	create_right(90, 0, 100);	//93 is 90 for create
	create_end_function();
	create_squareup_wall(50);
	create_end_function();
	msleep(500);
	
	create_drive_direct_dist(100, 100, 50);
	create_end_function();
	create_right(90, 0, 100);	//face the mesa
	create_end_function();
	
	create_drive_direct_dist(-200, -200, -550);
	create_end_function();
	
	end_program();
}
#endif

/** =====================================================			FUNCTIONS			==================================================== **/



void start_function(int light_start_port) {
	//light_start(light_start_port_or_function_start);
	shut_down_in(119); // Time is 120 seconds, but it needs to shut down a bit earlier
	enable_servos();
	create_connect();
}

void end_program() {
	disable_servos();
	msleep(100);
	create_stop();
	create_block();
	msleep(100);
	create_disconnect();
}

void create_move(int left_power, int right_power, int mm) {	//create moving forward
	create_drive_direct(right_power, left_power);
	set_create_distance(0);
	while(get_create_distance() < mm) {
		msleep(1);
	}
}

void create_turn_CW(int speed /* mm per second */, int degrees) {	//create turning in place clockwises
	create_spin_CW(speed);
	set_create_normalized_angle(0);
	while(get_create_normalized_angle() < -degrees) {
		msleep(1);
	}
}

void create_turn_CCW(int speed /* mm per second */, int degrees) {	//create turning in place counter-clockwise
	create_spin_CCW(speed);
	set_create_normalized_angle(0);
	while(get_create_normalized_angle() < degrees) {
		msleep(1);
	}
}

void create_arm(int position_of_servo1 /* ticks of the servo */) {
	set_servo_position(main_arm_servo_1, position_of_servo1);
	//set_servo_position(main_arm_servo_2, (- position_of_servo1) + main_arm_down_servo_1 + 60);
}

void create_arm_default() {
	set_servo_position(main_arm_servo_1, main_arm_default);
	//set_servo_position(main_arm_servo_2, (- main_arm_default) + main_arm_down_servo_1 + 100);
}

void create_end_function() {
	create_stop();
	create_block();
}

void create_squareup_wall(int power) {
	int i = (power/5);
	if (power < 50) {
		i = 0;
	}
	//int anti_wall_climb = 0;
	/*
	if (power > 50) {
		i = - 10;
	}
	else if (power > 100) {
		i = - 20;
	}
	else if (power > 150) {
		i = - 30;
	}
	else if (power > 300) {
		i = - 40;
	}
	*/
	
	
	while ( digital(touch_1) != 1 && digital(touch_2) != 1) { //It uses and instead of or because it's weird
		create_drive_direct_dist(-power, -power, -10);
	}
	
	if ( digital(touch_1) == 1) {
		while ( digital(touch_2) != 1) {
			create_drive_direct_dist( - (power/2), (power/4) + i, -10);
		}
	}
	
	else if ( digital(touch_2) == 1) {
		while ( digital(touch_1) != 1) {
			create_drive_direct_dist((power/4) + i, - (power/2), -10);
		}
	}
	
	
	create_drive_direct_dist(20, 20, 5);
}

