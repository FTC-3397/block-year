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

//Shoot when the IR beacon reaches a "sweet spot" in front of the bot

#include "..\Driver Suite\drivers\hitechnic-sensormux.h"
#include "..\Driver Suite\drivers\hitechnic-irseeker-v2.h"
#include "..\Driver Suite\drivers\lego-ultrasound.h"
#include "..\Driver Suite\drivers\hitechnic-accelerometer.h"
#include "JoystickDriver.c"  //remove?
#include "BotSystems.h"

//void holonomicBeepAtIR();
//void trackIR();
//void stopAllMotors();
static void updateSensors();
static void moveForward();
static void moveForwardFast();
static void strafeIR();
static void rotateIR();
static void approachIR(int d);
static void moveToRamp();
static void turnLeft();
static void turnRight();
static void strafeLeft();
static void strafeRight();

static int readAvgXaxis();
static int readAvgYaxis();

static int getAvgDir();
static int getAvgStr(int acSXR, int acSXL);
static int getAvgLeftStr();
static int getAvgRightStr();

static int _dirACL;
static int _dirACR;
static int acS1L, acS2L, acS3L, acS4L, acS5L;
static int acS1R, acS2R, acS3R, acS4R, acS5R;
static int avgStr,avgLeftStr, avgRightStr, avgDir, avgStr1, avgStr2, avgStr3, avgStr4, avgStr5;

static int x, y;

static int _x_axis, _y_axis, _z_axis;
static int avgDelay = 1;
static int numAvg = 15;

static int distance;

const tMUXSensor IRL = msensor_S3_1;
const tMUXSensor IRR = msensor_S3_2;
const tMUXSensor sonar = msensor_S3_4;
const tMUXSensor accel = msensor_S3_3;

//tHTIRS2DSPMode _mode = DSP_1200;

task main()
{
	waitForStart();
	//getJoystickSettings(joystick);
	//eraseDisplay();
	initSystems();
	/*while(true)
	{
		//moveForward();
		//eraseDisplay();
		updateSensors();
		avgDir = getAvgDir();
		avgStr1 = getAvgStr(acS1R, acS1L);
		avgStr2 = getAvgStr(acS2R, acS2L);
		avgStr3 = getAvgStr(acS3R, acS3L);
		avgStr4 = getAvgStr(acS4R, acS4L);
		avgStr5 = getAvgStr(acS3R, acS5L);
		//nxtDisplayCenteredTextLine(3, "%d", "%d", avgDir, avgStr);
		nxtDisplayCenteredTextLine(3, "%d", avgStr3);
		nxtDisplayCenteredTextLine(4, "%d", avgDir);
		//aimAtIR();
		//moveOut();
		x = readAvgXaxis();
		y = readAvgYaxis();
	}*/
	//moveOut();
	//strafeIR();
	//wait1Msec(1000);
	//rotateIR();
	//while(avgStr3 < 115)  moveForward();
	//stopAllMotors();
	pullBack(5000);
	fire();
	strafeLeft();
	wait1Msec(4000);
	moveForwardFast();
	wait1Msec(6000);
	stopAllMotors();
	//moveToRamp();

	//approachIR(4);
}

/*
Strafes until the IR crate appears
*/
static void strafeIR()
{
	//-----------------------------Setup-------------------------------------------------
	updateSensors();
	//pullBack(1500);      //load...
	ClearTimer(T1);
	//-----------------------------Moving the Bot--------------------------------------------

	while(true)
	{
		updateSensors();
		if(_dirACL == 6 && _dirACR == 5) /*stopAllMotors();*/ return;
		else if(avgLeftStr < 15 && avgRightStr < 15) strafeLeft();
		else if(avgLeftStr > avgRightStr) strafeLeft();
		else/*(avgLeftStr < avgRightStr)*/ strafeRight();
	}
	//stopAllMotors();
}

static void rotateIR()
{
	//-----------------------------Setup-------------------------------------------------
	updateSensors();
	//-----------------------------Moving the Bot--------------------------------------------

	while(true)
	{
		updateSensors();
		if(_dirACL == 5 && _dirACR == 5) /*stopAllMotors();*/ return;
		//if(avgLeftStr == avgRightStr) /*stopAllMotors();*/ return;
		else if(avgLeftStr < 15 && avgRightStr < 15) turnLeft();
		else if(avgLeftStr > avgRightStr) turnLeft();
		else/*(avgLeftStr < avgRightStr)*/ turnRight();
	}
	//stopAllMotors();
}

