#ifndef _FINALCREATE
#define _FINALCREATE
//required for buffering and scripting
#define WHEEL_DROP 1
#define CLIFF 10
#define BUMP 5
#define LEFT_BUMP 6
#define LEFT_BUMP 6
#define RIGHT_BUMP 7
#define BUTTON_ADVANCED 16
#define BUTTON_PLAY 17//TODO: finish all events.  p16 of create docs
#define SEN_0 18

//this is to get around kiss-c's lack of intelligence and lack of the inclusion of an ACTUAL WRITE_BYTE FUNCTION THAT WORKS ON BOTH THINGS
/*
#ifndef __IROBOT_CREATE_H__
//int NUMBYTES;
void serial_init()
{
}
void create_write_byte(int num)
{
	//NUMBYTES++;
}
#endif
*/

#define get_high_byte2(a) ((a)>>8)
#define get_low_byte2(a) ((a)&255)

#define create_write_int(integer) create_write_byte(get_high_byte2(integer));create_write_byte(get_low_byte2(integer))

//this is for just good old plain scripting
void create_wait_time(int time)//time is in deciseconds
{
	create_write_byte(155);
	create_write_byte(time);
}

/*
void create_special_connect(){
	serial_init();
	create_write_byte(128);
	create_write_byte(132);
	create_power_led(250,254);
	atexit(create_disconnect);
}*/

void create_wait_dist(int dist)//dist is in mm
{
	create_write_byte(156);
	create_write_int(dist);
}
void create_wait_angle(int angle)//degrees, negative = right
{
	create_write_byte(157);
	create_write_int(angle);
}
void create_wait_event(int event)//see #defines for possible answers.  Use 255-event for the inverse
{
	create_write_byte(158);
	create_write_byte(event);
}

void create_drive_direct_dist(int r_speed, int l_speed, int dist)
{
	create_write_byte(145);
	create_write_int(r_speed);
	create_write_int(l_speed);
	create_wait_dist(dist);
}
void create_drive_direct_left(int r_speed, int l_speed, int angle)
{
	create_write_byte(145);
	create_write_int(r_speed);
	create_write_int(l_speed);
	create_wait_angle(angle);
}
void create_drive_direct_right(int r_speed, int l_speed, int angle)
{
	create_write_byte(145);
	create_write_int(r_speed);
	create_write_int(l_speed);
	create_wait_angle(-angle);
}
void create_right(int angle, int radius, int speed)
{
	create_write_byte(137);
	create_write_int(speed);
	if (radius == 0){
		create_write_int(-1);
	}else{
		create_write_int(-radius);
	}
	create_wait_angle(-angle);
}
void create_left(int angle, int radius, int speed)
{
	create_write_byte(137);
	create_write_int(speed);
	if (radius == 0){
		create_write_int(1);
	}else{
		create_write_int(radius);
	}
	create_wait_angle(angle);
}
void create_forward(int dist, int speed)
{
	create_write_byte(145);
	create_write_int(speed);
	create_write_int(speed);
	create_wait_dist(dist);
}
void create_backward(int dist, int speed)
{
	create_write_byte(145);
	create_write_int(-speed);
	create_write_int(-speed);
	create_wait_dist(-dist);
}
void create_crash()
{
	create_write_byte(7);
}

void output_sen_0()
{
	create_write_byte(147);
	create_write_byte((0*1)+(0*2)+(1*4));
}

void stop_output()
{
	create_write_byte(147);
	create_write_byte(0);
}

void create_motors(int byte){
	create_write_byte(138);
	create_write_byte(byte);
	//1*(pin 23)+2*(pin 22)+4*pin(24)
	//so, pin 24 on = send 4
	//off = send 0
}

void create_send(){
	//gogo OI mode data!
	create_write_byte(142);
	create_write_byte(35);
	
}
void create_recieve(){
	
	char buffer[1];
	char *bptr = buffer;
	create_read_block(bptr,1);
	
}
// blocks program until create finishes
void create_block()
{
	create_stop();
	create_send();
	create_recieve();
}
void create_motor_slow(int speed)
{
	create_write_byte(144);
	create_write_byte(speed);
	create_write_byte(speed);
	create_write_byte(speed);
}
#endif
