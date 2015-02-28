
#ifndef _DRIVE_H_
#define _DRIVE_H_

#define gmpc(port) get_motor_position_counter(port)


//primary driving code
#define MOT_LEFT 0//Polyp edition!
#define MOT_RIGHT 3 
#define PI 3.14159265358979

#define SPD 100//turning
#define SPDl 100.//left forward
#define SPDr 94.//right forward
#define rdistmult 1.0
#define SPDlb 100.//left backward
#define SPDrb 100.//right backward
#define rdistmultb (SPDrb/SPDlb)
#define wheeldiameter 4.3
#define ks 13.4
#define CMtoBEMF (850/(PI*wheeldiameter))

void drive_off();
void clear_all_drive();
void drive(int mL,int mR);


void right(float degrees, float radius);
void left(float degrees, float radius);
void forward(float distance);
void multforward(float distance, float speedmult);
void backward(float distance);

#endif
