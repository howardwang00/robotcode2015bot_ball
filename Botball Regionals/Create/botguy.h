// Created on Sat April 11 2015

// Replace FILE with your file's name
#ifndef _FILE_H_
#define _FILE_H_




int create_track_botguy()
{
	int area;
	float time = curr_time();
	while(time + 3 > curr_time())
	{
		printf("Before Camera Update");
		camera_update();
		printf("After Camera Update");
		area = get_object_area(RED,0);
		if (area > 500)
		{
			printf("Seen Blob of Red color\n");
			return RED;
		}
		area = get_object_area(GREEN,0);
		if (area > 500)
		{
			printf("Seen Blob of Green color\n");
			return GREEN;
		}
	}
	printf("Saw nothing :(((((((( !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	return NOTHING;
}

void if_red() {
	
}

void if_green() {
	
}

void backup() {
	
}




#endif
