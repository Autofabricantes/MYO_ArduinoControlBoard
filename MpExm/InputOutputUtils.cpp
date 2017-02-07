#include "InputOutputUtils.h"

/******************************************************************************/
/* INITIALIZATION INPUT METHODS                                               */
/******************************************************************************/

void InputOutputUtils::initializeInputElements() {

	logger.debug("InputOutputUtils - initializeInputElements (50segs aprox.)\n");

	myowareSensorController1 = MyoControl(PIN_INPUT_MYOWARE_SENSOR_1);
	myowareSensorController2 = MyoControl(PIN_INPUT_MYOWARE_SENSOR_2);
  
	delay(500);

	logger.info("InputOutputUtils - initializeInputElements - Calibrate myoware Sensor 1\n");
	myowareSensorController1.calibration();
	logger.info("InputOutputUtils - initializeInputElements - Calibrate myoware Sensor 2\n");
	myowareSensorController2.calibration();
	
	//test.testInitializeLedStripe();

}

void InputOutputUtils::resetInputElements() {

	logger.debug("InputOutputUtils - resetInputElements\n");

	myowareSensorController1.calibration();
	myowareSensorController2.calibration();

}

/******************************************************************************/
/* INITIALIZATION OUTPUT METHODS                                              */
/******************************************************************************/

void InputOutputUtils::initializeOutputElements() {


	logger.info("InputOutputUtils - initializeOutputElements\n");

	// Initialize motors pinout
	pinMode(MUX_A, OUTPUT);
	pinMode(MUX_B, OUTPUT);
	pinMode(MUX_C, OUTPUT);
  
	// Initialize motors pinout
	pinMode(PIN_OUTPUT_MOTOR_MITTEN_PWM, OUTPUT);
	pinMode(PIN_OUTPUT_MOTOR_MITTEN, OUTPUT);
	pinMode(PIN_OUTPUT_MOTOR_FOREFINGER_PWM, OUTPUT);
	pinMode(PIN_OUTPUT_MOTOR_FOREFINGER, OUTPUT);
	pinMode(PIN_OUTPUT_MOTOR_THUMB_PWM, OUTPUT);
	pinMode(PIN_OUTPUT_MOTOR_THUMB, OUTPUT);

	if(getMittenPosition() == CLOSE){
		logger.info("InputOutputUtils - Open mitten\n");
		motorControl(MITTEN,OPEN,100);
		delay(1000);
	}

	if(getForefingerPosition() == CLOSE){
		logger.info("InputOutputUtils - Open forefinger\n");
		motorControl(FOREFINGER,OPEN,TEST_SPEED);
		delay(1000);
	}

	if(getThumbPosition() == CLOSE){
		logger.info("InputOutputUtils - Open thumb\n");
		motorControl(THUMB,OPEN,TEST_SPEED);
		delay(1000);
	}
	
	//currentState.setCurrentState(STATE_INACTIVE);
	
  //test.testOutputWithLedStripe(0,0,0);
	//delay(2000);
	//test.testOutputWithLedStripe(0,255,0);

}

void InputOutputUtils::resetOutputElements() {

	logger.debug("InputOutputUtils - resetOutputElements\n");

	initializeOutputElements();

}


/******************************************************************************/
/* FINGERS POSITION                                                           */
/******************************************************************************/

int InputOutputUtils::getMittenPosition() {

	//TODO: What happens if finger position is diferent to current position?
	// Tenedremos que revisar en qué posicion se encuentar el dedo realmente para 
	// restaurar la posicion si es necesario.
	int mittenPosition = currentState.getMittenPosition();

	logger.info("InputOutputUtils - getMittenPosition - Mitten position: %i\n", mittenPosition);

	return mittenPosition;

}

int InputOutputUtils::getForefingerPosition() {

	// TODO: What happens if finger position is diferent to current position?
	// Tenedremos que revisar en qué posicion se encuentar el dedo realmente para 
	// restaurar la posicion si es necesario.
	int forefingerPosition = currentState.getForefingerPosition();

	logger.debug("InputOutputUtils - getForefingerPosition - Forefinger position: %i\n", forefingerPosition);

	return forefingerPosition;
}

int InputOutputUtils::getThumbPosition() {

	//TODO: What happens if finger position is diferent to current position?
	// Tenedremos que revisar en qué posicion se encuentar el dedo realmente para 
	// restaurar la posicion si es necesario.
	int thumbPosition = currentState.getThumbPosition();

	logger.debug("getThumbPosition - Thumb position: %i\n", thumbPosition);

	return thumbPosition;

}

/******************************************************************************/
/* TRANSITIONS                                                                */
/******************************************************************************/

