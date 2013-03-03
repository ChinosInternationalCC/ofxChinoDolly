#ifndef __ofxChinoDolly__
#define __ofxChinoDolly__

#include "ofMain.h"


#define ARDUINO_CONNECTED

class ofxChinoDolly{
	
	public:
	
		ofxChinoDolly();
		//ofxChinoDolly(string ComPort);


		~ofxChinoDolly();
		void setup();
		unsigned char MoveDollyForward(unsigned char Revolutions);
		unsigned char MoveDollyBackward(unsigned char Revolutions);
		unsigned char TiltUp(unsigned char Revolutions);
		unsigned char TiltDown(unsigned char Revolutions);
		unsigned char ShiftLeft(unsigned char Revolutions);
		unsigned char ShiftRight(unsigned char Revolutions);
		unsigned char Calibrate(void);
		unsigned char SetSpeed(unsigned char Speed);

	private:
		ofSerial	serial;

};

#endif