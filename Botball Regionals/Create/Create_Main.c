// Created on Fri February 6 2015


#include "botguy.h"




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

#define MAIN
#ifdef MAIN
void main()
{
	
	create_arm(main_arm_down_servo_1 - 25);	//to get above the cubes when turned towards them
	set_servo_position(claw_servo, claw_open_regular);
	set_servo_position(main_arm_pusher, pusher_down + 600);	//help push the arm up
	start_function(light_start_sensor);
	
	create_drive_direct_dist(-10, -10, -10);	//get off the wall
	create_end_function();
	
	set_servo_position(claw_servo, claw_open_regular + 200);
	msleep(500);

	create_left(31, 0, 100); //turn to face cubes
	create_end_function();
	msleep(1000);
	
	set_servo_position(main_arm_pusher, pusher_down);	// pusher for arm not interferring with the beginning servo positions
	create_arm(main_arm_down_servo_1);
	msleep(800);
	set_servo_position(claw_servo, claw_hold_cubes);
	msleep(1000);
	set_servo_position(main_arm_pusher, pusher_shove);
	create_arm(main_arm_up_servo_1 - 55);
	msleep(500);
	
	create_left(25, 0, 30);	//turn to face mesa to drop cubes next to mesa
	create_drive_direct_dist(-200, -200, -700);	//drive to mesa
	create_drive_direct_dist(-100, -100, -125);	//go slower
	create_end_function();
	msleep(100);
	
	set_servo_position(claw_servo, claw_open_regular);
	msleep(500);
	create_arm(main_arm_mesa_behind);	//so we won't hit botgal/pod
	
	//create_forward(50, 100);
	//create_end_function();
	msleep(100);
	create_left(47, 0, 100); //face botgal/pod
	create_backward(100, 150);	//get close to botguy
	create_end_function();
	
	//arm go up to botguy
	msleep(100);
	create_arm(main_arm_up_servo_1 - 100);
	msleep(300);
	create_arm(main_arm_up_servo_1 - 25);
	msleep(1000);
	set_servo_position(claw_servo, claw_hold_botguy);
	msleep(500);
	
	set_servo_position(main_arm_pusher, pusher_behind);	//push the arm up and keep it there
	create_arm(main_arm_mesa_behind);
	msleep(500);
	
	create_forward(50, 150);	//now have botguy
	create_end_function();
	
	
	if (create_track_botguy() == RED) {
		if_red();	//see botguy.h
	}
	else if (create_track_botguy() == GREEN) {
		if_green();
	}
	else if (create_track_botguy() == NOTHING) {	//never runs this for some reason
		//backup();
		if_red();	//because sometimes it doesn't see botguy
	}
	else {
		//backup();
		if_red();
	}
	
	
	msleep(1000);
	
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
	
	bulldoze();
	
	end_program();
}
#endif

//#define BOTGUY_TRACK
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


