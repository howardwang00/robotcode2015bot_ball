// Created on Sat March 21 2015

// Replace FILE with your file's name
#ifndef _FILE_H_
#define _FILE_H_

#include "createDrive.h"
#include "generic.h"

#define light_start_sensor 2 //random #, change later, light sensor not yet applied
#define main_arm_servo_1 3
#define main_arm_servo_2 2
#define claw_servo 2

#define main_arm_up_servo_1 1475	//on top of mesa
#define main_arm_mid_servo_1 1000	//position of arm when driving
#define main_arm_down_servo_1 835	//picking up cubes
#define main_arm_up_servo_2 1700
#define main_arm_mid_servo_2 1225
#define main_arm_down_servo_2 1060

#define claw_hold_cubes 475
#define claw_open_regular 600	//when the claw is not holding anything
#define claw_hold_botguy 340	//holding botguy
#define claw_hold_pod 400	//holding pod

void start_function(int light_start_port)
{
	//light_start(light_start_port_or_function_start);
	shut_down_in(119); // Time is 120 seconds, but it needs to shut down a bit earlier
	enable_servos();
	create_connect();
}

void create_move(int left_power, int right_power, int mm) {	//create moving forward
	create_drive_direct(right_power, left_power);
	set_create_distance(0);
	while(get_create_distance() < mm) {
		msleep(1);
	}
}

void create_turn_CW(int speed /* mm per second */, int degrees) {	//create turning in place clockwise
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
	set_servo_position(main_arm_servo_2, position_of_servo1+225);
}
#endif
