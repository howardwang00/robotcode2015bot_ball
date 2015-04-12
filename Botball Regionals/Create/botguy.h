// Created on Sat April 11 2015

// Replace FILE with your file's name
#ifndef _FILE_H_
#define _FILE_H_


#include "createDrive.h"
#include "generic.h"
#include "newmenu.h"

#define RED 0	//for camera
#define GREEN 1
#define NOTHING 234234	//random #



int create_track_botguy()
{
	int area;
	float time = curr_time();
	while(time + 3 > curr_time())
	{
		printf("Before Camera Update");
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
	create_left(75, 0, 100);
	create_backward(200, 150);
	create_left(50, 0, 100);
	create_end_function();
	
	create_arm_drive();
	set_servo_position(claw_servo, claw_open_regular);
	
	create_right(50, 0, 100);
	create_end_function();
	
	bulldoze();
	
}


void if_green() {
	
	printf("Now delivering botpod to mineral analysis area!");
	
	// square up first
	
	create_left(75, 0, 100);
	create_backward(200, 150);
	
	create_squareup_wall(50);
	create_end_function();
	
	//now going to other side
	
}


void backup() {
	
	printf("Oh no, didn't find botguy, now running bulldoze. :(");
	
	
	create_left(75, 0, 100);
	
	create_arm_drive();
	
	create_backward(200, 150);
	
	bulldoze();
	
}




#endif
