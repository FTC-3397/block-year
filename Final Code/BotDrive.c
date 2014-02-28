#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S3,     HTSMUX,         sensorI2CCustom)
#pragma config(Motor,  motorA,          magLeft,       tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          magRight,      tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     LBoomMotor,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     RBoomMotor,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     frontRightMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     backRightMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     M4Motor,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     flagMotor,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     backLeftMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     frontLeftMotor, tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    camServo1,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    camServo2,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    hookServo,            tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "BotSystems.h"
#include "PolarJoystick.h"

typedef enum {STOP = 0, IN = 1, OUT = -1} Magazine;
typedef enum {FRONT = 0, BACK = 1, LEFT = 2, RIGHT = 3} Direction;

task Pull();

static float Y1, Y2, X1, X2;
static float factor;

static byte mag;
static byte dir;

static int localPower;

task main()
{
	initSystems();

	nVolume = 4;  // 4 = max volume

	factor = 1.28;
	mag = STOP;
	dir = FRONT;

	servo[hookServo] = 0;

	while(true)
	{
		getJoystickSettings(joystick);  //Try inside and outside the loop

		//-------------------------------------Holonomic------------------------------------------

		Y1 = /*(float)*/joystick.joy1_y1 / 1.28;
		Y2 = /*(float)*/joystick.joy1_y2 / 1.28;
		X1 = /*(float)*/joystick.joy1_x1 / 1.28;
		X2 = /*(float)*/joystick.joy1_x2 / 1.28;

		if(joy1Btn(2))
		{
			if(factor == 1.28)
				factor = .3906;
			else factor = 1.28;
		}

		if(joystick.joy1_TopHat == 0) dir = FRONT;
		if(joystick.joy1_TopHat == 4) dir = BACK;
		if(joystick.joy1_TopHat == 6) dir = LEFT;
		if(joystick.joy1_TopHat == 2) dir = RIGHT;

		if(dir == FRONT)
		{
			motor[frontRightMotor] = X1 - Y2 + X2;
			motor[backRightMotor] =  X1 - Y2 - X2;
			motor[frontLeftMotor] = X1 + Y2 + X2;
			motor[backLeftMotor] =  X1 + Y2 - X2;
		}
		else if(dir == BACK)
		{
			motor[frontRightMotor] = X1 + Y2 - X2;
			motor[backRightMotor] =  X1 + Y2 + X2;
			motor[frontLeftMotor] = X1 - Y2 - X2;
			motor[backLeftMotor] =  X1 - Y2 + X2;
		}
		else if(dir == RIGHT)
		{
			motor[frontRightMotor] = X1 - X2 + Y2;
			motor[backRightMotor] =  X1 - X2 - Y2;
			motor[frontLeftMotor] = X1 + X2 + Y2;
			motor[backLeftMotor] =  X1 + X2 - Y2;
		}
		else   //dir == LEFT
		{
			motor[frontRightMotor] = X1 + X2 - Y2;
			motor[backRightMotor] =  X1 + X2 + Y2;
			motor[frontLeftMotor] = X1 - X2 - Y2;
			motor[backLeftMotor] =  X1 - X2 + Y2;
		}

		//--------------------------------------Flag-----------------------------------------------

		if(joy1Btn(8))
			motor[flagMotor] = 100;
		else if(joy1Btn(7))
			motor[flagMotor] = -100;
		else motor[flagMotor] = 0;

		//---------------------------------------M4---------------------------------------------------

		//~20 encoder counts per degree of rotation

		if(joy2Btn(3))														//Button B pressed => FULL POWER
		{
			localPower = 9520;
			StartTask(Pull);
		}
		if(joy2Btn(4))														//Button Y pressed => medium high power
		{
			localPower = 7000;
			StartTask(Pull);
		}
		if(joy2Btn(1))														//Button x pressed => medium low power
		{
			localPower = 5000;
			StartTask(Pull);
		}
		if(joy2Btn(2))														//Button a pressed => low power
		{
			localPower = 3000;
			StartTask(Pull);
		}

		if(joy2Btn(8))															//Fires the servo hit - return when right trigger button pressed again
		{
			fire();
		}
		//----------------------------------------Boom----------------------------------------------

		motor[LBoomMotor] = joystick.joy2_y1 / -1.28;
		motor[RBoomMotor] = joystick.joy2_y1 / -1.28;

		//---------------------------------------Magazine-------------------------------------------

		if(joystick.joy2_y2 > 10 || joystick.joy2_y2 < -10)
		{
			mag = 4;
			motor[magLeft] = joystick.joy2_y2 / 1.28;
			motor[magRight] = joystick.joy2_y2 / 1.28;
			PlayTone(abs(joystick.joy2_y2 / 10) * (abs((int)joystick.joy2_x1 + 5 / 10)), 10);
		}
		else
		{
			motor[magLeft] = 0;
			motor [magRight] = 0;
		}

		//writeDebugStream("%d", mag);

		if(joy1Btn(6)) mag = IN;
		if(joy1Btn(5)) mag = OUT;
		if(joy1Btn(5) && joy1Btn(6)) mag = STOP;

		if(mag == IN)
		{
			motor[magLeft] = 100;
			motor[magRight] = 100;
			PlayTone(500, 10);
		}
		else if(mag == OUT)
		{
			motor[magLeft] = -100;
			motor[magRight] = -100;
			PlayTone(1000, 10);
		}
		else if(mag == STOP)
		{
			motor[magLeft] = 0;
			motor[magRight] = 0;
		}

		//---------------------------------------Hooks----------------------------------------------
		if(joystick.joy2_TopHat == 1)
		{
			servo[hookServo] = 230;
			PlaySound(soundBeepBeep);
		}
		//---------------------------------------Extras---------------------------------------------

		if(joy1Btn(10) || joy2Btn(10)) stopAllMotors();
		//PlayTone((rand() % (700-500)) + 500, 5);     //rand() % (max-min)) + min;

		wait1Msec(10);
	}
}

task Pull()
{
	pullBack(localPower);
	StopTask(Pull);
}
