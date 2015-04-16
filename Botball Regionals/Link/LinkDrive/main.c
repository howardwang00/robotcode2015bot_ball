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
#define SERV_SORT 2
#define SERV_SWEEP 0
#define SERV_GRAB 3
#define MOT_PICK 3
#define SORT_SPEED 70

//Position functions
void sort_main(){set_servo_position(SERV_SORT,600);msleep(200);}
void sort_sec(){set_servo_position(SERV_SORT,1050);}
//void sort_mid(){set_servo_position(SERV_SORT,1090);msleep(200);}

void grab_poms(){set_servo_position(SERV_GRAB,1490);msleep(200);set_servo_position(SERV_GRAB,1410);}
void release_poms(){set_servo_position(SERV_GRAB,2047);msleep(200);}
void bump_poms(){set_servo_position(SERV_GRAB,1510);msleep(10);set_servo_position(SERV_GRAB,1410);}

void sweep_bump(){set_servo_position(SERV_SWEEP,1450);msleep(20);}
void sweep_out(){set_servo_position(SERV_SWEEP,982);msleep(200);}
void sweep_out2(){set_servo_position(SERV_SWEEP,1182);msleep(100);}
void sweep_default(){set_servo_position(SERV_SWEEP,1750);msleep(50);}
/*void slow_servo(int servo,int pos)
{
	if(pos > get_servo_position(servo))
	{
		while(pos > get_servo_position(servo))
		{
			set_servo_position(servo,get_servo_position(servo)+10);
			msleep(20);
		}
	}
	else
	{
		while(pos < get_servo_position(servo))
		{
			set_servo_position(servo,get_servo_position(servo)-10);
			msleep(20);
		}
	}
}*/
//void bump_poms()
//{
	/*set_servo_position(SERV_GRAB,1500);
msleep(200);*/
//set_servo_position(SERV_GRAB,800);
//msleep(200);
	/*motor(MOT_LEFT,50);
	motor(MOT_RIGHT,50);
	clear_all_drive();
	WAIT(5*CMtoBEMF<=gmpc(MOT_RIGHT)&&5*CMtoBEMF<=gmpc(MOT_LEFT))
	motor(MOT_RIGHT,0);
motor(MOT_LEFT,0);*/
//}

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
size: the average size of tribbles on the camera, based on a percentage value between 0 and 100.
discrepancy: the maximum discrepancy from the main size allowed, based on a percentage value between 0 and 100.
time: the duration for which this program runs, in seconds.
*/
void cam_sort(int mainColor, int size, int discrepancy, int time, int jamDist)
{
	motor(MOT_PICK,-SORT_SPEED);
	msleep(500);
	//initialization process
	if(size<0||size>100) 
	printf("Warning: Size is out of the specified range!\n");
	if(discrepancy<0||discrepancy>100)
	printf("Warning: Discrepancy is out of the specified range!\n");
	jamDist = jamDist*CMtoBEMF;
	float lastTest = curr_time();
	//determining resolution
	printf("Tracking in:");
	int res_val = 0;
	switch(CAM_RES)
	{
		case LOW_RES:
		res_val = (160*120)/100;
		printf("Low res\n");
		break;
		case MED_RES:
		res_val = (320*240)/100;
		printf("Medium res\n");
		break;
		case HIGH_RES:
		res_val = (640*480)/100;
		printf("High res\n");
		break;
		default:
		printf("Warning: Unknown res!\n");
		break;
	}
	size = res_val*size;
	discrepancy = res_val*discrepancy;
	//camera sorting initialization
	multicamupdate(5);
	float startTime = curr_time();
	int leftPos, rightPos;
	float newTime = curr_time();
	int area = 0;
	int last = get_motor_position_counter(MOT_PICK);
	int alt = 0;
	motor(MOT_PICK,SORT_SPEED);
	//Sorting process
	
	
	motor(MOT_RIGHT,71);
	motor(MOT_LEFT,71);
	leftPos = gmpc(MOT_LEFT);
	rightPos = gmpc(MOT_RIGHT);
	while(startTime+time>=curr_time())	//Timekeeper
	{
		if((gmpc(MOT_LEFT)-leftPos)/CMtoBEMF>=1&&(gmpc(MOT_RIGHT)-rightPos)/CMtoBEMF>=1) // sketch
		{
			printf("newTime:%d\n",newTime);
			printf("curr time:%d\n",curr_time());
			if(newTime+2 < curr_time())
			{
				motor(MOT_RIGHT,50);
				motor(MOT_LEFT,49);
				
				newTime = curr_time();
				leftPos=gmpc(MOT_LEFT);
				rightPos=gmpc(MOT_RIGHT);
			}
		}
		else
		{
			if((gmpc(MOT_LEFT)-leftPos)/CMtoBEMF>=2)
			{
				motor(MOT_LEFT,0);
			}
			else
			{
				newTime = curr_time();
			}
			if((gmpc(MOT_RIGHT)-rightPos)/CMtoBEMF>=2)
			{
				motor(MOT_RIGHT,0);
			}
			else
			{
				newTime=curr_time();
			}
			printf("gmpc: Mot_left-leftPos = %d",(gmpc(MOT_LEFT)-leftPos)/CMtoBEMF);
			printf("gmpc: Mot_right-rightPos = %d",(gmpc(MOT_RIGHT)-rightPos)/CMtoBEMF);
			
		}
		
		
		//leftPos = get_motor_position(MOT_LEFT);
		//rightPos = get_motor_position(MOT_RIGHT);
		//failsafe
		if(lastTest+1<=curr_time())
		{
			
			if(alt == 1)
			{
				//bump_poms();
				//forward(2);
				alt = 0;
			}
			else
			{
				alt = 1;
				motor(MOT_LEFT,0);
				motor(MOT_RIGHT,0);
			}
			if(jamDist>(get_motor_position_counter(MOT_PICK)-last))
			{
				motor(MOT_PICK,-90);
				//shake(5);
				msleep(1000);
				motor(MOT_PICK,SORT_SPEED);
			}
			last = get_motor_position_counter(MOT_PICK);
			lastTest = curr_time();
			sweep_bump();
			msleep(20);
			sweep_default();
		}
		//actual sorting
		camera_update();
		area = get_object_area(mainColor,0);
		if(area>500)
		{
			printf("Seen Blob of Main color\n");
			if(area>=size-discrepancy&&area<=size+discrepancy)
			{
				motor(MOT_PICK,SORT_SPEED/4);
				sort_main();
				msleep(50);
				motor(MOT_PICK,SORT_SPEED);
				printf("sorted");
				//motor(MOT_PICK,0);
				//msleep(100);
				//sweep_bump();
				//motor(MOT_PICK,SORT_SPEED);
				//sweep_default();
			}
			else
			{
				printf("Blob failed specifications\n");
				sort_sec();
			}
		}
		else
		{
			sort_sec();/*
			if(mainColor == 0)
			area = get_object_area(1,0);
			else
			area = get_object_area(0,0);
			if(area>500)
			{
			printf("Seen blob of secondary color\n");
			if(area>=size-discrepancy&&area<=size+discrepancy)
			{
			//msleep(50);
			//motor(MOT_PICK,0);
			//msleep(200);
			//motor(MOT_PICK,SORT_SPEED);
			printf("sorted sec");
			}
			}*/
		}
	}
	motor(MOT_PICK,0);
	motor(MOT_LEFT,0);
	motor(MOT_RIGHT,0);
}
//side programs
#define s_SQUAREUP 101
#define s_RAWSORT 102
#define s_SWEEP 103
#define s_FORWARD 104

