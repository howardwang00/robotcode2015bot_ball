#ifndef _FINALCREATESCRIPTING
#define _FINALCREATESCRIPTING

#define get_high_byte2(a) ((a)>>8)
#define get_low_byte2(a) ((a)&255)

int BYTES[120], curr_byte = 0;
void init_script()
{
    int i;
    curr_byte = 0;
    for(i = 0;i < 120;i++)
    BYTES[i] = -1;
}
void serial_byte(int byte)
{
    BYTES[curr_byte] = byte;
    curr_byte++;
}

void serial_int(int integer)
{
    BYTES[curr_byte] = get_high_byte2(integer);
    curr_byte++;
    BYTES[curr_byte] = get_low_byte2(integer);
    curr_byte++;
}
void run_script()
{
    int i = 0;
    if (curr_byte > 100)
      {            
        printf("ERROR: TOO LARGE!");
    }
    else
      {
        create_write_byte(152);
        create_write_byte(curr_byte);
        while(i < curr_byte)
          {
            create_write_byte(BYTES[i]);
            printf("%d\n",BYTES[i]);
            i++;
        }
        printf("%d total\n",curr_byte);
    }
    create_write_byte(153);
}
void process_script()//gets script ready to be run with begin_script
{
    int i = 0;
    if (curr_byte > 100)
      {            
        printf("ERROR: TOO LARGE!");
    }
    else
      {
        create_write_byte(152);
        create_write_byte(curr_byte);
        while(i < curr_byte)
          {
            create_write_byte(BYTES[i]);
            printf("%d\n",BYTES[i]);
            i++;
        }
        printf("%d total\n",curr_byte);
    }
}
void begin_script()//will run the script- NOTE: must run process_script first!!!
{
    create_write_byte(153);
}


void restart_script()
{
    serial_byte(153);
}
void wait_time(int time)//time is in deciseconds
{
    serial_byte(155);
    serial_byte(time);
}
void wait_dist(int dist)//dist is in mm
{
    serial_byte(156);
    serial_int(dist);
}
void wait_angle(int angle)//degrees, negative = right
{
    serial_byte(157);
    serial_int(angle);
}
void wait_event(int event)//see #defines for possible answers.  Use 255-event for the inverse
{
    serial_byte(158);
    serial_byte(event);
}
void stop()
{
    serial_byte(145);
    serial_byte(0);
    serial_byte(0);
    serial_byte(0);
    serial_byte(0);
}
void drive_direct(int r_speed, int l_speed)
{
    serial_byte(145);
    serial_int(r_speed);
    serial_int(l_speed);
}
void drive_direct_dist(int r_speed, int l_speed, int dist)
{
    serial_byte(145);
    serial_int(r_speed);
    serial_int(l_speed);
    wait_dist(dist);
}
void drive_direct_left(int r_speed, int l_speed, int angle)
{
    serial_byte(145);
    serial_int(r_speed);
    serial_int(l_speed);
    wait_angle(angle);
}
void drive_direct_right(int r_speed, int l_speed, int angle)
{
    serial_byte(145);
    serial_int(r_speed);
    serial_int(l_speed);
    wait_angle(-angle);
}
void turn_right(int angle, int radius, int speed)
{
    serial_byte(137);
    serial_int(speed);
    serial_int(-radius);
    wait_angle(-angle);
}
void turn_left(int angle, int radius, int speed)
{
    serial_byte(137);
    serial_int(speed);
    serial_int(radius);
    wait_angle(angle);
}
void cforward(int dist, int speed)
{
    serial_byte(145);
    serial_int(speed);
    serial_int(speed);
    wait_dist(dist);
}
void cbackward(int dist, int speed)
{
    serial_byte(145);
    serial_int(-speed);
    serial_int(-speed);
    wait_dist(-dist);
}


//Sets the PWM signal for the three low side drivers (128 = 100%).  pwm2 is pin 24, pwm1 pin 23 and pwm0 pin 22
void pwm_low_side_drivers(int pwm2, int pwm1, int pwm0)
{
    //CREATE_BUSY;
    serial_byte(144);
    serial_byte(pwm2);
    serial_byte(pwm1);
    serial_byte(pwm0);
    //CREATE_FREE;
}

//Turns on and off the signal for the three low side drivers (128 = 100%).  pwm2 is pin 24, pwm1 pin 23 and pwm0 pin 22
//A 0 or 1 should be given for each of the drivers to turn them off or on.
void low_side_drivers(int pwm2, int pwm1, int pwm0)
{
    //CREATE_BUSY;
    serial_byte(138);
    serial_byte(4*pwm2+2*pwm1+pwm0);
    //CREATE_FREE;
}

#endif
