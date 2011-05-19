/*
*	Function:		moto_left_mototr(unsigned char increase,unsigned char panic)
*	Author(s):		Reza Moussavi, Rahwa Bahta
*	Description:	To incease/decrease panic/normal the left motor
*/
void moto_left_motor(unsigned char increase,unsigned char panic){
	leftPulse = increase?leftMotorLimitIncrease(leftPulse, panic?PANIC_STEP:NORMAL_STEP):leftMotorLimitDecrease(leftPulse, panic?PANIC_STEP:NORMAL_STEP);
	#ifdef ARDUINO
		escLeft.writeMicroseconds(leftPulse);
	#elif defined PC
		analogWrite(LEFT_MOTOR, leftPulse);
	#endif
		PRINT_STRING("Increasing left motor pulse");
		PRINT_NEW_LINE;
}

/*
*	Function:		moto_right_mototr(unsigned char increase,unsigned char panic)
*	Author(s):		Reza Moussavi, Rahwa Bahta
*	Description:	To incease/decrease panic/normal the right motor
*/
void moto_right_motor(unsigned char increase,unsigned char panic){
	rightPulse = increase?rightMotorLimitIncrease(rightPulse, panic?PANIC_STEP:NORMAL_STEP):rightMotorLimitDecrease(rightPulse, panic?PANIC_STEP:NORMAL_STEP);
	#ifdef ARDUINO
		escRight.writeMicroseconds(rightPulse);
	#elif defined PC
		analogWrite(RIGHT_MOTOR, rightPulse);
	#endif
		PRINT_STRING("Increasing right motor pulse");
		PRINT_NEW_LINE;
}

/*
*	Function:		moto_front_mototr(unsigned char increase,unsigned char panic)
*	Author(s):		Reza Moussavi, Rahwa Bahta
*	Description:	To incease/decrease panic/normal the front motor
*/
void moto_front_motor(unsigned char increase,unsigned char panic){
	frontPulse = increase?frontMotorLimitIncrease(frontPulse, panic?PANIC_STEP:NORMAL_STEP):frontMotorLimitDecrease(frontPulse, panic?PANIC_STEP:NORMAL_STEP);
	#ifdef ARDUINO
		escFront.writeMicroseconds(frontPulse);
	#elif defined PC
		analogWrite(FRONT_MOTOR, frontPulse);
	#endif
		PRINT_STRING("Increasing front motor pulse");
		PRINT_NEW_LINE;
}

/*
*	Function:		moto_rear_mototr(unsigned char increase,unsigned char panic)
*	Author(s):		Reza Moussavi, Rahwa Bahta
*	Description:	To incease/decrease panic/normal the rear motor
*/
void moto_rear_motor(unsigned char increase,unsigned char panic){
	rearPulse = increase?rearMotorLimitIncrease(rearPulse, panic?PANIC_STEP:NORMAL_STEP):rearMotorLimitDecrease(rearPulse, panic?PANIC_STEP:NORMAL_STEP);
	#ifdef ARDUINO
		escRear.writeMicroseconds(rearPulse);
	#elif defined PC
		analogWrite(REAR_MOTOR, rearPulse);
	#endif
		PRINT_STRING("Increasing rear motor pulse");
		PRINT_NEW_LINE;
}




