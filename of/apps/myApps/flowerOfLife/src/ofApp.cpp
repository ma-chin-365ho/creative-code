#include "ofApp.h"

#define RAD_LEN     30
#define POINT_NUM_HEXAGONAL 6
#define CIRCUMF_NUM 8

ofVec2f pos_ctr;
long frame_cnt = 0;

//--------------------------------------------------------------
float getPointXCncntcircle (float cntr_x, float rad, float theta)
{
    return (rad * cos(theta)) + cntr_x;
}
float getPointYCncntcircle (float cntr_y, float rad, float theta)
{
    return (rad * sin(theta)) + cntr_y;
}



//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(18);
    ofBackgroundHex(0x000000);
    
    pos_ctr.x = ofGetWidth() / 2;
    pos_ctr.y = ofGetHeight() / 2;
}

//--------------------------------------------------------------
void ofApp::update(){

    
    
    
    frame_cnt++;
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofVec2f pos;
    ofVec2f base_pos;
    float theta;
    float kakudo = 0;
    float rad = 0;

    /* center cirlce */
    ofNoFill();
    ofDrawCircle(pos_ctr.x, pos_ctr.y, RAD_LEN);
    
    base_pos.x = pos_ctr.x;
    base_pos.y = pos_ctr.y;
    

/*
    // ofDrawCircle(pos_ctr.x + RAD, pos_ctr.y, RAD);
    pos.x = getPointXCncntcircle(base_pos.x, RAD, theta);
    pos.y = getPointYCncntcircle(base_pos.y, RAD, theta);
    cout << "================" << endl;
    cout << base_pos.x << endl ;
    cout << base_pos.y << endl ;
    cout << pos.x << endl ;
    cout << pos.y << endl ;
*/

#if (1)
    for (int j = 0; j < CIRCUMF_NUM; j++) {
        if ((j % 2) == 0) {
            kakudo = 30;
            rad = RAD_LEN * ((int)(j / 2) + 1);
        } else {
            kakudo = 0;
            rad = ((RAD_LEN * cos(glm::radians((float)30))) * 2)
                + ((RAD_LEN * cos(glm::radians((float)30))) * ((j - 1) / 2));
        }
        theta = glm::radians(kakudo);

        for (int i = 0; i < POINT_NUM_HEXAGONAL; i++) {
            
            pos.x = getPointXCncntcircle(base_pos.x, rad, theta);
            pos.y = getPointYCncntcircle(base_pos.y, rad, theta);
            
            /* Surrounding circle */
            ofDrawCircle(pos.x, pos.y, RAD_LEN);

            kakudo += (360 / 6);
            theta = glm::radians(kakudo);
        }
    }
#endif
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
