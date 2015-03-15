// Created on Fri February 6 2015 by: Howard Wang


#include "createDrive.h"
#include "generic.h"

#define light_start_sensor 2 //random #, change later
#define main_arm_servo 3
#define claw_servo 2


#define main_arm_up 1475	//on top of mesa
#define main_arm_mid 1000	//driving
#define main_arm_down 835	//picking up cubes
#define claw_hold_cubes 475
#define claw_open_regular 600
#define claw_hold_botguy 340	//holding botguy
#define claw_hold_pod 400	//holding pod

void start_function(int light_start_port_for_function_start); //function to start the robot

void create_move(int left_power, int right_power, int mm);

int main()
{
	start_function(light_start_sensor);
	
	create_move_forward(100, 100, 300);
	
	create_stop();
	
	
	//set_servo_position(main_arm_servo, main_arm_mid); //move arm to a higher position than cubes
	//msleep(100);
	//create_drive_direct_dist(-10, -10, 10);
	//msleep(60000);
	//create_stop();
	//msleep(500);
	
	//create_left(10, 0, 100); //turn to face cubes
	//msleep(10000);
	/*
	set_servo_position(main_arm_servo, main_arm_down+30);
	msleep(200);
	set_servo_position(main_arm_servo, main_arm_down);
	msleep(300);
	set_servo_position(claw_servo, claw_hold_cubes);
	msleep(100);
	set_servo_position(main_arm_servo, main_arm_up);
	msleep(20000); // wait 20 seconds for Link to pass
	*/
	
	/*create_drive_direct_dist(-100, -100, 100);
	msleep(100);
	create_drive_direct_dist(-30, -30, 100); //go slower for the rest of the way
	msleep(300);
	*/
	
	//set_servo_position(claw_servo, claw_open_regular); //drop cubes
	
	
	disable_servos();
	//create_stop();
	create_disconnect();
	return 0;
}



void start_function(int light_start_port)
{
	//light_start(light_start_port_or_function_start);
	shut_down_in(119.5); // Time is 120 seconds, but it needs to shut down a bit earlier
	enable_servos();
	create_connect();
}


void create_move(int left_power, int right_power, int mm) {
	create_drive_direct(right_power, left_power);
	set_create_distance(0);
	while(get_create_distance() < mm+1) {
		msleep(1);
	}
}



