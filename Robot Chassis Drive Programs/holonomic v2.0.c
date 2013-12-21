#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     backLeftMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     frontLeftMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     backRightMotor, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     frontRightMotor, tmotorTetrix, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Left Joystick is joystick 1 (Y1,X1), and right joystick is joystick2 (Y2, X2)

int Y1, Y2, X1, X2;

void omniDrive();
void stopAllMotors();

int bumpPos;

#include "JoystickDriver.c"
task main()
{
	//servoChangeRate[bumpServo] = 0;
	//bumpPos = 130;
	//eraseDisplay();
	//	nxtDisplayCenteredBigTextLine(4,"X %3d",avgX);
	while(true)
	{
		omniDrive();
	}
}
void omniDrive()
{
  //PlayImmediateTone(abs(Y1 + Y2 + X1 + X2 * 30), 50);
	getJoystickSettings(joystick);

	//bumpPos = 130;

	Y1 = joystick.joy1_y1 / -1.28;
	Y2 = joystick.joy1_y2 / -1.28;
	X1 = joystick.joy1_x1 / 1.28;
	X2 = joystick.joy1_x2 / 1.28;

	motor[frontRightMotor] = -Y2 - X1 - X2;
	motor[backRightMotor] =  -Y2 - X1 + X2;
	motor[frontLeftMotor] = -Y2 + X1 + X2;
	motor[backLeftMotor] =  -Y2 + X1 - X2;

  /*if(joy1Btn(8))
  	motor[flagMotor] = 100;
  else if(joy1Btn(7))
  	motor[flagMotor] = -100;
  else motor[flagMotor] = 0;

  if(joy1Btn(2)) stopAllMotors();

  if(joy1Btn(3)) bumpPos = 255;

  servo[bumpServo] = bumpPos;*/

	wait1Msec(100);
}

void stopAllMotors()
{
	motor[frontLeftMotor] = 0;
	motor[frontRightMotor] = 0;
	motor[backLeftMotor] = 0;
	motor[backRightMotor] = 0;
	//motor[flagMotor] = 0;
}
