#include "ofxChinoDolly.h"
#include "ChinoDollyComm.h"

ofxChinoDolly::ofxChinoDolly()
{
	
}

ofxChinoDolly::~ofxChinoDolly()
{
	
}

void ofxChinoDolly::setup()
{
	#ifdef ARDUINO_CONNECTED
	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
	// this should be set to whatever com port your serial device is connected to.
	// (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
	// arduino users check in arduino app....
	//serial.setup(0, baud); //open the first device
	int baud=9600;
	ofxChinoDolly::serial.setup(DEFAULT_SERIAL_COM, baud); // windows example 
	#endif   
}

unsigned char ofxChinoDolly::MoveDollyForward(unsigned char Revolutions)
{
	#ifdef ARDUINO_CONNECTED
	ofxChinoDolly::serial.writeByte(CMD_MOVE_FORWARD);
	ofxChinoDolly::serial.writeByte(Revolutions);
	#endif
	return 0;
}

unsigned char ofxChinoDolly::MoveDollyBackward(unsigned char Revolutions)
{
	#ifdef ARDUINO_CONNECTED
	ofxChinoDolly::serial.writeByte(CMD_MOVE_BACKWARD);
	ofxChinoDolly::serial.writeByte(Revolutions);
	#endif
	return 0;
}

unsigned char ofxChinoDolly::ShiftDollyLeft(unsigned char Revolutions)
{
	#ifdef ARDUINO_CONNECTED
	ofxChinoDolly::serial.writeByte(CMD_SHIFT_LEFT);
	ofxChinoDolly::serial.writeByte(Revolutions);
	#endif
	return 0;
}

unsigned char ofxChinoDolly::ShiftDollyRight(unsigned char Revolutions)
{
	#ifdef ARDUINO_CONNECTED
	ofxChinoDolly::serial.writeByte(CMD_SHIFT_RIGHT);
	ofxChinoDolly::serial.writeByte(Revolutions);
	#endif
	return 0;
}

unsigned char ofxChinoDolly::TiltDollyUp(unsigned char Revolutions)
{
	#ifdef ARDUINO_CONNECTED
	ofxChinoDolly::serial.writeByte(CMD_TILT_UP);
	ofxChinoDolly::serial.writeByte(Revolutions);
	#endif
	return 0;
}

unsigned char ofxChinoDolly::TiltDollyDown(unsigned char Revolutions)
{
	#ifdef ARDUINO_CONNECTED
	ofxChinoDolly::serial.writeByte(CMD_TILT_DOWN);
	ofxChinoDolly::serial.writeByte(Revolutions);
	#endif
	return 0;
}

unsigned char ofxChinoDolly::SetSpeed(unsigned char Speed)
{
	#ifdef ARDUINO_CONNECTED
	ofxChinoDolly::serial.writeByte(CMD_SET_SPEED);
	ofxChinoDolly::serial.writeByte(Speed);
	#endif
	return 0;
}

unsigned char ofxChinoDolly::Calibrate(void){
	#ifdef ARDUINO_CONNECTED
	ofxChinoDolly::serial.writeByte(CMD_CALIBRATE);
	ofxChinoDolly::serial.writeByte(0);
	#endif

	return 0;
}