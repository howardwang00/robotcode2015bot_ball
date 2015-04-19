// Created on Mon April 13 2015

// Replace FILE with your file's name
#ifndef _createMove_H_
#define _createMove_H_


#include "createDrive.h"
#include "generic.h"
#include "newmenu.h"

#define RED 0	//for camera
#define GREEN 1
#define NOTHING 234	//random #



#define light_start_sensor 0
#define touch_1 14	//flipped because I flipped my code
#define touch_2 15

#define main_arm_servo_1 2	//KIPR flipped 2 and 3 on the servo ports
//#define main_arm_servo_2 3
#define main_arm_pusher 1	//KIPR also flipped 0 and 1 on the servo ports
#define claw_servo 0


#define main_arm_up_servo_1 750
#define main_arm_mesa_forward 1200	//on top of mesa bulldozing in front
#define main_arm_mesa_behind 450	//on top of mesa bulldozing behind
#define main_arm_down_servo_1 1400	//picking up cubes 
#define main_arm_drive 1225
//#define main_arm_up_servo_2 
//#define main_arm_mid_servo_2 
//#define main_arm_down_servo_2 

#define pusher_down 0
#define pusher_shove 1250 //pushing arm all the way up
#define pusher_hold 675 // holding up arm while driving
#define pusher_behind 1475	//push the arm all the way back so it can lift botguy

#define claw_hold_cubes 475
#define claw_open_regular 700	//when the claw is not holding anything
#define claw_hold_botguy 320	//holding botguy
#define claw_sweep 1400
#define claw_igus 310



/** =====================================================			FUNCTIONS			==================================================== **/

void start_function(int light_start_port) {
	light_start(light_start_port);
	shut_down_in(119); // Time is 120 seconds, but it needs to shut down a bit earlier
	enable_servos();
	create_connect();
	create_full();
	printf("Connected to Create\n");
	camera_open(LOW_RES);
	printf("Connected to Camera\n");
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

void bulldoze() {	// STARTS FACING AWAY FROM MESA, NEXT TO BASE, NEAR RIGHT ANGLE AWAY FROM CALDERA
	
	create_squareup_rightangle(100, 75);
	create_end_function();
	set_servo_position(claw_servo, claw_open_regular);	//drop botguy/pod if it's still there so the program doesn't screw up
	
	create_right(80, 0, 100);	//face the mesa
	
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
	create_drive_direct_dist(-100, -100, -100);
	create_right(101, 0, 100);
	create_end_function();
	msleep(500);
	
	create_arm(main_arm_mesa_behind + 100);
	msleep(100);
	set_servo_position(main_arm_pusher, pusher_hold);	//go back
	set_servo_position(claw_servo, claw_sweep);
	printf("Ready to Sweep!");
	msleep(300);
	
	create_backward(50, 100);
	msleep(100);
	create_arm(main_arm_mesa_behind);
	create_backward(100, 75);
	create_end_function();
	set_servo_position(claw_servo, claw_open_regular + 50);	//push stuff into claw range
	msleep(300);
	set_servo_position(claw_servo, claw_sweep);
	msleep(300);
	create_backward(100, 75);
	create_end_function();
	set_servo_position(claw_servo, claw_open_regular + 50);	//push stuff into claw range
	msleep(300);
	set_servo_position(claw_servo, claw_sweep);
	msleep(300);
	create_backward(100, 75);
	set_servo_position(claw_servo, claw_open_regular);	//push stuff into claw range
	msleep(500);
	set_servo_position(claw_servo, claw_sweep);
	msleep(500);
	create_backward(200, 75);	//bulldoze with arm behind
	create_end_function();
	
	create_forward(500, 200);	//go back
	create_end_function();
	
	create_arm(main_arm_mesa_forward - 200);
	msleep(700);
	create_arm(main_arm_mesa_forward);	//prepare to sweep
	msleep(100);
	
	create_right(3, 0, 50);
	create_backward(150, 100);
	create_left(3, 0, 50);
	create_backward(50, 100);
	create_end_function();
	
	
	set_servo_position(claw_servo, claw_open_regular);	//push stuff into claw range
	msleep(500);
	set_servo_position(claw_servo, claw_sweep);
	msleep(500);
	
	
	create_backward(100, 50);
	create_end_function();
	set_servo_position(claw_servo, claw_open_regular);	//push stuff into claw range
	msleep(500);
	set_servo_position(claw_servo, claw_sweep);
	create_backward(100, 50);
	create_end_function();
	msleep(100);
	create_backward(100, 50);
	create_end_function();
	msleep(100);
	
	create_forward(20, 50);	//so it helps the game pieces go in
	create_end_function();
	//set_servo_position(claw_servo, claw_open_regular);	//push stuff in
	msleep(500);
	create_backward(20, 50);
	create_end_function();
	create_arm(main_arm_up_servo_1);
	set_servo_position(claw_servo, claw_sweep);
	msleep(200);
	
	create_arm(main_arm_up_servo_1);
	msleep(100);
	create_forward(50, 100);
	create_end_function();
	msleep(100);
	create_arm(main_arm_mesa_forward - 200);	//allow us to push all the way
	create_backward(50, 100);
	
	
	create_backward(100, 50);	//drive all the way
	create_end_function();
	set_servo_position(claw_servo, claw_open_regular);	//try to push stuff in again
	msleep(200);
	create_arm(main_arm_up_servo_1);
	set_servo_position(claw_servo, claw_sweep);
	msleep(100);
	create_arm(main_arm_mesa_forward - 100);
	set_servo_position(claw_servo, claw_open_regular);	//push stuff in again
	msleep(100);
	
	create_arm(main_arm_mesa_behind);
	create_forward(400, 100);	//drive back
	create_end_function();
	set_servo_position(claw_servo, claw_sweep);
	create_arm(main_arm_mesa_forward - 200);
	msleep(300);
	create_arm(main_arm_mesa_forward);
	msleep(100);
	create_backward(200, 50);
	create_end_function();
	create_arm(main_arm_up_servo_1);
	msleep(100);
	create_arm(main_arm_mesa_forward - 100);
	msleep(100);
	set_servo_position(claw_servo, claw_open_regular);	//push stuff in again
	msleep(100);
	set_servo_position(claw_servo, claw_sweep);
	msleep(100);
	create_backward(200, 50);
	create_end_function();
	set_servo_position(claw_servo, claw_open_regular - 50);	//push stuff in again
	msleep(100);
	set_servo_position(claw_servo, claw_sweep);
	msleep(100);
}








#endif
