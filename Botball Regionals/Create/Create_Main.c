// Created on Fri February 6 2015


#include "createDrive.h"
#include "generic.h"
#include "newmenu.h"

#define RED 0	//for camera
#define GREEN 1
#define NOTHING 234234234234234	//random #

#define light_start_sensor 2 //random #, change later, light sensor not yet applied
#define touch_1 14	//flipped because I flipped my code
#define touch_2 15

#define main_arm_servo_1 2	//KIPR flipped 2 and 3 on the servo ports
//#define main_arm_servo_2 3
#define main_arm_pusher 1	//KIPR also flipped 0 and 1 on the servo ports
#define claw_servo 0


#define main_arm_up_servo_1 900
#define main_arm_mesa_forward 1200	//on top of mesa bulldozing in front
#define main_arm_mesa_behind 625	//on top of mesa bulldozing behind
#define main_arm_down_servo_1 1525	//picking up cubes 
#define main_arm_drive 1375
//#define main_arm_up_servo_2 
//#define main_arm_mid_servo_2 
//#define main_arm_down_servo_2 

#define pusher_down 0
#define pusher_push 725
#define pusher_shove 1225 //pushing arm up all the way
#define pusher_hold 625 // holding up arm while driving
#define pusher_behind 1475	//push the arm back so it can lift botguy

#define claw_hold_cubes 475
#define claw_open_regular 700	//when the claw is not holding anything
#define claw_hold_botguy 320	//holding botguy
#define claw_sweep 1350


void start_function(int light_start_port_for_function_start); //function to start the robot

void end_program();

void create_move(int left_power, int right_power, int mm);

void create_turn_CW(int speed, int degrees);

void create_turn_CCW(int speed, int degrees);

void create_arm(int position_of_servo1);

void create_end_function();

void create_squareup_wall(int power);

void create_arm_drive();

int create_track_botguy();

void create_squareup_rightangle(int first_speed, int second_speed);

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
	
	create_arm(main_arm_down_servo_1 - 25);	//to get above the cubes when turned towards them
	set_servo_position(claw_servo, claw_open_regular);
	set_servo_position(main_arm_pusher, pusher_down + 600);	//help push the arm up
	start_function(light_start_sensor);
	
	
	msleep(100);
	create_drive_direct_dist(-10, -10, -5);	//get off the wall
	create_end_function();
	
	set_servo_position(claw_servo, claw_open_regular + 200);
	msleep(500);

	create_left(31, 0, 75); //turn to face cubes
	create_end_function();
	msleep(1000);
	
	set_servo_position(main_arm_pusher, pusher_down);	// pusher for arm not interferring with the beginning servo positions
	create_arm(main_arm_down_servo_1);
	msleep(800);
	set_servo_position(claw_servo, claw_hold_cubes);
	msleep(800);
	set_servo_position(main_arm_pusher, pusher_shove);
	create_arm(main_arm_up_servo_1 - 50);
	msleep(500);
	
	create_left(25, 0, 30);	//turn to face mesa to drop cubes next to mesa
	create_drive_direct_dist(-150, -150, -700);	//drive to mesa
	create_drive_direct_dist(-50, -50, -125);	//go slower
	create_end_function();
	msleep(100);
	
	set_servo_position(claw_servo, claw_open_regular);
	msleep(500);
	create_arm(main_arm_mesa_behind);	//so we won't hit botgal/pod
	create_left(47, 0, 75); //face botgal/pod
	create_backward(100, 75);	//get close to botguy
	create_end_function();
	
	create_arm(main_arm_up_servo_1 - 100);
	msleep(300);
	create_arm(main_arm_up_servo_1);
	msleep(500);
	set_servo_position(claw_servo, claw_hold_botguy);
	msleep(1000);
	
	set_servo_position(main_arm_pusher, pusher_behind);	//push the arm up and keep it there
	create_arm(main_arm_mesa_behind);
	msleep(500);
	
	create_forward(50, 50);
	create_end_function();
	
	set_servo_position(main_arm_pusher, pusher_shove);
	
	msleep(2000);
	
	end_program();
}
#endif


