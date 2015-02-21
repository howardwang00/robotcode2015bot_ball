/*
void line_squareup(double srad, double lrad, double sensor_angle){
	//srad is distance from wheel to close sensor lrad is distance to far sensor
	//angle is angle between sensors
	
	int lsens = analog(1);
	int rsens = analog(0);
	
	double turn_angle = 0;
	double extra_turn = 0;
	
	int turn_motor = -1;
	
	int dark = 800;//test this and change it to be correct
	
	while(lsens >  dark && rsens > dark ) {
		motor(MOT_LEFT,50);
		motor(MOT_RIGHT,50);
		//move forward
		lsens = analog(1);
		rsens = analog(0);
		clear_motor_position_counter(MOT_RIGHT);
		clear_motor_position_counter(MOT_LEFT)
		if (lsens > dark){
			while(rsens < dark ) {
				printf("extra turn:%d\n",extra_turn);
				lsens = analog(1);
				rsens = analog(0);
				motor(MOT_RIGHT,50);
				mav(MOT_LEFT,0);
				//turn left by moving right forward
				turn_angle = sensor_angle - (CMtoBEMF * get_motor_position_counter(MOT_RIGHT))/ks;
				extra_turn = turn_angle + (-2 * atan((sqrt(41-40*cos(turn_angle))-5*sin(turn_angle))/(4-5*cos(turn_angle)));
				//values based of of srad and lrad using wolfram alpha i dont know if the link can do all the math
				//srad is 12, lrad is 15
				turn_direction = MOT_RIGHT;
			}
			
			
		}
		if (rsens > dark){
			while(lsens < dark ) {
				lsens = analog(1);
				rsens = analog(0);
				motor(MOT_LEFT,50);
				mav(MOT_RIGHT,0);
				//turn right by moving left forward
				turn_angle = sensor_angle - (CMtoBEMF * get_motor_position_counter(MOT_LEFT))/ks;
				extra_turn = turn_angle + (-2 * atan((sqrt(41-40*cos(turn_angle))-5*sin(turn_angle))/(4-5*cos(turn_angle)));
				//values based of of srad and lrad using wolfram alpha i dont know if the link can do all the math
				//srad is 12, lrad is 15
				//for new values equation is(srad/lrad)*cos(a)=cos(a+turn_angle) a+turn_angle=extra_turn
				turn_direction = MOT_LEFT;
			}
			
		}
	}
	//turn extra
	mrp(turn_direction,50,(extra_turn * ks)/CMtoBEMF);
	while(lsens <  dark && rsens < dark ) {
		lsens = analog(1);
		rsens = analog(0);
		motor(MOT_LEFT,-50);
		motor(MOT_RIGHT,-50);
		//move backward
		//we could change this to forward to have it square up on the far side of the line.
	}
}*/