/*
Moves foward until d units of IR strength units has been reached (sector 3)
*/
static void approachIR(int d)
{
	updateSensors();

	/*int*/ distance = getAvgStr(acS3R, acS3L);
	int temp = distance - d;
	while(distance > temp)
	{
		updateSensors();
		moveForward();
		nxtDisplayCenteredBigTextLine(3,"%c", 'a');
		distance = getAvgStr(acS3R, acS3L);
	}
	stopAllMotors();
	//PlaySound(soundBeepBeep);
	//wait1Msec(500);
}

static void moveToRamp()
{
	while(USreadDist(sonar) != 255)
	{
		strafeLeft();
	}
	wait1Msec(3000);
	moveForward();
	wait1Msec(4000);

	while(readAvgYaxis() < 194)
	{
		strafeRight();
	}
	stopAllMotors();
}

static void moveForwardFast()
{
	motor[frontLeftMotor] = 100;
	motor[frontRightMotor] = -100;
	motor[backLeftMotor] = 100;
	motor[backRightMotor] = -100;
}

static void moveForward()
{
	motor[frontLeftMotor] = 40;
	motor[frontRightMotor] = -40;
	motor[backLeftMotor] = 40;
	motor[backRightMotor] = -40;
}

static void turnRight()
{
	motor[frontLeftMotor] = 20;
	motor[frontRightMotor] = 20;
	motor[backLeftMotor] = 20;
	motor[backRightMotor] = 20;
}

static void turnLeft()
{
	motor[frontLeftMotor] = -20;
	motor[frontRightMotor] = -20;
	motor[backLeftMotor] = -20;
	motor[backRightMotor] = -20;
}

static void strafeLeft()
{
	motor[frontLeftMotor] = -30;
	motor[frontRightMotor] = -30;
	motor[backLeftMotor] = 35;  //compensation
	motor[backRightMotor] = 30;
}

static void strafeRight()
{
	motor[frontLeftMotor] = 30;
	motor[frontRightMotor] = 30;
	motor[backLeftMotor] = -30;
	motor[backRightMotor] = -30;
}

/*
Gets the average direction from the two IR sensors
*/
static int getAvgDir()
{
	return (_dirACL + _dirACR) / 2;
}

/*
Returns average of all strengths
*/
static int getAvgStr()
{
	return getAvgLeftStr() + getAvgRightStr();
}

/*
Parameters: (right IR strength direction, left IR strength directoin
Gets the average of two IR strength directions, each from a different IR sensor
*/
static int getAvgStr(int acSXR, int acSXL)
{
	return (acSXR + acSXL) / 2;
}

/*
Returns average of all left strength sectors
*/
static int getAvgLeftStr()
{
	return (acS1L + acS2L + acS3L + acS4L + acS5L) / 5;
}

/*
Returns average of all right strength sectors
*/
static int getAvgRightStr()
{
	return (acS1R + acS2R + acS3R + acS4R + acS5R) / 5;
}

static int readAvgXaxis()                                   //eliminates noise of readings
{
	int avgX;
	for(int i = 0; i < numAvg; i++)
	{
		// Read all of the axes at once
		if (!HTACreadAllAxes(accel, _x_axis, _y_axis, _z_axis))
		{
			nxtDisplayTextLine(4, "ERROR!!");
			wait1Msec(avgDelay);
			//StopAllTasks();
		}
		avgX = (avgX + _x_axis) / 2;       //rolling average of x
	}
	return(avgX*.4444 + 100);
}

static int readAvgYaxis()                                   //eliminates noise of readings
{
	int avgY;
	for(int i = 0; i < numAvg; i++)
	{
		// Read all of the axes at once
		if (!HTACreadAllAxes(accel, _x_axis, _y_axis, _z_axis))
		{
			nxtDisplayTextLine(4, "ERROR!!");
			wait1Msec(avgDelay);
			//StopAllTasks();
		}
		avgY = (avgY + _y_axis) / 2;       //rolling average of x
	}
	return(abs(avgY*.4444-180));
}


/*
Updates sensor information
*/
static void updateSensors()
{
	//HTIRS2setDSPMode(IRL, _mode);
	//HTIRS2setDSPMode(IRR, _mode);

	_dirACL = HTIRS2readACDir(IRL);
	_dirACR = HTIRS2readACDir(IRR);

	avgStr = getAvgStr();
	avgLeftStr = getAvgLeftStr();
	avgRightStr = getAvgRightStr();

	HTIRS2readAllACStrength(IRL,  acS1L,  acS2L,  acS3L,  acS4L,  acS5L);
	HTIRS2readAllACStrength(IRR,  acS1R,  acS2R,  acS3R,  acS4R,  acS5R);
}