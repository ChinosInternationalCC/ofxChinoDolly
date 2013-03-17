#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    gui = new ofxUICanvas(0,0,320,320);
    gui->addWidgetDown(new ofxUILabel("Manual Control", OFX_UI_FONT_LARGE)); 
	gui->addWidgetDown(new ofxUIToggle(32, 32, false, "FULLSCREEN"));
    gui->addWidgetRight(new ofxUIToggle(32, 32, false, "Calibrate"));
	gui->addSlider("Carito Position",5,40,100,304,16);
	gui->addWidgetDown(new ofxUIButton(32, 32, false, "Backward"));
	gui->addWidgetRight(new ofxUIButton(32, 32, false, "Forward"));
	gui->addSlider("Shift",5,40,100,304,16);
    gui->addWidgetDown(new ofxUIButton(32, 32, false, "ShiftLeft"));
	gui->addWidgetRight(new ofxUIButton(32, 32, false, "ShiftRight"));	
	gui->addSlider("Tilt",5,40,100,304,16);
	gui->addWidgetDown(new ofxUIButton(32, 32, false, "TiltUp"));
	gui->addWidgetRight(new ofxUIButton(32, 32, false, "TiltDown"));
	gui->addNumberDialer("Speed",0.0,255.0,0.0,1.0);
    
    ofAddListener(gui->newGUIEvent, this, &testApp::guiEvent); 
    gui->loadSettings("GUI/guiSettings.xml"); 

	dolly.setup();
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}
//--------------------------------------------------------------
void testApp::exit()
{
    //gui->saveSettings("GUI/guiSettings.xml"); 
    delete gui; 
}
//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
{	
	unsigned char Rev;
    float CurrentPosSliderVal;
	
	if(e.widget->getName() == "Carito Position")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;    
        //ofBackground(slider->getScaledValue());
		CurrentPosSliderVal = slider->getScaledValue();
		
		if ((unsigned char)CurrentPosSliderVal != (unsigned char)PosPreviousPosSliderVal)
		{  
			if (PosPreviousPosSliderVal > CurrentPosSliderVal)
			{
				Rev = (unsigned char) (PosPreviousPosSliderVal-CurrentPosSliderVal);
				cout << Rev << '\n';
			    cout << (PosPreviousPosSliderVal-CurrentPosSliderVal); 
				dolly.MoveDollyForward(Rev);
			}
			else
			{
				Rev = (unsigned char) (CurrentPosSliderVal-PosPreviousPosSliderVal);
				cout <<'-' <<Rev << '\n';			
				
				dolly.MoveDollyBackward(Rev);

			}
		
			//save the current Slider Position
			PosPreviousPosSliderVal = CurrentPosSliderVal;
		}

    }
    else if(e.widget->getName() == "FULLSCREEN")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        ofSetFullscreen(toggle->getValue());   
    }
	else if(e.widget->getName() == "Backward")
    {
		dolly.MoveDollyBackward(1);
    }
	else if(e.widget->getName() == "Forward")
    {
		dolly.MoveDollyForward(1);
    }
	else if(e.widget->getName() == "ShiftLeft")
    {
		dolly.ShiftDollyLeft(1);
    }
	else if(e.widget->getName() == "ShiftRight")
    {
		dolly.ShiftDollyRight(1);
    }
	else if(e.widget->getName() == "TiltUp")
    {
		dolly.TiltDollyUp(1);
    }
	else if(e.widget->getName() == "TiltDown")
    {
		dolly.TiltDollyDown(1);
    }
	else if(e.widget->getName() == "Tilt")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;    
        //ofBackground(slider->getScaledValue());
		CurrentPosSliderVal = slider->getScaledValue();
		
		if ((unsigned char)CurrentPosSliderVal != (unsigned char)TiltPreviousPosSliderVal)
		{  
			if (TiltPreviousPosSliderVal > CurrentPosSliderVal)
			{   
				Rev = (unsigned char) (TiltPreviousPosSliderVal-CurrentPosSliderVal);
				cout << Rev << '\n';
			    cout << (TiltPreviousPosSliderVal-CurrentPosSliderVal); 
				dolly.TiltDollyDown(Rev);
			}
			else
			{
				Rev = (unsigned char) (CurrentPosSliderVal-TiltPreviousPosSliderVal);
				cout <<'-' <<Rev << '\n';			
				
				dolly.TiltDollyUp(Rev);

			}
		
			//save the current Slider Position
			TiltPreviousPosSliderVal = CurrentPosSliderVal;
		}

    }
	else if(e.widget->getName() == "Shift")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;    
        //ofBackground(slider->getScaledValue());
		CurrentPosSliderVal = slider->getScaledValue();
		
		if ((unsigned char)CurrentPosSliderVal != (unsigned char)ShiftPreviousPosSliderVal)
		{  
			if (ShiftPreviousPosSliderVal > CurrentPosSliderVal)
			{   
				Rev = (unsigned char) (ShiftPreviousPosSliderVal-CurrentPosSliderVal);
				cout << Rev << '\n';
			    cout << (ShiftPreviousPosSliderVal-CurrentPosSliderVal); 
				dolly.ShiftDollyLeft(Rev);
			}
			else
			{
				Rev = (unsigned char) (CurrentPosSliderVal-ShiftPreviousPosSliderVal);
				cout <<'-' <<Rev << '\n';			
				
				dolly.ShiftDollyRight(Rev);

			}
		
			//save the current Slider Position
			ShiftPreviousPosSliderVal = CurrentPosSliderVal;
		}

    }
	else if(e.widget->getName() == "Calibrate")
	{
		dolly.Calibrate();

	}
	else if(e.widget->getName() == "Speed")
	{
		ofxUINumberDialer *dialer = (ofxUINumberDialer *) e.widget;
		dolly.SetSpeed((unsigned char)dialer->getValue());
	}
}
//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
    switch (key) {
        case 'p':
            gui->setDrawWidgetPadding(true);
            break;
        case 'P':
            gui->setDrawWidgetPadding(false);
            break;

		case 'f':
			dolly.MoveDollyForward(1);
			break;
		case 'b':
			dolly.MoveDollyBackward(1);
			break;

		case 'l':
			dolly.MoveDollyForward(1);
			break;
		case 'r':
			dolly.MoveDollyBackward(1);
			break;
		case 'u':
			dolly.MoveDollyForward(1);
			break;
		case 'd':
			dolly.MoveDollyBackward(1);
			break;
	
	 
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{

}
//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}