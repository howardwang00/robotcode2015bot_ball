#include "drive.h"
#include "generic.h"
#include "newmenu.h"
#define SERV_SORT 0
#define MOT_PICK 0
void sort_main(){set_servo_position(SERV_SORT,1500);msleep(500);}
void sort_sec(){set_servo_position(SERV_SORT,833);msleep(500);}
void cam_sort(int mainColor, int size, int discrepancy, int time)
{
	camera_update();
	float startTime = curr_time();
	int area = 0;
	while(startTime+time>=curr_time())	//Timekeeper
	{
		camera_update();
		if(get_object_count(0)>0)
		{
			area = get_object_area(mainColor,0);
			printf("test a");
			if(area>=size-discrepancy&&area<=size+discrepancy)
				sort_main();
			else
				sort_sec(); printf("%d",area);
		}
	}
}
int main()
{
	camera_open(LOW_RES);
	enable_servos();
	motor(MOT_PICK,100);
	forward(120);
	left(50,0);
	forward(60);
	right(50,0);
	forward(45);
	right(180,0);
	cam_sort(0,1000,100,10);
	forward(240);
	left(135,0);
	forward(120);
	right(45,0);
	forward(30);
	right(90,0);
	forward(100);
}
