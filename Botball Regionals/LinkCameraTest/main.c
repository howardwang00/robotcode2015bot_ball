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
 
#include "newmenu.h"
#include "generic.h"

//Colors
#define RED_START 0
#define GREEN_START 1
//Servos and Motors
#define SERV_SORT 0
#define MOT_PICK 0
//Position Functions
void sort_main(){set_servo_position(SERV_SORT,1833);}
void sort_sec(){set_servo_position(SERV_SORT,640);}

/*
sorts the poms into their respective bins for time seconds

mainColor: the pom color that goes into the main bin
size: the average size of tribbles on the camera
discrepancy: the maximum discrepancy from the main size allowed
time: the duration for which this program runs
*/
void cam_sort(int mainColor, int size, int discrepancy, int time)
{
	printf("blah1");
	camera_update();
	printf("blah");
	float startTime = curr_time();
	printf("blah");
	int area = 0;
	while(startTime+time>=curr_time())	//Timekeeper
	{
		camera_update();
		printf("works pre-check");
		area = get_object_area(mainColor,0);
		printf("the check works");
		if(area>=size-discrepancy&&area<=size+discrepancy)
			sort_main();
		else
			sort_sec();
	}
}
int main()
{
	camera_open(LOW_RES);
	enable_servos();
	motor(MOT_PICK,100);
	//msleep(100000);
	printf("test1");
	cam_sort(0,1000,100,10);
	msleep(1000);
	printf("test2");
	msleep(1000);
	disable_servos();
	return 0;
}
