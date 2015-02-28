// Created on Thu Jun 6 2013
/*
*
* AS OF 3142014, this is only a test file. Use to recycle code, don't run.
*
*
*
*
*/

#define COL_GREEN 0
//#include "./generic.h"
//#include "./drive.h"

//radians per pixel- they're square pixels though, so fovx==fovy
#define fovx ((20*DEGTORAD)/mdptx)
#define fovy ((15*DEGTORAD)/mdpty)

#define mdptx 160
#define mdpty 120
#define CAMANGLE (ang*DEGTORAD)
#define OFFSET 10
#define HEIGHT (9.5-1.2)//camera center minus tribble center

#ifdef OK
int main()
{
	double ang = 15.9;
	//forward(10);
	camera_open(MED_RES);
	while(1){
		if(a_button()){
			ang -= .05;
			printf("\n%f\n",ang);
			WAIT(!a_button());
		}
		if(b_button()){
			ang += .05;
			printf("\n%f\n",ang);
			WAIT(!b_button());
		}
		update_wait();
		if (cam_area(COL_GREEN) > 50){
			int x,y;
			
			point2 mcenter;
			mcenter = get_object_center(COL_GREEN,0);
			printf("x %d y %d a %d\n", mcenter.x, mcenter.y,cam_area(COL_GREEN));
			x=mcenter.x;
			y=mcenter.y;
			
			//find the angles
			double xangle = (mdptx-x)*fovx;
			double yangle = (mdpty-y)*fovy+CAMANGLE; //CAMANGLE = how much the camera is angled down, but it's also upsidedown.
			printf("xa %f ya %f\n", xangle,yangle);

			//double mult = HEIGHT/sin(-yangle);
			double xx,yy;
			yy = HEIGHT*tan(pi/2-yangle);//offset to handle camera vs watned location difference
			xx = sin(xangle)*yy;
			xx -= 4;
			yy -= 15;//make relative to claw position
			printf("x %f y %f\n", xx, yy);

			//now, x and y are relative to the robot's (x,y)
			//double angle = atan(x/y);
			//(x-r)^2+y^2=r^2, solve for r.
			//distance from (x,y) to (r,0) equals distance from (0,0) to (r,0)
			
			if (x != 0){
				double radius = (xx*xx+yy*yy)/(2*xx);
				double angle = atan(yy/(radius-xx))*RADTODEG;
					if (radius < 0) radius = -radius;
				printf("r %f a %f\n", radius, angle);
			}
		}
	}
	printf("Got here, test complete\n");
	return 0;
}

void rightish(double radius){//turn right
	int turnrspeed;
	long turnl=(long)round((((2*radius+ks)*CMtoBEMF)*PI));
	long turnr=(long)round((((2*radius-ks)*CMtoBEMF)*PI));
	if(turnl == 0l) return;
	turnrspeed = round((float)turnr/(float)turnl*SPD);
	mav(MOT_LEFT, SPD);
	mav(MOT_RIGHT,turnrspeed);
}
void leftish(double radius){//turn right
	int turnlspeed;
	long turnr=(long)round((((2*radius+ks)*CMtoBEMF)*PI));
	long turnl=(long)round((((2*radius-ks)*CMtoBEMF)*PI));
	if(turnl == 0l) return;
	turnlspeed = round((float)turnr/(float)turnl*SPD);
	mav(MOT_RIGHT, SPD);
	mav(MOT_LEFT,turnlspeed);
}
#endif
