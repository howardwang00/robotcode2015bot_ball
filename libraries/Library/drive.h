#ifndef _DRIVE_H_
#define _DRIVE_H_

//primary driving code
#define MOT_LEFT 0
#define MOT_RIGHT 1
#define PI 3.14159265358979
#define SPD 1000
#define SPDl 1000.
#define SPDr 1000. 
#define rdistmult (SPDr/SPDl)
// CHANGE KS FOR ROBOT
#define ks 7//distance from one wheel to another in cm
#define wheeldiameter 5.5 //this is in cm

#define CMtoBEMF (921/wheeldiameter/PI) //921 is how many backemf ticks there are in a full wheel, take the number of units per rotation, divide by circumference
#define LBUMP digital(14)
#define RBUMP digital(15) //left/right back bump sensors (used for square_back())

//fd and back definitions - to fix if code breaks
#define fd(MOT) motor(MOT, 100);
#define bk(MOT) motor(MOT, -100);

#define drive_off() off(MOT_RIGHT) ;off(MOT_LEFT)
#define drive(mL,mR) mav(MOT_LEFT,mL);mav(MOT_RIGHT,mR)

void square_back()
{
	int _A = 0,_B = 0;
	float time = seconds();//used for timeout
	bk(MOT_LEFT);
	bk(MOT_RIGHT);
	while((_A == 0 || _B == 0) && (seconds()-time < 10))//while the bump sensors are false & it has been less than 10 seconds
	// move backwards, if the bot is bumped, turn the motor off, and break out of the loop
	{
		if (LBUMP){//if the left sensor is pressed
			off(MOT_LEFT);//turn towards wall
			_A = 1;
			} else {
			bk(MOT_LEFT);//otherwise, approach the wall more
			_A = 0;
		}
		
		if (RBUMP){//if the right sensor is pressed
			off(MOT_RIGHT);//turn towards wall
			_B = 1;
			} else {
			bk(MOT_RIGHT);//otherwise, approach the wall more
			_B = 0;
		}
		msleep(1);//give other processes time to do things
	}
	drive_off();//turn both motors off at end
}

//same logic as square back, flipped back and forward
void square_forward()
{
	int _A = 0,_B = 0;
	float time = seconds();//used for timeout
	fd(MOT_LEFT);
	fd(MOT_RIGHT);
	while((_A == 0 || _B == 0) && (seconds()-time < 10))//while the bump sensors are false & it has been less than 10 seconds
	// move backwards, if the bot is bumped, turn the motor off, and break out of the loop
	{
		if (LBUMP){//if the left sensor is pressed
			off(MOT_LEFT);//turn towards wall
			_A = 1;
			} else {
			fd(MOT_LEFT);//otherwise, approach the wall more
			_A = 0;
		}
		
		if (RBUMP){//if the right sensor is pressed
			off(MOT_RIGHT);//turn towards wall
			_B = 1;
			} else {
			fd(MOT_RIGHT);//otherwise, approach the wall more
			_B = 0;
		}
		msleep(1);//give other processes time to do things
	}
	drive_off();//turn both motors off at end
}
void right(float degrees, float radius){//turn right a number of degrees with a certain radius
	int turnrspeed;
	long turnl=(long)round((((2*radius+ks)*CMtoBEMF)*PI)*degrees/360.);
	long turnr=(long)round((((2*radius-ks)*CMtoBEMF)*PI)*degrees/360.);
	if(turnl == 0l) return;
	turnrspeed = round((float)turnr/(float)turnl*SPD);
	mrp(MOT_LEFT, SPD,turnl);
	if(turnrspeed < 0) turnrspeed = -turnrspeed;
	if(turnrspeed < 50){
		turnrspeed = 0;
		turnr = 0l;
		off(MOT_RIGHT);
		}else{
		mrp(MOT_RIGHT,turnrspeed,turnr);
	}
	bmd(MOT_RIGHT);
	bmd(MOT_LEFT);
}
void left(float degrees, float radius){//turn left a number of degrees with a certain radius
	int turnlspeed;
	long turnl=(long)round((((2*radius-ks)*CMtoBEMF)*PI)*degrees/360.);
	long turnr=(long)round((((2*radius+ks)*CMtoBEMF)*PI)*degrees/360.);
	if(turnr == 0l) return;
	turnlspeed = round((float)turnl/(float)turnr*SPD);
	mrp(MOT_RIGHT, SPD,turnr);
	if(turnlspeed < 0) turnlspeed = -turnlspeed;
	if(turnlspeed < 50){
		turnlspeed = 0;
		turnl=0l;
		off(MOT_LEFT);
		}else{
		mrp(MOT_LEFT,turnlspeed,turnl);
	}
	bmd(MOT_LEFT);
	bmd(MOT_RIGHT);
}
void forward(float distance){//go forward a number of CM    NOT    backEMF counts
	if(distance < 0l){
		distance = -distance;
	}
	long newdist;
	newdist = distance*CMtoBEMF;//conversion ratio
	mrp(MOT_RIGHT,SPDr,newdist*rdistmult);
	mrp(MOT_LEFT,SPDl,newdist);
	bmd(MOT_RIGHT);
	bmd(MOT_LEFT);
}
void backward(float distance){//go backward a number of CM    NOT    backEMF counts
	if(distance < 0l){
		distance = -distance;
	}
	long newdist;
	newdist = distance*CMtoBEMF;
	mrp(MOT_RIGHT,SPDr,-newdist*rdistmult);
	mrp(MOT_LEFT,SPDl,-newdist);
	bmd(MOT_RIGHT);
	bmd(MOT_LEFT);
}
#endif
