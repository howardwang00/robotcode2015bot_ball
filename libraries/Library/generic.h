//UTILITY
float bound(float num, float max)
{
	if (num > max)
	return max;
	else if (num < -max)
	return -max;
	else
	return num;
}
int in_range(int input, int wanted, int fudge)
{
	if (wanted+fudge >= input && wanted-fudge <= input)
	return 1;
	else
	return 0;
}
float ET_distance(int port){
    return ((sqrt(100.0/analog10(port)))-2.2);
}

#define WAIT(thing); while(!(thing)){msleep(10);}
#define gmpc(port) get_motor_position_counter(port)

#define DEGTORAD 0.017453292519943295769236907684886
//DEGTORAD = (PI*2)/360
#define RADTODEG 57.295779513082320876798154814105
#define pi 3.1415926535897932384626433832795

//LIGHT START
#define light_s() analog10(sensor)
void light_start(int sensor)
{
	int max = 0,min = 9999,curr = 0,avg = 0;
	display_clear();
	display_printf(0,0,"Max:");
	display_printf(0,1,"Min:");
	display_printf(0,2,"Curr:");
	display_printf(0,3,"avg:");
	while(!b_button() && !c_button())//INTERACTION BUTTON
	{
		curr = light_s();
		if (curr > max)
		{max = curr;}
		if (curr < min)
		{min = curr;}
		avg = (max+min)/2;
		display_printf(5,0,"%d   ",max);
		display_printf(5,1,"%d   ",min);
		display_printf(6,2,"%d   ",curr);
		display_printf(5,3,"%d   ",avg);
		if (curr > avg)
		{
			display_printf(10,5,"XX");
		}
		else
		{
			display_printf(10,5,"OO");
		}
		msleep(50);
	}
	display_clear();
	display_printf(0,4,"Prepared to begin: c to skip");
	while(light_s() > avg && !(c_button()))
	{
		msleep(50);
	}
}

//TIMING
long _start_time;
void start()
{
	_start_time = systime();
}
float curr_time()
{
    return (systime()-_start_time)/1000.0;
}
void now()
{
    printf("now %f\n",curr_time());
}

void wait_till(float t)
{
	now();
    msleep(((long)(t*1000))-curr_time());
}

//SERVOS
//servo_off(int) is replaced with the KIPR library function disable_servo(int)
void servo_set(int port,int end,float time)//,float increment)
{//position is from 0-2047
	float increment = .01;
	//printf("servo %d",port);
	float curr,start = get_servo_position(port);
	float i = ((end-start)/time)*increment;
	curr = start;
	if (start > end)
	{
		while(curr > end)
		{
			//printf("%f\n",curr);
			set_servo_position(port,curr);
			curr+=i;
			msleep((long)(increment*1000));
		}
	}
	else if (start < end)
	{
		while(curr < end)
		{
			//printf("%f\n",curr);
			set_servo_position(port,curr);
			curr+=i;
			msleep((long)(increment*1000));
		}
	}
	set_servo_position(port,end);
}

//camera stuff

int cam_area(int channel){//returns largest blob in channel, or 0 if none
	if (get_object_count(channel) > 0){
		return get_object_area(channel,0);
	}
	return 0;
}
void update_wait(){//updates the camera, and waits until success
	while(!camera_update()) msleep(1);
}


#define state(State) if (currstate == State)
#define next(State) currstate = State
int currstate;