//main programs
#define s_START 1
#define s_CROSSFIELD 2
#define s_PILE1 3
#define s_PILE2 4
#define s_RETURNFIELD 5
#define s_DUMPPOMS 6
#define s_PILEALT 7

#define s_END 0

struct menuitem menu[]=
{
	{s_START,"start"},
	{s_CROSSFIELD,"crossfield"},
	{s_PILE1,"Pile 1"},
	{s_PILE2,"Pile 2"},
	{s_SQUAREUP,"squareup"},
	{s_SWEEP,"sweep"},
	{s_FORWARD,"forward"},
	{s_RAWSORT,"sorting"},
	{s_END,"END"}
	
};
void cam_display()
{
	graphics_open(80,60);
	int col, row;
	const unsigned char* ptr;
	while(!side_button())
	{
		camera_update();
		//printf("%3d,%3d,%3d\n",*ptr,*(ptr+1),*(ptr+2));//bgr
		int x,y;
		for(y=0;y<120;y+=2){
			const unsigned char* row = get_camera_frame_row(y);
			for(x=0;x<160;x+=2){
				ptr = row+(3*x);
				int r = *(ptr+2);
				int g = *(ptr+1);
				int b = *(ptr);
				//if (r > g*3/2+20 && r > b*3/2+20 && abs(b-g) < 20 && (r < 120))
				//graphics_pixel(x,y,255,0,0);
				//else
				graphics_pixel(x/2,y/2,r,g,b);
			}
		}
		graphics_update();
		msleep(200);
	}
	
	graphics_close();
}
int main()
{
	enable_servos();
	sort_sec();
	camera_open(CAM_RES);
	multicamupdate(5);
	sweep_default();
	set_servo_position(SERV_GRAB,929);
	Get_Mode();
	while(currstate!=s_END)
	{
		state(s_FORWARD)
		{
			release_poms();
			forward(100);
		}
		state(s_SWEEP)
		{
			sweep_default();
			msleep(50);
			sweep_out();
			msleep(150);
		}
		state(s_SQUAREUP)
		{
			squareup(10);
			next(s_END);
		}
		state(s_RAWSORT)
		{
			release_poms();
			//thread_start(thread_create(cam_display));
			//grab_poms();
			sort_main();
			sort_sec();
			//motor(MOT_LEFT,30);
			//motor(MOT_RIGHT,35);
			cam_sort(0,60,40,30,3);
			sweep_out();
			next(s_END);
		}
		state(s_START) // start, cross field, then pile1 and pile2, returnfield, dumpPoms and end
		{
			light_start(0);
			shut_down_in(119);
			release_poms();
			motor(MOT_LEFT,-70);
			motor(MOT_RIGHT,-70);
			msleep(1000);
			//motor(MOT_RIGHT,0);
			//motor(MOT_LEFT,0);
			forward(20);
			//set_servo_position(SERV_GRAB,1250);
			//msleep(300);
			//release_poms();
			left(6,0);
			forward(15);
			right(8,0);
			forward(15);
			printf("end of Crossfield");
			next(s_CROSSFIELD);
		}
		state(s_CROSSFIELD)
		{
			printf("start of Crossfield");
			//left(4,0);
			forward(10);
			grab_poms();
			motor(MOT_PICK,40);
			forward(30);
			motor(MOT_PICK,0);
			//right(4,0);
			//motor(MOT_PICK,-30);
			forward(104);
			next(s_PILEALT);
		}
		state(s_PILEALT)
		{
			left(176,ks/2);
			backward(40);
			cam_sort(0,50,25,15,2);
			backward(30);
			cam_sort(0,50,25,10,2);
			left(80,0);
			//backward(50);
			/*
			right(90,0);
			release_poms();
			forward(33);
			right(84,ks/2);
			forward(30);
			grab_poms();
			left(88,ks/2);
			backward(80);
			forward(20);
			left(88,ks/2);
			backward(30);
			cam_sort(0,50,25,30,3);*/
			next(s_PILE2);
		}
		state(s_PILE1)
		{
			left(-88,ks/2);
			//right(96,ks/2);
			backward(75);
			forward(40);
			left(-88,ks/2);
			backward(40);
			forward(10);
			left(88,ks/2);
			//backward(50);
			//motor(MOT_LEFT,60);
			//motor(MOT_RIGHT,63);
			//forward(20);
			cam_sort(0,50,25,30,2);
			release_poms();
			next(s_PILE2);
		}
		state(s_PILE2)
		{
			backward(70);
			forward(15);
			right(88,0);
			backward(40);
			release_poms();
			forward(65);
			//motor(MOT_PICK,-40);
			grab_poms();
			backward(80);
			forward(20);
			left(88,ks/2);
			//release_poms();
			//right(105,46);
			/*motor(MOT_LEFT,-70);
			motor(MOT_RIGHT,-70);
			msleep(3000);
			forward(2);
			left(20,0);
			forward(45);
			right(180,0);*/
			//motor(MOT_LEFT,40);
			//motor(MOT_RIGHT,55);
			/*backward(70);
			forward(20);
			left(-88,ks/2);
			backward(30);
			forward(10);
			left(88,ks/2);*/
			backward(40);
			cam_sort(0,50,25,30,2);
			//forward(240);
			/*left(135,0);
			forward(120);
			right(45,0);
			forward(30);
			right(90,0);
			forward(100);
			next(s_END);*/
			next(s_RETURNFIELD);
		}
		state(s_RETURNFIELD)
		{
			backward(80);
			forward(10);
			right(67,0);
			//backward(50);
			forward(180);
			right(88,0);
			next(s_DUMPPOMS);
		}
		state(s_DUMPPOMS)
		{
			sweep_out();
			msleep(150);
			sweep_out2();
			sweep_out();
			sweep_out2();
			sweep_out();
			next(s_END);
			now();
		}
		return 0;
	}
}
