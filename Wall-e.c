#include <stdio.h>

void forward(int, int);
void backward(int, int);
void turnleft(int, int);
void turnright(int, int);
void opencubewall();
void closecubewall();
void pulleyup(int);
void pulleydown(int);
void tiltdown();
void tiltup();

// Sensor ports
#define START_LIGHT_PORT 0

// Servo ports
#define CUBE_WALL_PORT 2

// Motor ports
#define LEFT_MOTOR 2
#define RIGHT_MOTOR 1
#define PULLEY_MOTOR 3
#define TILT_MOTOR 0

// Other
#define DIAMETER 1000
#define PI 3.141592653589793238462643385027


/*
This program is meant to provide a framework as well basic mobility functions for the Lego robot. This program will refer to the Lego by his name, Wall-E.
*/
int main()
{
	//start right ski 2.75 inches from the side wall
	//
	//
	//Waiting to start	
	
	//wait_for_light(START_LIGHT_PORT);
	shut_down_in(120);
	// 3700 3700 3700 3700 3700
	//
	//Game tasks
	//
	//Drive forward to wall
	backward(400, 1000);

	forward(5600, 1000);
	backward(100, 500);
	
	//Get orange cubes
	pulleyup(4000);
	turnleft(82, 300);
	opencubewall();
	forward(2000, 500);
	backward(450, 500);
	pulleydown(400);
	msleep(500);
	turnright(40, 500);
	msleep(500);
	closecubewall();
	msleep(500);
	//edit
	
	//Upper storage area
	turnleft(95, 500);
	forward(2300, 1000);
	pulleydown(3600);
	turnleft(90, 500);
	forward(1800, 1000);
	tiltdown();
	msleep(2000);
	opencubewall();
	
}

/*
This function takes two ints.
dist is the distance that Wall-E will move in ticks.
speed is the speed at which Wall-E will move in ticks/s. speed is in the interval, [0, 1000].
*/
void forward(int dist, int speed)
{
	int rightspeed = speed;
	int leftspeed = rightspeed * .98;
	int initdist = 100;
	move_relative_position(LEFT_MOTOR, leftspeed, dist);
	move_relative_position(RIGHT_MOTOR, rightspeed, -1 * dist); //This is negative b/c the motor will be upside down
	while(!get_motor_done(LEFT_MOTOR) && !get_motor_done(RIGHT_MOTOR))
		msleep(10);
	off(LEFT_MOTOR);    // Don't use ao() because the pulley motor needs to stay on to freeze
	off(RIGHT_MOTOR);
}

/*
This function takes two ints.
dist is the distance that Wall-E will move in ticks.
speed is the speed at which Wall-E will move in ticks/s. speed is in the interval, [0, 1000].
*/
void backward(int dist, int speed)
{
	int rightspeed = speed;
	int leftspeed = rightspeed * .92;
	move_relative_position(LEFT_MOTOR, leftspeed, -1 * dist);
	move_relative_position(RIGHT_MOTOR, rightspeed, dist); //This is negative b/c the motor will be upside down
	while(!get_motor_done(LEFT_MOTOR) || !get_motor_done(RIGHT_MOTOR))
		msleep(10);
	off(LEFT_MOTOR);
	off(RIGHT_MOTOR);
}

/*
This function takes two ints.
angle is the number of degrees that Wall-E will turn.
speed is the speed at which Wall-E will move in tick/s. speed is in the interval, [0, 1000].
*/
void turnright(int angle, int speed)
{
	int ticks;
	angle -= 30;
	double alpha = /*5.7777777777777777777777777777779*/ 1;
	
	ticks = (int)(alpha * (angle * (PI / 180)) * (DIAMETER / 2));
	
	move_relative_position(RIGHT_MOTOR, speed, ticks);
	move_relative_position(LEFT_MOTOR, speed, ticks);
	while(!get_motor_done(RIGHT_MOTOR) && !get_motor_done(LEFT_MOTOR))
		msleep(10);
	off(LEFT_MOTOR);
	off(RIGHT_MOTOR);
}

/*
This function takes two ints.
angle is the number of degrees that Wall-E will turn.
speed is the speed at which Wall-E will move in tick/s. speed is in the interval, [0, 1000].
*/
void turnleft(int angle, int speed)
{
	int ticks;
	angle -= 30;
	double alpha = /*5.9777777777777777777777777777779*/ 1;
	
	ticks = (int)(alpha * (angle * (PI / 180)) * -(DIAMETER / 2));
	
	move_relative_position(LEFT_MOTOR, -1 * speed, ticks);
	//move_relative_position(RIGHT_MOTOR, (int)(.01 * speed), ticks);
	move_relative_position(RIGHT_MOTOR, -1 * speed, ticks);
	while(!get_motor_done(LEFT_MOTOR) && !get_motor_done(RIGHT_MOTOR))
		msleep(10);
	off(LEFT_MOTOR);
	off(RIGHT_MOTOR);
}

void opencubewall()
{
	set_servo_position(CUBE_WALL_PORT, 2000);
	enable_servo(CUBE_WALL_PORT);
	msleep(1500);
}

void closecubewall()
{
	set_servo_position(CUBE_WALL_PORT, 0);
	enable_servo(CUBE_WALL_PORT);
	msleep(1500);
}

void pulleydown(int dist)
{
	move_relative_position(PULLEY_MOTOR, 400, dist);
	block_motor_done(PULLEY_MOTOR);
	off(PULLEY_MOTOR);
}

void pulleyup(int dist)
{
    move_relative_position(PULLEY_MOTOR, 400, -1 * dist);
	block_motor_done(PULLEY_MOTOR);
	freeze(PULLEY_MOTOR);
}

void tiltdown()
{
	move_relative_position(TILT_MOTOR, 200, -250);
	block_motor_done(TILT_MOTOR);
	off(TILT_MOTOR);
}

void tiltup()
{
	move_relative_position(TILT_MOTOR, 200, 250);
	block_motor_done(TILT_MOTOR);
	off(TILT_MOTOR);
}


