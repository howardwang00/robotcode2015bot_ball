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
#define SERV_GRAB 3
#define MOT_PICK 3
#define SORT_SPEED 70

//Position functions
void sort_main(){set_servo_position(SERV_SORT,1500);msleep(200);}
void sort_sec(){set_servo_position(SERV_SORT,780);msleep(200);}
void sort_mid(){set_servo_position(SERV_SORT,1090);msleep(200);}
void grab_poms(){set_servo_position(SERV_GRAB,1000);msleep(200);}
void release_poms(){set_servo_position(SERV_GRAB,220);msleep(200);}

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
shakes the robot left and right reps amount of times

reps: the amount of shakes we did.
*/
void shake(int reps)
{
	int i;
	for(i = 0;i<reps;i++)
	{
		left(5,0);
		right(5,0);
	}
}
/*
sorts the poms into their respective bins for time seconds

mainColor: the pom color that goes into the main bin. See above comment for camera color designations.
initial: the average size of tribbles on the camera, based on a percentage value between 0 and 100.
fudge: the maximum discrepancy from the main size allowed, based on a percentage value between 0 and 100.
time: the duration for which this program runs, in seconds.
*/
void cam_sort(int mainColor, int initial, int fudge, int time, int jamDist)
{
	//initialization process
	if(initial<0||initial>100) 
		printf("Warning: Initial is out of the specified range\n");
	if(fudge<0||fudge>100)
		printf("Warning: Fudge is out of the specified range\n");
	int size;
	jamDist = jamDist*CMtoBEMF;
	float lastTest = curr_time();
	int discrepancy;
	//determining resolution
	printf("Tracking in:");
	switch(CAM_RES)
	{
		case LOW_RES:
			size = ((160*120)/100)*initial;
			discrepancy = ((160*120)/100)*fudge;
			printf("Low resolution\n");
		break;
		case MED_RES:
			size = ((320*240)/100)*initial;
			discrepancy = ((320*240)/100)*fudge;
			printf("Medium resolution\n");
		break;
		case HIGH_RES:
			size = ((640*480)/100)*initial;
			discrepancy = ((640*480)/100)*fudge;
			printf("High resolution\n");
		break;
	}
	//camera sorting process
	multicamupdate(5);
	float startTime = curr_time();
	int area = 0;
	int last = get_motor_position_counter(MOT_PICK);
	motor(MOT_PICK,SORT_SPEED);
	//Sorting process
	while(startTime+time>=curr_time())	//Timekeeper
	{
		if(lastTest+2<=curr_time())
		{
			if(jamDist>(get_motor_position_counter(MOT_PICK)-last))
			{
				motor(MOT_PICK,-100);
				//shake(5);
				msleep(3000);
				motor(MOT_PICK,SORT_SPEED);
			}
			last = get_motor_position_counter(MOT_PICK);
			lastTest = curr_time();
		}
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
/*
#define s_START 0
#define s_CROSSFIELD 1

struct menuitem menu[]=
{
	{s_START,"start"},
	{s_CROSSFIELD,"crossfield"}
};
*/
int main2()
{
	squareup(10);
	return 0;
}
int main4()
{
	camera_open(CAM_RES);
	enable_servos();
	motor(MOT_LEFT,15);
	motor(MOT_RIGHT,35);
	cam_sort(0,70,25,50,3);
}
int main()
{
	set_servo_position(SERV_GRAB,1250);
	msleep(300);
	camera_open(CAM_RES);
	release_poms();
	enable_servos();
	left(5,0);
	forward(45);
	grab_poms();
	right(5,0);
	forward(130);
	right(92,ks/2);
	backward(75);
	motor(MOT_LEFT,70);
	motor(MOT_RIGHT,74);
	cam_sort(0,70,25,30,3);
	release_poms();
	backward(30);
	forward(30);
	right(88,0);
	forward(60);
	motor(MOT_PICK,-40);
	grab_poms();
	backward(60);
	left(88,0);
	release_poms();
	//right(105,46);
	/*motor(MOT_LEFT,-70);
	motor(MOT_RIGHT,-70);
	msleep(3000);
	forward(2);
	left(20,0);
	forward(45);
	right(180,0);*/
	motor(MOT_LEFT,40);
	motor(MOT_RIGHT,55);
	cam_sort(0,70,25,50,3);
	forward(240);
	left(135,0);
	forward(120);
	right(45,0);
	forward(30);
	right(90,0);
	forward(100);
	return 0;
}
