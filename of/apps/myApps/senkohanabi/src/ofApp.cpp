#include "ofApp.h"
#include "myNode.hpp"

// #define MACRO_DEBUG_MODE

#define MAX_NODE_NUM 1000
#define MAX_NODE 16

#define EDA_1_RAD  ofRandom(180, 220)
#define EDA_2_RAD  ofRandom(100, 140)
#define EDA_3_RAD  ofRandom(80, 120)
#define EDA_4_RAD  ofRandom(60, 100)


using namespace std;

/* class defienitoin */

template <class X_CLS>
class myNode {
    myNode<X_CLS> * parent ;
    myNode<X_CLS> * child[MAX_NODE] ;
    int child_cnt = 0;
    int depth = 0;
public:
    X_CLS val;
    myNode();
    myNode(myNode<X_CLS> * parent);
    void setParent(myNode<X_CLS> * parent);
    void setChild(myNode<X_CLS> * child);
    void setDepth(int p_depth);

    myNode<X_CLS> * getParent();
    int getDepth();

    void clear();

    /* ~myNode(); */
};

template <class X_CLS>
myNode<X_CLS>::myNode()
{
    
}

template <class X_CLS>
myNode<X_CLS>::myNode(myNode<X_CLS> * parent)
{
    this->parent = parent;
}

template <class X_CLS>
void myNode<X_CLS>::setParent(myNode<X_CLS> * parent)
{
    this->parent = parent;
}

template <class X_CLS>
myNode<X_CLS> * myNode<X_CLS>::getParent()
{
    return this->parent;
}

template <class X_CLS>
void myNode<X_CLS>::setChild(myNode<X_CLS> * child)
{
    this->child[child_cnt] = child;
    child_cnt++;
}

template <class X_CLS>
void myNode<X_CLS>::setDepth(int p_depth)
{
    this->depth = p_depth;
}

template <class X_CLS>
int myNode<X_CLS>::getDepth()
{
    return this->depth;
}

template <class X_CLS>
void myNode<X_CLS>::clear()
{
    this->parent = nullptr;
    for (int i = 0 ; i < child_cnt; i++)
    {
        this->child[i] = nullptr;
    }
    child_cnt = 0;
}

/*
myNode::~myNode() {
    
}
 */

/* function definition */

#if (0)
/*何故かptr_pnt->xに値が渡らない時がある。*/
void setPointCncntcircle (float cntr_x, float cntr_y, float rad, float theta,
                            ofVec2f * ptr_pnt)
{
    ptr_pnt->x = (rad * cos(theta)) + cntr_x;
    cout << rad << " " << cos(theta) << " " << ptr_pnt->x << endl;
    
    ptr_pnt->y = (rad * sin(theta)) + cntr_y;
    
    return ;
}
#else
float getPointXCncntcircle (float cntr_x, float rad, float theta)
{
    return (rad * cos(theta)) + cntr_x;
}
float getPointYCncntcircle (float cntr_y, float rad, float theta)
{
    return (rad * sin(theta)) + cntr_y;   /* 普通に間違ってたcosになってた。。。投稿した後気づく。 */
}

#endif



/* global variant */

ofVec2f  base_pos;
array<myNode<class ofVec2f>, MAX_NODE_NUM> lsNode;
int phase = 0;
int i_node_end = 0;

long frameCnt = 0;

