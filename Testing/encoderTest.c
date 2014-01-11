#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          motor1, tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          motor2, tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     backLeftMotor, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     frontLeftMotor, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     backRightMotor, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     frontRightMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     flagMotor,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    bumpServo,            tServoNone)
#pragma config(Servo,  srvo_S1_C4_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

int e;

task main()
{
	eraseDisplay();
	getJoystickSettings(joystick);
	nMotorEncoder[motor1] = 0;
	while(true)
	{
		bFloatDuringInactiveMotorPWM = true;
		e = nMotorEncoder[motor1];
		nxtDisplayCenteredBigTextLine(4, "%d", e);
		//bFloatDuringInactiveMotorPWM = false;

		motor[motor1] = joystick.joy1_y2 / 1.27;

	}
}
