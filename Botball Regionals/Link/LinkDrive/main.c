#include "drive.h"
#include "generic.h"
#include "newmenu.h"

//Sensors
#define LEFT_BUMP digital(14)
#define RIGHT_BUMP digital(15)
#define CAM_RES LOW_RES

/*
Camera colors:

RED: #0
Hue:
Saturation:
Value:
 
GREEN: #1
Hue:
Saturation:
Value:
*/

//Motors and servos
#define SERV_SORT 0
#define MOT_PICK 1
#define SORT_SPEED 65

//Position functions
void sort_main(){set_servo_position(SERV_SORT,1500);msleep(200);}
void sort_sec(){set_servo_position(SERV_SORT,780);msleep(200);}
void sort_mid(){set_servo_position(SERV_SORT,1090);msleep(200);}

//Currently not in use. No touch sensors to use with.
void squareup(int max_time)
{
	float start_time = curr_time();
	while(!LEFT_BUMP&&!RIGHT_BUMP&&start_time+max_time>=curr_time())
	{
		if(!LEFT_BUMP)
			motor(MOT_LEFT,-50);
		else
			motor(MOT_LEFT,0);
		if(!RIGHT_BUMP)
			motor(MOT_RIGHT,-50);
		else
			motor(MOT_RIGHT,0);
	}
	ao();
}

/*
sorts the poms into their respective bins for time seconds

mainColor: the pom color that goes into the main bin. See above comment for camera color designations.
initial: the average size of tribbles on the camera, based on a percentage value between 0 and 100.
fudge: the maximum discrepancy from the main size allowed, based on a percentage value between 0 and 100.
time: the duration for which this program runs, in seconds.
*/
void cam_sort(int mainColor, int initial, int fudge, int time)
{
	//initialization process
	if(initial<0||initial>100) 
		printf("Initial is out of the specified range\n");
	if(fudge<0||fudge>100)
		printf("fudge is out of the specified range\n");
	int size;
	int discrepancy;
	printf("Tracking in:");
	switch(CAM_RES)
	{
		case LOW_RES:
			size = ((160*120)/100)*initial;
			discrepancy = ((160*120)/100)*fudge;
			printf("Low res\n");
		break;
		case MED_RES:
			size = ((320*240)/100)*initial;
			discrepancy = ((320*240)/100)*fudge;
			printf("Medium res\n");
		break;
		case HIGH_RES:
			size = ((640*480)/100)*initial;
			discrepancy = ((640*480)/100)*fudge;
			printf("High res\n");
		break;
	}
	multicamupdate(5);
	float startTime = curr_time();
	int area = 0;
	motor(MOT_PICK,SORT_SPEED);
	//Sorting process
	while(startTime+time>=curr_time())	//Timekeeper
	{
		camera_update();
		area = get_object_area(mainColor,0);
		if(area>500)
		{
			printf("Seen Blob of Main color\n");
			if(area>=size-discrepancy&&area<=size+discrepancy)
				sort_main();
			else
				printf("Blob failed specifications\n");
		}
		else
		{
			if(mainColor==0)
				area = get_object_area(1,0);
			else
				area = get_object_area(0,0);
			if(area>500)
				printf("Seen Blob of Secondary color\n");
			if(area>=size-discrepancy&&area<=size+discrepancy)
				sort_sec();
			else
				printf("Blob failed specifications\n");
		}
		sort_mid();
	}
}
int main2()
{
	squareup(10);
	return 0;
}
int main()
{
	camera_open(CAM_RES);
	enable_servos();
	motor(MOT_LEFT,15);
	motor(MOT_RIGHT,35);
	cam_sort(0,50,25,50);
}
int main3()
{
	camera_open(LOW_RES);
	enable_servos();
	forward(120);
	left(50,0);
	forward(60);
	right(50,0);
	forward(45);
	right(180,0);
	cam_sort(0,50,25,10);
	forward(240);
	left(135,0);
	forward(120);
	right(45,0);
	forward(30);
	right(90,0);
	forward(100);
	return 0;
}