void app_update(){
        int i_node = 0;
        
        int node_1_cnt = ofRandom(1, 5);
        int node_2_cnt = ofRandom(1, 5);
        int node_3_cnt = ofRandom(1, 5);
        int node_4_cnt = ofRandom(1, 5);
        
        int node_1_st = 0;
        int node_2_st = 0;
        int node_3_st = 0;
        int node_4_st = 0;
        /*
        int node_5_cnt = ofRandom(1, 3);
        int node_6_cnt = ofRandom(1, 3);
        int node_7_cnt = ofRandom(1, 3);
        int node_8_cnt = ofRandom(1, 3);
         */
        
        
        frameCnt++;
        
        if (frameCnt <= 100)
        {
            phase = 1;
        }
        else if (frameCnt <= 200)
        {
            phase = 2;
        }
        else if (frameCnt <= 300)
        {
            phase = 3;
        }
        else if (frameCnt <= 400)
        {
            phase = 4;
        }
        else if (frameCnt <= 500)
        {
            phase = 0;
            frameCnt = 0;
        }
        
        /* ノードクリア */
        for (int i = 0; i < i_node_end; i++)
        {
            lsNode[i].clear();
        }
        i_node_end = 0;
        
        if (phase == 0)
        {
            return ;
        }
        /* 枝分かれ1 **/
        node_1_st = i_node;
        for (int i_node_1 = 0; i_node_1 < node_1_cnt; i_node_1++,i_node++)
        {
            lsNode[i_node].setDepth(1);
            lsNode[i_node].val.x = getPointXCncntcircle(
                base_pos.x,
                EDA_1_RAD,
                glm::radians(ofRandom(0, 359))
            );
            lsNode[i_node].val.y = getPointYCncntcircle(
                base_pos.y,
                EDA_1_RAD,
                glm::radians(ofRandom(0, 359))
            );
        }
        i_node_end = i_node;

        if (phase == 4)
        {
            return ;
        }
        
        /* 枝分かれ2 **/
        node_2_st = i_node;
        for (int i_node_1 = 0; i_node_1 < node_1_cnt; i_node_1++) {
            for (int i_node_2 = 0; i_node_2 < node_2_cnt; i_node_2++,i_node++) {
                lsNode[i_node].setDepth(2);
                lsNode[node_1_st + i_node_1].setChild(&lsNode[i_node]);
                lsNode[i_node].setParent(&lsNode[node_1_st + i_node_1]);
                lsNode[i_node].val.x = getPointXCncntcircle(
                    lsNode[i_node].getParent()->val.x,
                    EDA_2_RAD,
                    glm::radians(ofRandom(0, 359))
                );
                lsNode[i_node].val.y = getPointYCncntcircle(
                    lsNode[i_node].getParent()->val.y,
                    EDA_2_RAD,
                    glm::radians(ofRandom(0, 359))
                );
            }
        }
        i_node_end = i_node;

        if (phase == 3)
        {
            return ;
        }
        
        /* 枝分かれ3 **/
        node_3_st = i_node;
        for (int i_node_1 = 0; i_node_1 < node_1_cnt; i_node_1++) {
            for (int i_node_2 = 0; i_node_2 < node_2_cnt; i_node_2++) {
                for (int i_node_3 = 0; i_node_3 < node_3_cnt; i_node_3++,i_node++) {
                    lsNode[i_node].setDepth(3);
                    lsNode[node_2_st + (i_node_1 * node_2_cnt) + i_node_2].setChild(&lsNode[i_node]);
                    lsNode[i_node].setParent(&lsNode[node_2_st + (i_node_1 * node_2_cnt) + i_node_2]);
                    lsNode[i_node].val.x = getPointXCncntcircle(
                        lsNode[i_node].getParent()->val.x,
                        EDA_3_RAD,
                        glm::radians(ofRandom(0, 359))
                    );
                    lsNode[i_node].val.y = getPointYCncntcircle(
                        lsNode[i_node].getParent()->val.y,
                        EDA_3_RAD,
                        glm::radians(ofRandom(0, 359))
                    );
                }
            }
        }
        i_node_end = i_node;

        if (phase == 2)
        {
            return ;
        }
        
        /* 枝分かれ4 **/
        node_4_st = i_node;
        for (int i_node_1 = 0; i_node_1 < node_1_cnt; i_node_1++) {
            for (int i_node_2 = 0; i_node_2 < node_2_cnt; i_node_2++) {
                for (int i_node_3 = 0; i_node_3 < node_3_cnt; i_node_3++) {
                    for (int i_node_4 = 0; i_node_4 < node_4_cnt; i_node_4++,i_node++) {
                        lsNode[i_node].setDepth(4);
                        lsNode[node_3_st + (i_node_1*node_2_cnt*node_3_cnt) + (i_node_2*node_3_cnt) + i_node_3].setChild(&lsNode[i_node]);
                        lsNode[i_node].setParent(&lsNode[node_3_st + (i_node_1*node_2_cnt*node_3_cnt) + (i_node_2*node_3_cnt) + i_node_3]);
                        lsNode[i_node].val.x = getPointXCncntcircle(
                            lsNode[i_node].getParent()->val.x,
                            EDA_4_RAD,
                            glm::radians(ofRandom(0, 359))
                        );
                        lsNode[i_node].val.y = getPointYCncntcircle(
                            lsNode[i_node].getParent()->val.y,
                            EDA_4_RAD,
                            glm::radians(ofRandom(0, 359))
                        );
                    }
                }
            }
        }
        i_node_end = i_node;
        
    /*
        for (int i = 0; i < node_1_cnt; i++) {
            ls_myNode_1.push_back(myNode<class ofVec2f>());
        }
        for (myNode<class ofVec2f> node : ls_myNode_1) {
    */

}