int InputOutputUtils::getTransitionToPerform(State state) {

	logger.debug("InputOutputUtils - getTransitionToPerform\n");

	currentState = state;

	/*
	boolean activation1 = myowareSensorController1.activation();
	logger.info("InputOutputUtils - myowareSensorController1 - activation: %d\n", activation1);
	// TODO - Cambiar la forma en la que leemos del sensor, pasando por el multiplexor
	readMultiplexorInput(CONTROL_INPUT_MYOWARE_SENSOR_1);
	boolean activation2 = myowareSensorController2.activation();
	// TODO - Cambiar la forma en la que leemos del sensor, pasando por el multiplexor
	readMultiplexorInput(CONTROL_INPUT_MYOWARE_SENSOR_2);
	logger.info("InputOutputUtils - myowareSensorController2 - activation: %d\n", activation2);

	int transitionTo = 0;
	if (!activation1 && !activation2){
		logger.info("InputOutputUtils - IDLE\n");
		transitionTo = STATE_IDLE;
	}else if (!activation1 && activation2) {
		logger.info("InputOutputUtils - FINGERS\n");
		transitionTo = STATE_FINGER;
	} else if (activation1 && !activation2) {
		logger.info("InputOutputUtils - TONGS\n");
		transitionTo = STATE_TONGS;
	} else {
		logger.info("InputOutputUtils - FIST\n");
		transitionTo = STATE_FIST;
	}
	*/
	
	// TODELETE: Funcionalidad que permite hacer tests con el motor
	// sin depender de los sensores
	static int i = 0;
	int transitionTo = 0;

	transitionTo = ((i++)%STATES_NUMBER);

	return transitionTo;
	
}


void InputOutputUtils::openMitten() {

	logger.debug("InputOutputUtils - openMitten\n");

  
	if(getMittenPosition() == CLOSE){
		logger.info("InputOutputUtils - openMitten - OPEN\n");
		test.testOutputWithLedStripe(0,0,255,0);
		test.testOutputWithLedStripe(1,0,255,0);
		test.testOutputWithLedStripe(2,0,255,0);
		motorControl(MITTEN, OPEN, TEST_SPEED);
	}

}

void InputOutputUtils::closeMitten() {

	logger.debug("InputOutputUtils - closeMitten\n");
  
	if(getMittenPosition() == OPEN){
		logger.info("InputOutputUtils - closeMitten - CLOSE\n");
		test.testOutputWithLedStripe(0,255,0,0);
		test.testOutputWithLedStripe(1,255,0,0);
		test.testOutputWithLedStripe(2,255,0,0);
		motorControl(MITTEN, CLOSE, 100);
	}
}

void InputOutputUtils::openForefinger() {

	logger.debug("InputOutputUtils - openForefinger\n");

	if(getForefingerPosition() == CLOSE){
		logger.debug("InputOutputUtils - openForefinger - OPEN\n");
		test.testOutputWithLedStripe(3,0,255,0);
		motorControl(FOREFINGER, OPEN, TEST_SPEED);	
	}
}

void InputOutputUtils::closeForefinger() {

	logger.debug("InputOutputUtils - closeForefinger\n");

	if(getForefingerPosition() == OPEN){
		logger.debug("InputOutputUtils - closeForefinger - CLOSE\n");
		test.testOutputWithLedStripe(3,255,0,0);
		motorControl(FOREFINGER, CLOSE,TEST_SPEED);
	}
}

void InputOutputUtils::openThumb() {

	logger.debug("InputOutputUtils - openThumb\n");

	if(getThumbPosition() == CLOSE){
		logger.debug("InputOutputUtils - openThumb - OPEN\n");
		test.testOutputWithLedStripe(4,0,255,0);
		motorControl(THUMB,OPEN,TEST_SPEED);
	}

}

void InputOutputUtils::closeThumb() {

	logger.debug("InputOutputUtils - closeThumb\n");

	if(getThumbPosition() == CLOSE){
		logger.debug("InputOutputUtils - closeThumb - CLOSE\n");
		test.testOutputWithLedStripe(4,255,0,0);
		motorControl(THUMB,CLOSE,TEST_SPEED);
	}

}


/******************************************************************************/
/* PCB CONTROLS                                                               */
/******************************************************************************/


void InputOutputUtils::motorControl(int motorID, int motorDir, int motorSpeed) {

	// Forward Direction --> CLOSE --> 1
	if (motorDir) { 
		digitalWrite(MOTOR_CONTROL_MATRIX[motorID][1], LOW);
		analogWrite(MOTOR_CONTROL_MATRIX[motorID][0], motorSpeed);
		delay(1000);
		// Parar el motor
		analogWrite(MOTOR_CONTROL_MATRIX[motorID][0], 0);

	// Backward Direction --> OPEN --> 0
	} else {
		digitalWrite(MOTOR_CONTROL_MATRIX[motorID][1], HIGH);
		analogWrite(MOTOR_CONTROL_MATRIX[motorID][0], motorSpeed);
		delay(1000);
		// Parar el motor
		analogWrite(MOTOR_CONTROL_MATRIX[motorID][0], 0);
	}
  
}


int InputOutputUtils::readMultiplexorInput(int controlId){

	// Main Multiplexer (vs Acc Multiplexer)
		
	// Lecture Sensors through 74HC4051 Multiplexer
	// Entry channel selection for 74HC4051
	
	logger.info("InputOutputUtils - readMultiplexorInput - input[%i]\n", controlId);

	int cA = controlId & 0x01;   
	int cB = (controlId>>1) & 0x01;     
	int cC = (controlId>>2) & 0x01;   
	
	digitalWrite(MUX_A, cA);
	digitalWrite(MUX_B, cB);
	digitalWrite(MUX_C, cC);
  
	int readedValue = analogRead(MUX_MAIN);

	logger.info("InputOutputUtils - readMultiplexorInput - output[%i]\n", readedValue);
	
	return readedValue;

}

InputOutputUtils inputOutputUtils = InputOutputUtils();
