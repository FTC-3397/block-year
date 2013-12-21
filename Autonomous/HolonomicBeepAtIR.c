#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S2,     IRS,            sensorI2CCustom)
#pragma config(Sensor, S3,     IRL,            sensorI2CCustom)
#pragma config(Sensor, S4,     IRR,            sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     backLeft,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     frontLeft,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     backRight,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     frontRight,    tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Beep when the IR beacon reaches a "sweet spot" in front of an IR beacon

#include "hitechnic-irseeker-v2.h"
#include "JoystickDriver.c"

void holonomicBeepAtIR();
void trackIR();
void stopAllMotors();

int _dirACL;
int _dirACR;
int _dirACS;
int avgDir;
int acS1L, acS2L, acS3L, acS4L, acS5L;
int acS1R, acS2R, acS3R, acS4R, acS5R;
int acS1S, acS2S, acS3S, acS4S, acS5S;

tHTIRS2DSPMode _mode = DSP_1200;

task main()
{
	while(true)
	{
		getJoystickSettings(joystick);

		//holonomicStopAtIR();
		holonomicBeepAtIR();
		if(joy1Btn(2))
		{
			stopAllMotors();
			break;
		}
	}
}

void holonomicBeepAtIR()  //good zone: both dirs 5, both strengths in 3 from 60-90
{
	//-----------------------------IR Setup-------------------------------------------------
	HTIRS2setDSPMode(IRL, _mode);
	HTIRS2setDSPMode(IRR, _mode);
	HTIRS2setDSPMode(IRS, _mode);


	_dirACL = HTIRS2readACDir(IRL);
	_dirACR = HTIRS2readACDir(IRR);
	_dirACR = HTIRS2readACDir(IRS);


	HTIRS2readAllACStrength(IRL,  acS1L,  acS2L,  acS3L,  acS4L,  acS5L);
	HTIRS2readAllACStrength(IRR,  acS1R,  acS2R,  acS3R,  acS4R,  acS5R);
	HTIRS2readAllACStrength(IRS,  acS1S,  acS2S,  acS3S,  acS4S,  acS5S);


	//-----------------------------Moving the Bot--------------------------------------------
	motor[frontLeft] = 50;
	motor[frontRight] = 50;
	motor[backLeft] = -50;
	motor[backRight] = -50;
	if(_dirACR == 5 && acS3S > 40)
	{
		//stopAllMotors();
	  PlaySound(soundBeepBeep);
	}
}

void trackIR()
{
	//-----------------------------IR Setup-------------------------------------------------
	HTIRS2setDSPMode(IRL, _mode);
	HTIRS2setDSPMode(IRR, _mode);

	_dirACL = HTIRS2readACDir(IRL);
	_dirACR = HTIRS2readACDir(IRR);

	HTIRS2readAllACStrength(IRL,  acS1L,  acS2L,  acS3L,  acS4L,  acS5L);
	HTIRS2readAllACStrength(IRR,  acS1R,  acS2R,  acS3R,  acS4R,  acS5R);

	int temp = 0;

	for(int i = 0; i < 10; i++)
	{
		temp += _dirACL + _dirACR;
	}

	avgDir = temp / 20;

	//-----------------------------Moving the Bot--------------------------------------------
	if(avgDir < 5)
	{
		if(avgDir < 4)
		{
			motor[frontLeft] = -50;
			motor[frontRight] = 50;
			motor[backLeft] = 50;
			motor[backRight] = -50;
		}
		else  //avgDir == 4
		{
			motor[frontLeft] = 0;
			motor[frontRight] = 50;
			motor[backLeft] = -50;
			motor[backRight] = 0;
		}
	}
	else if(avgDir > 5)
	{
		if(avgDir > 6)
		{
			motor[frontLeft] = 50;
			motor[frontRight] = -50;
			motor[backLeft] = -50;
			motor[backRight] = 50;
		}
		else  //avgDir == 6
		{
			motor[frontLeft] = 50;
			motor[frontRight] = 0;
			motor[backLeft] = 0;
			motor[backRight] = -50;
		}
	}
	else  //avgDir == 5
	{
		motor[frontLeft] = 50;
		motor[frontRight] = 50;
		motor[backLeft] = -50;
		motor[backRight] = -50;
	}
}

void stopAllMotors()
{
	motor[frontLeft] = 0;
	motor[frontRight] = 0;
	motor[backLeft] = 0;
	motor[backRight] = 0;
}