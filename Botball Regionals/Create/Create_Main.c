// Created on Fri February 6 2015


#include "createDrive.h"
#include "generic.h"

//#define Tournament 1

#define light_start_sensor 2 //random #, change later, light sensor not yet applied
#define main_arm_servo_1 2	//KIPR flipped 2 and 3 on the servo ports
#define main_arm_servo_2 3
#define claw_servo 2


#define main_arm_up_servo_1 1225	//on top of mesa
//#define main_arm_mid_servo_1 1280
#define main_arm_down_servo_1 1825	//picking up cubes
#define main_arm_default 530	//position of arm when driving
//#define main_arm_up_servo_2 
//#define main_arm_mid_servo_2 
//#define main_arm_down_servo_2 

#define claw_hold_cubes 475
#define claw_open_regular 600	//when the claw is not holding anything
#define claw_hold_botguy 340	//holding botguy
#define claw_hold_pod 400	//holding pod


void start_function(int light_start_port_for_function_start); //function to start the robot

void create_move(int left_power, int right_power, int mm);

void create_turn_CW(int speed, int degrees);

void create_turn_CCW(int speed, int degrees);

void create_arm(int position_of_servo1);

void create_default();



#define MAIN
#ifdef MAIN
int main()
{
	create_default();	//make sure servo is in the correct position so enabling servos won't screw us up
	printf("1\n");
	start_function(light_start_sensor);
	printf("4\n");
	
	
	msleep(1000);
	create_arm(main_arm_up_servo_1); //move arm to a higher position than cubes
	printf("5");
	msleep(500);
	create_arm(main_arm_down_servo_1);
	printf("6");
	msleep(500);
	
	
	
	
	
	disable_servos();
	msleep(100);
	create_stop();
	create_block();
	msleep(100);
	create_disconnect();
	return 0;
}
#endif


//#define TEST_CREATE_DRIVEPATH
#ifdef TEST_CREATE_DRIVEPATH
void main()
{
	
	msleep(100);
	create_drive_direct_dist(-10, -10, -10);	//get off the wall
	create_stop();
	create_block();
	msleep(500);
	
	create_left(30, 0, 10); //turn to face cubes
	create_stop();
	create_block();
	msleep(100);
	
	
	create_arm(main_arm_down-30);
	msleep(200);
	create_arm(main_arm_down);
	msleep(300);
	set_servo_position(claw_servo, claw_hold_cubes);
	msleep(100);
	create_arm(main_arm_up);
	msleep(20000); // wait 20 seconds for Link to pass
	
	
	create_drive_direct_dist(-100, -100, -100);
	create_drive_direct_dist(-30, -30, -100); //go slower for the rest of the way
	create_stop();
	create_block();
	
	
	set_servo_position(claw_servo, claw_open_regular); //drop cubes
	msleep(500);
	
}
#endif



/** =====================================================			FUNCTIONS			=====================================================**/



void start_function(int light_start_port)
{
	#ifdef Tournament
	light_start(light_start_port_or_function_start);
	#endif
	shut_down_in(119); // Time is 120 seconds, but it needs to shut down a bit earlier
	printf("2\n");
	enable_servos();
	printf("3\n");
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
	set_servo_position(main_arm_servo_2, (- position_of_servo1) + main_arm_down_servo_1 + 60);
}

void create_default() {
	set_servo_position(main_arm_servo_1, main_arm_default);
	set_servo_position(main_arm_servo_2, (- main_arm_default) + main_arm_down_servo_1 + 100);
}

