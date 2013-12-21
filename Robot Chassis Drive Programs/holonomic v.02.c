
#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     frontleftMotor, tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C1_2,     frontrightMotor, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     backleftMotor, tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C2_2,     backrightMotor, tmotorTetrix, PIDControl, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
0
------------0
|					 |0
|					 |
0	|					 |
------------
0
*/

//Left Joystick is joystick 1 (Y1,X1), and right joystick is joystick2 (Y2, X2)

int fleft,fright,bleft,bright;

void omniDrive();
#include "JoystickDriver.c"
task main()
{
	//eraseDisplay();
	//	nxtDisplayCenteredBigTextLine(4,"X %3d",avgX);
	while(true)
	{
		omniDrive();
	}

}
void omniDrive()
{

	getJoystickSettings(joystick);
	fleft  = (int) joystick.joy1_y2 / 1.28;
	fright = (int) joystick.joy1_y2 / 1.28;
	bleft = (int) joystick.joy1_x2 / 1.28;
	bright = (int) joystick.joy1_x2 / 1.28;
	/*if(left > 100) left = 100;
	if(left < 0)   left = 0;
	if(right > 100) right = 100;
	if(right < 0) 	right = 0;
	if(north > 100) north = 100;
	if(north < 0) north = 0;
	if(south > 100) south = 0;
	if(south < 0) south = 0;*/
	fleft = fleft - joystick.joy1_x1;
	fright = fright + joystick.joy1_x1;
	bleft = bleft - joystick.joy1_x1;
	bright = bright + joystick.joy1_x1;
	if(joystick.joy1_x1 == 0 && joystick.joy1_y2 == 0 && joystick.joy1_x2 == 0)
	{
		fleft = 0;
		fright = 0;
		bleft = 0;
		bright = 0;
	}

	if(joystick.joy1_x1 == 0 && joystick.joy1_y2 == 0 && joystick.joy1_x2 > 20)
	{
		fleft = -50;
		fright = 50;
		bleft = 50;
		bright = -50;
	}

	if(joystick.joy1_x1 == 0 && joystick.joy1_y2 == 0 && joystick.joy1_x2 < -20)
	{
		fleft = 50;
		fright = -50;
		bleft = -50;
		bright = 50;
	}

	if(joystick.joy1_x1 == 0 && joystick.joy1_y2 < -20 && joystick.joy1_x2 == 0)
	{
		fleft = -50;
		fright = 50;
		bleft = -50;
		bright = 50;
	}


	if(joystick.joy1_x1 == 0 && joystick.joy1_y2 > 20 && joystick.joy1_x2 == 0)
	{
		fleft = 50;
		fright = -50;
		bleft = 50;
		bright = -50;
	}


	if(joystick.joy1_x1 > 20 && joystick.joy1_y2 == 0 && joystick.joy1_x2 == 0)
	{
		fleft = 50;
		fright = 50;
		bleft = 50;
		bright = 50;
	}

		if(joystick.joy1_x1 < 20 && joystick.joy1_y2 == 0 && joystick.joy1_x2 == 0)
		{
			fleft = -50;
			fright = -50;
			bleft = -50;
			bright = -50;
		}

			motor[frontrightMotor] = fright;
			motor[frontleftMotor]  = fleft;
			motor[backrightMotor] = bright;
			motor[backleftMotor]  = bleft;
			wait1Msec(100);
		}
		/*
		while(true)
		{


		getJoystickSettings(joystick);  // Update Buttons and Joysticks

		armEncoder = nMotorEncoder[armMotor];
		liftEncoder = nMotorEncoder[liftMotor];





		int driveData = joystick.joy1_x2 / factor;
		motor[leftMotor] = joystick.joy1_y1 / factor + driveData;
		motor[rightMotor] =  joystick.joy1_y1 / factor - driveData;

		//motor[rightMotor] = joystick.joy1_y2 / factor;
		//motor[leftMotor] = joystick.joy1_y1 / factor;
		*/
