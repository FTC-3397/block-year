#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S4, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     IRL,            sensorI2CCustom)
#pragma config(Sensor, S3,     IRR,            sensorI2CCustom)
#pragma config(Motor,  motorA,          magLeft,       tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          magRight,      tmotorNXT, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     backRightMotor, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     frontRightMotor, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     M4Motor,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     flagMotor,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     LBoomMotor,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     RBoomMotor,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     backLeftMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     frontLeftMotor, tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    camServo1,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    camServo2,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//#include "C:\Users\user\Documents\Robotics\13-14\Programming\Final Code\BotSystems.h"
//#include "F:\temp robotics files\2014-block-party-master\2014-block-party-master\Final Code\BotSystems.h"
#include "BotSystems.h"

#define STOP 0
#define IN 1
#define OUT -1

int Y1, Y2, X1, X2;
//float factor = .63;
//float factor = .1969;
float factor = .7874;  //limits to 100
byte mag = STOP;

task main()
{
	initSystems();

	while(true)
	{
		getJoystickSettings(joystick);  //Try inside and outside the loop

		//-------------------------------------Holonomic------------------------------------------

		Y1 = joystick.joy1_y1 / -1.28;
		Y2 = joystick.joy1_y2 / -1.28;
		X1 = joystick.joy1_x1 / 1.28;
		X2 = joystick.joy1_x2 / 1.28;

		motor[frontRightMotor] = -Y2 - X1 - X2;
		motor[backRightMotor] =  -Y2 - X1 + X2;
		motor[frontLeftMotor] = -Y2 + X1 + X2;
		motor[backLeftMotor] =  -Y2 + X1 - X2;

		//--------------------------------------Flag-----------------------------------------------

		if(joy1Btn(8))
			motor[flagMotor] = 100;
		else if(joy1Btn(7))
			motor[flagMotor] = -100;
		else motor[flagMotor] = 0;

		//---------------------------------------M4---------------------------------------------------

		if(joy2Btn(3))														//Button B pressed => FULL POWER!!!/3000
		{
			pullBack(3000);											//3000 = Pull back distance
		}
		if(joy2Btn(4))														//Button Y pressed => medium high power/2300
		{
			pullBack(2300);
		}
		if(joy2Btn(1))														//Button x pressed => medium low power/1500
		{
			pullBack(1500);
		}
		if(joy2Btn(2))														//Button a pressed => low power/1000
		{
			pullBack(1000);
		}
		//}
		if(joy2Btn(8))															//Fires the servo hit - return when right trigger button pressed again
		{
			fire();
		}
		//----------------------------------------Boom----------------------------------------------

		motor[LBoomMotor] = joystick.joy2_y1 * factor;
		motor[RBoomMotor] = joystick.joy2_y1 * factor;

		//---------------------------------------Magazine-------------------------------------------

		if(joy1Btn(6) || joy2Btn(6))
			mag = IN;
		if(joy1Btn(5) || joy2Btn(5))
			mag = OUT;
		if(joy1Btn(5) && joy1Btn(6) || joy2Btn(5) && joy2Btn(6))
			mag = STOP;

		if(mag == IN)
		{
			motor[magLeft] = 100;
			motor[magRight] = 100;
		}
		else if(mag == OUT)
		{
			motor[magLeft] = -100;
			motor[magRight] = -100;
		}
		else
		{
			motor[magLeft] = 0;
			motor[magRight] = 0;
		}
		//---------------------------------------Extras---------------------------------------------

		if(joy1Btn(10) || joy2Btn(10)) stopAllMotors();

		wait1Msec(100);
	}
}
