#pragma config(Motor,  motorA,          motor1,        tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	eraseDisplay();
	nMotorEncoder[motor1] = 0;

	while(true)
	{
		nMotorEncoder[motor1] = 0;
		nxtDisplayCenteredBigTextLine(4, "%d", nMotorEncoder[motor1]);
		while(nNxtButtonPressed == 1)
		{
			motor[motor1] = 100;
			nxtDisplayCenteredBigTextLine(4, "%d", nMotorEncoder[motor1]);
		}
		while(nNxtButtonPressed == 2)
		{
			motor[motor1] = -100;
			nxtDisplayCenteredBigTextLine(4, "%d", nMotorEncoder[motor1]);
		}
		motor[motor1] = 0;
	}
}
