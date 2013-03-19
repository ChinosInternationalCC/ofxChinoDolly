#ifndef __ofxChinoDolly__
#define __ofxChinoDolly__

#include "ofMain.h"


#define ARDUINO_CONNECTED
#define DEFAULT_SERIAL_COM "\\\\.\\COM12"
//#define DEFAULT_SERIAL_COM "COM12"

class ofxChinoDolly{
	
	public:
	
		ofxChinoDolly();
		//ofxChinoDolly(string ComPort);


		~ofxChinoDolly();
		void setup();
		unsigned char MoveDollyForward(unsigned char Revolutions);
		unsigned char MoveDollyBackward(unsigned char Revolutions);
		unsigned char ShiftDollyLeft(unsigned char Revolutions);
		unsigned char ShiftDollyRight(unsigned char Revolutions);
		unsigned char TiltDollyUp(unsigned char Revolutions);
		unsigned char TiltDollyDown(unsigned char Revolutions);
		unsigned char Calibrate(void);
		unsigned char SetSpeed(unsigned char Speed);
		//void waitConfirmation(void);

	private:
		ofSerial	serial;

};

#endif