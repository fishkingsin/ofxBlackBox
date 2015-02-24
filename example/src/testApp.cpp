#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	fondo.loadImage("fondo.jpg");
	ofSetWindowShape(fondo.width,fondo.height);
	
	keyboard.setFont("helvetica.ttf",13);
	keyboard.loadMap("mac.kbd");
	keyboard.alpha = 200;
	ofAddListener(keyboard.objectPressed,this,&testApp::keyboardPressed);
	
	window.setup("setup.xml");
	ofAddListener(window.objectPressed,this,&testApp::windowPressed);
	
#ifdef USE_TUIO
	ofAddListener(tuioClient.cursorAdded,this,&testApp::tuioAdded);
	ofAddListener(tuioClient.cursorRemoved,this,&testApp::tuioRemoved);
	ofAddListener(tuioClient.cursorUpdated,this,&testApp::tuioUpdated);
	tuioClient.start(3333);
	
	keyboard.setTuioClient(&tuioClient);
	window.setTuioClient(&tuioClient);
#endif
	
}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(100,100,100);	
	
	keyboard.update();
	window.update();
	
#ifdef USE_TUIO //------------------ TUIO 
	tuioClient.getMessage();
#endif
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255, 255, 255);
	fondo.draw(0,0);
	
	keyboard.draw();
	window.draw();
	
#ifdef USE_TUIO //------------------ TUIO 
	tuioClient.drawCursors();
#endif
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	switch(key) {
		case 'f': ofToggleFullscreen(); break;
		case 'n': keyboard.addKey("N", 100, 100,53,53); break;
		case 's': keyboard.saveMap("newmap.kbd"); break;
		case 'w': window.close = !window.close;
	}
}

void testApp::keyboardPressed(string & action){
    if(window.objects.size()>0)
    {
        if(window.objects[window.focusObject] != NULL)
        {
            window.objects[window.focusObject]->act += action;
        }
    }
}

void testApp::windowPressed(string & action){
	if (action == "CLOSE") window.close = true;
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
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

#ifdef USE_TUIO
void testApp::tuioAdded(ofxTuioCursor &tuioCursor){	
}

void testApp::tuioUpdated(ofxTuioCursor &tuioCursor){
}

void testApp::tuioRemoved(ofxTuioCursor &tuioCursor){
}
#endif
