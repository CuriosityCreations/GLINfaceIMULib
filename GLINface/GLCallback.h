#ifndef _GLCALLBACK_H_
#define _GLCALLBACK_H_


/*
GL Callback
*/


//--GLINface mouseEvent
void mouseEvent(int button, int state, int x, int y);

//--GLINface mouseMotion
void mouseMotion(int x,int y);

//--GLINface displayall
void display();

//--GLINface initialize
void init();

//--GLINface KeyBoard
void keyboard(unsigned char key, int x, int y);

//--GLINface IMUfilter
void filter(RTVector3 imuData);


//--GLINface IMUfilter
void filter2(RTVector3 imuData);


#endif
