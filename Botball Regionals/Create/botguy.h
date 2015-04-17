// Created on Sat April 11 2015

// Replace FILE with your file's name
#ifndef _botguy_H_
#define _botguy_H_

#include "createMove.h"



int create_track_botguy()
{
	int area;
	float time = curr_time();
	while(time + 3 > curr_time())
	{
		printf("Before Camera Update");
		camera_update();
		camera_update();
		camera_update();
		camera_update();
		printf("After Camera Update");
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
	}
	printf("Saw nothing :(((((((( !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	return NOTHING;
}


void if_red() {
	
	printf("Now delivering botgal to base!\n");
	
	//drive to base and drop botgal down
	
	set_servo_position(main_arm_pusher, pusher_shove);	//push the arm up and keep it there
	create_arm(main_arm_up_servo_1);
	
	create_right(100, 0, 100);
	create_backward(100, 200);
	create_end_function();
	
	create_arm_drive();
	msleep(300);
	set_servo_position(claw_servo, claw_open_regular);
	
	create_right(50, 0, 100);
	create_backward(100, 200);
	create_left(30, 0, 100);
	create_end_function();
	
	bulldoze();
	
}


void if_green() {
	
	printf("Now delivering botpod to mineral analysis area!");
	
	// square up first
	
	set_servo_position(main_arm_pusher, pusher_shove);	//push the arm up and keep it there
	create_arm(main_arm_up_servo_1);
	
	create_left(150, 0, 150);
	create_backward(550, 200);
	create_end_function();
	
	create_squareup_wall(75);
	create_end_function();
	set_servo_position(main_arm_pusher, pusher_hold);
	create_arm(main_arm_mesa_forward + 200);
	msleep(400);
	create_arm_drive();
	
	create_forward(1000, 300);
	create_right(200, 0, 150);	// turn to face right side of mineral analysis area to not mess up the Link
	create_backward(600, 200);
	create_end_function();
	msleep(100);
	
	set_servo_position(claw_servo, claw_open_regular);
	
	//now going to other side
	
	create_forward(1250, 200);
	create_right(160, 0, 150);
	create_end_function();
	
	
	bulldoze();
	
}


void backup() {
	
	printf("Oh no, didn't find botguy, now running bulldoze. :(");
	
	set_servo_position(main_arm_pusher, pusher_shove);	//push the arm up and keep it there
	create_arm(main_arm_up_servo_1);
	
	create_left(65, 0, 150);
	create_backward(200, 200);
	create_left(80, 0, 150);
	create_backward(100, 200);
	create_end_function();
	
	create_arm_drive();
	
	bulldoze();
	
}




#endif
