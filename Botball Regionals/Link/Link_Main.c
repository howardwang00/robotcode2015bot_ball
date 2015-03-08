// Created on Fri February 6 2015

#define LIGHT_SENSOR_PORT ? // light sensor port is currently unknown

void start(int light_sensor_port);

int main()
{
	start(LIGHT_SENSOR_PORT);
	return 0;
}

void start(int light_sensor_port)
{
	wait_for_light(light_sensor_port);
	shut_down_in(119.5); // shuts down in 119.5 seconds instead of 120 so the robot can have time to shut down
	enable_servos();
}