/** CREATE STARTS IN BASE, FACING AWAY FROM THE MESA ABOUT TO DO A SQUARE-UP **/
//#define ARMSWEEP
#ifdef ARMSWEEP
void main()
{
	create_arm_drive();
	set_servo_position(claw_servo, claw_open_regular);
	start_function(light_start_sensor);
	
	create_squareup_rightangle(100, 50);
	
	create_right(81, 0, 100);	//face the mesa
	
	set_servo_position(claw_servo, claw_hold_cubes);	//so it doesn't hit the mesa
	msleep(100);
	
	//for momentum, so that the arm will have more time to accelerate
	set_servo_position(main_arm_pusher, pusher_down);
	create_arm(main_arm_down_servo_1);
	msleep(500);
	
	set_servo_position(main_arm_pusher, pusher_shove);
	create_arm(main_arm_up_servo_1 - 100);
	msleep(1000);
	
	create_drive_direct_dist(-200, -200, -750);	//go to mesa
	create_drive_direct_dist(-100, -100, -120);
	create_right(96, 0, 100);
	create_end_function();
	msleep(500);
	
	create_arm(main_arm_mesa_behind + 100);
	msleep(100);
	set_servo_position(main_arm_pusher, pusher_hold);	//go back
	set_servo_position(claw_servo, claw_sweep);
	printf("Ready to Sweep!");
	msleep(300);
	
	create_backward(50, 50);
	msleep(100);
	create_arm(main_arm_mesa_behind);
	create_backward(500, 50);
	create_end_function();
	
	create_forward(500, 100);
	create_end_function();
	
	create_arm(main_arm_mesa_forward - 200);
	msleep(1000);
	create_arm(main_arm_mesa_forward);
	msleep(100);
	
	create_backward(200, 75);
	create_end_function();
	
	set_servo_position(claw_servo, claw_open_regular - 50);	//push stuff into claw range
	msleep(500);
	set_servo_position(claw_servo, claw_sweep);
	
	create_right(3, 0, 10);
	create_backward(270, 50);
	create_end_function();
	
	set_servo_position(claw_servo, claw_open_regular);	//push stuff in
	msleep(1000);
	set_servo_position(claw_servo, claw_sweep);
	
	end_program();
}
#endif

#define BOTGUY_TRACK
#ifdef BOTGUY_TRACK
void main() {
	set_servo_position(main_arm_pusher, pusher_behind);	//push the arm up and keep it there
	create_arm(main_arm_mesa_behind);
	set_servo_position(claw_servo, claw_hold_botguy);
	start_function(light_start_sensor);
	
	msleep(100);
	
	create_track_botguy();
	
	msleep(10000);
	
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

void create_end_function() {
	create_stop();
	create_block();
}

void create_squareup_wall(int power) {
	
	while ( digital(touch_1) != 1 && digital(touch_2) != 1) { //It uses and instead of or because it's weird
		create_drive_direct(-power, -power);
		msleep(100);
	}
	
	if ( digital(touch_1) == 1) {
		while ( digital(touch_2) != 1) {
			create_drive_direct( - (power/4), (power/6));
			msleep(100);
		}
	}
	
	else if ( digital(touch_2) == 1) {
		while ( digital(touch_1) != 1) {
			create_drive_direct((power/6), - (power/4));
			msleep(100);
		}
	}
	
	create_end_function();
	msleep(100);
	create_drive_direct_dist(20, 20, 5);
}

void create_arm_drive() {
	set_servo_position(main_arm_pusher, pusher_hold);
	create_arm(main_arm_drive);
}

int create_track_botguy()
{
	int area;
	float time = curr_time();
	while(time + 3 > curr_time())
	{
		camera_update();
		area = get_object_area(RED,0);
		if (area > 500)
		{
			printf("Seen Blob of Red color\n");
			return RED;
		}
		area = get_object_area(GREEN,0);
		if (area > 500)
		{
			printf("Seen Blob of Green color\n");
			return GREEN;
		}
		
		printf("Saw nothing :(((((((( !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
		return NOTHING;
	}
}

void create_squareup_rightangle(int first_speed, int second_speed) {
	//squaring up
	create_squareup_wall(first_speed);
	msleep(100);
	//create_drive_direct_dist(100, 100, 50);
	create_right(85, 0, 100);
	create_end_function();
	create_squareup_wall(second_speed);
	msleep(100);
	create_end_function();
	msleep(500);
	
	create_drive_direct_dist(100, 100, 10);
}