void setFireColor(){
    
    int rand = ofRandom(0, 7);
    
    switch (rand) {
        case 1:
            ofSetHexColor(0xff4500);
            break;
        case 2:
            ofSetHexColor(0xfffacd);
            break;
        case 3:
            ofSetHexColor(0xff6347);
            break;
        case 4:
            ofSetHexColor(0xff8c00);
            break;
        case 5:
            ofSetHexColor(0xffff00);
            break;
        default:
            ofSetHexColor(0xfa8072);
            break;
    }
}


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(18);
    ofBackgroundHex(0x000000);
    
    base_pos.x = ofGetWidth()/2;
    base_pos.y = ofGetHeight()/2;
    
    /*
    for (int i = 0; i < CIRCLE_CNT; i++) {
        pos[i].x = 0;
        pos[i].y = 0;
    }
     */
}

//--------------------------------------------------------------
void ofApp::update(){
#ifdef MACRO_DEBUG_MODE
#else
    app_update();
#endif
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    setFireColor();
    ofDrawCircle(base_pos.x, base_pos.y, 15);
    
#ifdef MACRO_DEBUG_MODE
        ofDrawBitmapString("phase: " + ofToString(phase), 10, 10);
        ofDrawBitmapString("i_node_end: " + ofToString(i_node_end), 10, 20);
#endif

    for (int i_node = 0; i_node < i_node_end; i_node++) {
        if (lsNode[i_node].getParent() != nullptr) {
            ofDrawLine(
                lsNode[i_node].getParent()->val.x,
                lsNode[i_node].getParent()->val.y,
                lsNode[i_node].val.x,
                lsNode[i_node].val.y
            );
        }
#ifdef MACRO_DEBUG_MODE
            ofDrawBitmapString("i: " + ofToString(i_node), 0, 30 + i_node*20);
            if (lsNode[i_node].getParent() != nullptr) {
                ofDrawBitmapString(
                    "P.x: " + ofToString((int)lsNode[i_node].getParent()->val.x),
                    60, 30 + i_node*20);
                ofDrawBitmapString("P.y: " + ofToString((int)lsNode[i_node].getParent()->val.y), 120, 30 + i_node*20);
            }
            ofDrawBitmapString("v.x: " + ofToString((int)lsNode[i_node].val.x), 180, 30 + i_node*20);
            ofDrawBitmapString("v.y: " + ofToString((int)lsNode[i_node].val.y), 270, 30 + i_node*20);
#endif
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

#ifdef MACRO_DEBUG_MODE
        cout << "===============" << endl;
        app_update();
#endif

#if (0)
    int i_node = 0;
        
        int node_1_cnt = ofRandom(1, 5);
        int node_2_cnt = ofRandom(1, 5);
        int node_3_cnt = ofRandom(1, 5);
        int node_4_cnt = ofRandom(1, 5);
        
        int node_1_st = 0;
        int node_2_st = 0;
        int node_3_st = 0;
        int node_4_st = 0;
        /*
        int node_5_cnt = ofRandom(1, 3);
        int node_6_cnt = ofRandom(1, 3);
        int node_7_cnt = ofRandom(1, 3);
        int node_8_cnt = ofRandom(1, 3);
         */
        
        
        frameCnt++;
        
        if (frameCnt >= 5)
        {
            phase = 1;
        }
        else if (frameCnt >= 10)
        {
            phase = 2;
        }
        else if (frameCnt >= 15)
        {
            phase = 3;
        }
        else if (frameCnt >= 20)
        {
            phase = 4;
        }
        else if (frameCnt >= 25)
        {
            phase = 0;
        }
        
        /* ノードクリア */
        for (int i = 0; i < i_node_end; i++)
        {
            lsNode[i].clear();
        }
        i_node_end = 0;
        
        if (phase == 0)
        {
            return ;
        }
        /* 枝分かれ1 **/
        node_1_st = i_node;
        for (int i_node_1 = 0; i_node_1 < node_1_cnt; i_node_1++,i_node++)
        {
            lsNode[i_node].val.x = getPointXCncntcircle(
                base_pos.x,
                ofRandom(130, 160),
                glm::radians(ofRandom(0, 359))
            );
            lsNode[i_node].val.y = getPointYCncntcircle(
                base_pos.y,
                ofRandom(130, 160),
                glm::radians(ofRandom(0, 359))
            );
        }
        i_node_end = i_node;

        if (phase == 4)
        {
            return ;
        }
        
        /* 枝分かれ2 **/
        node_2_st = i_node;
        for (int i_node_1 = 0; i_node_1 < node_1_cnt; i_node_1++) {
            for (int i_node_2 = 0; i_node_2 < node_2_cnt; i_node_2++,i_node++) {
                lsNode[node_1_st + i_node_1].setChild(&lsNode[i_node]);
                lsNode[i_node].setParent(&lsNode[node_1_st + i_node_1]);
                lsNode[i_node].val.x = getPointXCncntcircle(
                    base_pos.x,
                    ofRandom(100, 140),
                    glm::radians(ofRandom(0, 359))
                );
                lsNode[i_node].val.y = getPointYCncntcircle(
                    base_pos.y,
                    ofRandom(100, 140),
                    glm::radians(ofRandom(0, 359))
                );
            }
        }
        i_node_end = i_node;

        if (phase == 3)
        {
            return ;
        }
        
        /* 枝分かれ3 **/
        node_3_st = i_node;
        for (int i_node_1 = 0; i_node_1 < node_1_cnt; i_node_1++) {
            for (int i_node_2 = 0; i_node_2 < node_2_cnt; i_node_2++) {
                for (int i_node_3 = 0; i_node_3 < node_3_cnt; i_node_3++,i_node++) {
                    lsNode[node_2_st + (i_node_1+1)*i_node_2].setChild(&lsNode[i_node]);
                    lsNode[i_node].setParent(&lsNode[node_2_st + (i_node_1+1) * i_node_2]);
                    lsNode[i_node].val.x = getPointXCncntcircle(
                        base_pos.x,
                        ofRandom(80, 120),
                        glm::radians(ofRandom(0, 359))
                    );
                    lsNode[i_node].val.y = getPointYCncntcircle(
                        base_pos.y,
                        ofRandom(80, 120),
                        glm::radians(ofRandom(0, 359))
                    );
                }
            }
        }
        i_node_end = i_node;

        if (phase == 2)
        {
            return ;
        }
        
        /* 枝分かれ4 **/
        node_4_st = i_node;
        for (int i_node_1 = 0; i_node_1 < node_1_cnt; i_node_1++) {
            for (int i_node_2 = 0; i_node_2 < node_2_cnt; i_node_2++) {
                for (int i_node_3 = 0; i_node_3 < node_3_cnt; i_node_3++) {
                    for (int i_node_4 = 0; i_node_4 < node_4_cnt; i_node_4++,i_node++) {
                        lsNode[node_3_st + ((i_node_1+1) * (i_node_2+1) * i_node_3)].setChild(&lsNode[i_node]);
                        lsNode[i_node].setParent(&lsNode[node_3_st + ((i_node_1+1) * (i_node_2+1) *i_node_3)]);
                        lsNode[i_node].val.x = getPointXCncntcircle(
                            base_pos.x,
                            ofRandom(60, 100),
                            glm::radians(ofRandom(0, 359))
                        );
                        lsNode[i_node].val.y = getPointYCncntcircle(
                            base_pos.y,
                            ofRandom(60, 100),
                            glm::radians(ofRandom(0, 359))
                        );
                    }
                }
            }
        }
        i_node_end = i_node;
        
    /*
        for (int i = 0; i < node_1_cnt; i++) {
            ls_myNode_1.push_back(myNode<class ofVec2f>());
        }
        for (myNode<class ofVec2f> node : ls_myNode_1) {
    */
#endif
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
