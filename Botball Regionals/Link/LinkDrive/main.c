#include "drive.h"
#include "generic.h"
#include "newmenu.h"
#define LEFT_BUMP digital(14)
#define RIGHT_BUMP digital(15)
#define SERV_SORT 0
#define MOT_PICK 1
void sort_main(){set_servo_position(SERV_SORT,1500);msleep(200);}
void sort_sec(){set_servo_position(SERV_SORT,780);msleep(200);}
void sort_mid(){set_servo_position(SERV_SORT,1090);msleep(200);}
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
void cam_sort(int mainColor, int size, int discrepancy, int time)
{
	multicamupdate(5);
	float startTime = curr_time();
	int area = 0;
	motor(MOT_PICK,65);
	while(startTime+time>=curr_time())	//Timekeeper
	{
		camera_update();
		int sorted_color;
		area = get_object_area(mainColor,0);
		if(area>500)
		{
			printf("Seen Main Blob\n");
			//motor(MOT_PICK,0);
			sorted_color = 0;
			if(area>=size-discrepancy&&area<=size+discrepancy)
				sort_main();
		}
		else
		{
			area = get_object_area(1,0);
			if(area>500)
			{
			printf("Seen Sec Blob\n");
			//	motor(MOT_PICK,0);
			}
			sorted_color = 1;
			if(area>=size-discrepancy&&area<=size+discrepancy)
				sort_sec();
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
	camera_open(LOW_RES);
	enable_servos();
	motor(MOT_LEFT,15);
	motor(MOT_RIGHT,35);
	motor(MOT_PICK,70);
	cam_sort(0,9600,4800,50);
}
int main3()
{
	camera_open(LOW_RES);
	enable_servos();
	mav(MOT_PICK,1000);
	forward(120);
	left(50,0);
	forward(60);
	right(50,0);
	forward(45);
	right(180,0);
	cam_sort(0,13440,4800,10);
	forward(240);
	left(135,0);
	forward(120);
	right(45,0);
	forward(30);
	right(90,0);
	forward(100);
}
