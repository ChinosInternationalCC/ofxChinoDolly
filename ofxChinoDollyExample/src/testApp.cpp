#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    gui = new ofxUICanvas(0,0,320,320);
    gui->addWidgetDown(new ofxUILabel("Chino Dolly", OFX_UI_FONT_LARGE)); 
    gui->addSlider("Carito Position",5,40,100,304,16);
	gui->addWidgetDown(new ofxUIButton(32, 32, false, "Backward"));
	gui->addWidgetDown(new ofxUIButton(32, 32, false, "Forward"));
    gui->addWidgetDown(new ofxUIButton(32, 32, false, "ShiftLeft"));
	gui->addWidgetDown(new ofxUIButton(32, 32, false, "ShiftRight"));
	gui->addWidgetDown(new ofxUIButton(32, 32, false, "TiltUp"));
	gui->addWidgetDown(new ofxUIButton(32, 32, false, "TiltDown"));
    gui->addWidgetDown(new ofxUIToggle(32, 32, false, "FULLSCREEN"));
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
		
		if ((unsigned char)CurrentPosSliderVal != (unsigned char)PreviousPosSliderVal)
		{  
			if (PreviousPosSliderVal > CurrentPosSliderVal)
			{
				Rev = (unsigned char) (PreviousPosSliderVal-CurrentPosSliderVal);
				cout << Rev << '\n';
			    cout << (PreviousPosSliderVal-CurrentPosSliderVal); 
				dolly.MoveDollyForward(Rev);
			}
			else
			{
				Rev = (unsigned char) (CurrentPosSliderVal-PreviousPosSliderVal);
				cout <<'-' <<Rev << '\n';			
				
				dolly.MoveDollyBackward(Rev);

			}
		
			//save the current Slider Position
			PreviousPosSliderVal = CurrentPosSliderVal;
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