// Created on Fri February 6 2015 by: Howard Wang


#include "createDrive.h"
#include "generic.h"

#define light_start_sensor 2 //random #, change later
#define main_arm_servo 3
#define claw_servo 2


#define main_arm_up 1475	//on top of mesa
#define main_arm_mid 1000	//driving
#define main_arm_down 835	//picking up cubes
#define claw_hold_cubes 234	//need value
#define claw_open_regular 234	//need value


void start(int light_start_port_for_function_start);



int main()
{
	/*
	light_start(light_start_sensor);
	shut_down_in(119.5); // Time is 120 seconds, but it needs to shut down a bit earlier
	enable_servos();
	//put cubes sideways in the middle of tape, facing Create
	*/
	start(light_start_sensor);
	
	set_servo_position(main_arm_servo, main_arm_mid); //move arm to a higher position than cubes
	create_right(30, 0, 100); //turn to face cubes
	set_servo_position(main_arm_servo, main_arm_down);
	msleep(200);
	set_servo_position(claw_servo, claw_hold_cubes);
	msleep(100);
	set_servo_position(main_arm_servo, main_arm_up);
	msleep(20000); // wait 20 seconds for Link to pass
	
	create_drive_direct_dist(100, 100, 100);
	create_block();
	msleep(100);
	create_drive_direct_dist(30, 30, 100); //go slower for the rest of the way
	msleep(300);
	
	set_servo_position(claw_servo, claw_open_regular); //drop cubes
	
	
	
	return 0;
}



void start(int light_start_port_for_function_start)
{
	int light_start_port_for_function_start;
	light_start(light_start_sensor_function_start);
	shut_down_in(119.5); // Time is 120 seconds, but it needs to shut down a bit earlier
	enable_servos();
}

