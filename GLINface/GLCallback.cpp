#include <GL/glut.h>
#include <iostream>
#include "RTIMULib.h"
#include "GLCallback.h"
#include "GLINface.h"


GLINface GLInface;

bool movecubekey;
bool moveframekey;
double oldX, oldY;
double zone;
double rotateAnglex,rotateAngley;
double movefx, movefy;

RTIMUSettings *settings = new RTIMUSettings("RTIMULib");
RTIMU *imu = RTIMU::createIMU(settings);

//  initialization
double ax=0.0f, ay=0.0f, az=0.0f;
double preax=0.0f, preay=0.0f, preaz=0.0f;
double vx=0.0f, vy=0.0f, vz=0.0f;
double x=0.0f, y=0.0f, z=0.0f;

//  high pass filter (zero-phase forward and reverse digital IIR filtering)
double a1 = 1.0;		double a2 = -0.9244;
double b1 = 0.9622;		double b2 = -b1;

/*double a1 = 1.0;		double a2 = -1.0;
double b1 = 1.0;		double b2 = -b1;*/

int order = 1;
double vxn1 = 0.0, vyn1 = 0.0, vzn1 = 0.0;
double dxn1 = 0.0, dyn1 = 0.0, dzn1 = 0.0;
double resultaxn1 = 0.0, resultayn1 = 0.0, resultazn1 = 0.0;
double resultvxn1 = 0.0, resultvyn1 = 0.0, resultvzn1 = 0.0;

int sampleCount = 0;
bool resetpos = false;


void mouseEvent(int button, int state, int x, int y){
	
	switch(button){
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN){
			oldX = x;
			oldY = y;
			movecubekey = true;
		}
		else{
			movecubekey = false;
		}
		break;
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN){
			moveframekey = true;

		}
		else{
			movecubekey = false;
		}
		break;
	case 3 :
		 zone += 5;
		break;
	case 4 :
		 zone -= 5;
		break;

	}
}


void mouseMotion(int x,int y){

	//cout<<" delX="<<(x - oldX)<<" delY="<<(y - oldY)<<endl;
	if (movecubekey == true){
		if(abs(x - oldX) > 0 && abs(x - oldX) > abs(y - oldY)){
			//rotate about Y
			if((x - oldX) > 0){
				rotateAnglex += 10.0 * 0.11;
			}
			else{
				rotateAnglex -= 10.0 * 0.11;
			}
		}
		if(abs(y - oldY) > 0 && abs(y - oldY) > abs(x - oldX)){
			//rotate about X
			if((y - oldY) > 0){
				rotateAngley += 10.0 * 0.11;
			}
			else{
				rotateAngley -= 10.0 * 0.11;
			}
		}

		oldX = x;
		oldY = y;
	}
	if (moveframekey == true){
		if(abs(x - oldX) > 0 && abs(x - oldX) > abs(y - oldY)){
			if((x - oldX) > 0){
				movefx += 1;
			}
			else{

				movefx -= 1;
			}

		}
		if(abs(y - oldY) > 0 && abs(y - oldY) > abs(x - oldX)){
			if((y - oldY) > 0){

				movefy += 1;
			}
			else{
				movefy -= 1;
			}
		}


		oldX = x;
		oldY = y;
	}
}


void filter(RTVector3 imuData, RTVector3 imuPoseData){

	vx = vx + imuData.x() / 9.8;
	vy = vy + imuData.y() / 9.8;
	vz = vz + imuData.z() / 9.8;

	
	if (sampleCount > order) {
		vx = (b1 * vx + b2 * vxn1 + a2 * resultaxn1) / a1;
		vy = (b1 * vy + b2 * vyn1 + a2 * resultayn1) / a1;
		vz = (b1 * vz + b2 * vzn1 + a2 * resultazn1) / a1;
		resultaxn1 = vx;
		resultayn1 = vy;
		resultazn1 = vz;
	}

	vxn1 = vx;
	vyn1 = vy;
	vzn1 = vz;
			
	
	x = x + vx;
	y = y + vy;
	z = z + vz;

	

	if (sampleCount > order) {
		x = (b1 * x + b2 * dxn1 + a2 * resultvxn1) / a1;
		y = (b1 * y + b2 * dyn1 + a2 * resultvyn1) / a1;
		z = (b1 * z + b2 * dzn1 + a2 * resultvzn1) / a1;
		resultvxn1 = x;
		resultvyn1 = y;
		resultvzn1 = z;
	}

	dxn1 = x;
	dyn1 = y;
	dzn1 = z;

    
	if (sampleCount%1== 0){
		GLInface.GLpos.at(0) = 100*x+100;
		GLInface.GLpos.at(2) = 100*y+100;
		GLInface.GLpos.at(1) = 100*z+100;

	}

	GLInface.GLgyro.at(0) = imuPoseData.x();
	GLInface.GLgyro.at(2) = imuPoseData.y();
	GLInface.GLgyro.at(1) = imuPoseData.z();

}


void filter2(RTVector3 imuData, RTVector3 imuPoseData){

	ax = imuData.x();
	if (abs(ax-preax) > 0.05){
        vx = vx + ax;
		GLInface.GLpos.at(0) = GLInface.GLpos.at(0) + vx;
	}
	preax = ax;

	ay = imuData.y();
	if (abs(ay-preay) > 0.05){
        vy = vy + ay;
		GLInface.GLpos.at(1) = GLInface.GLpos.at(1) + vy;
	}
	preay = ay;

	az = imuData.z();
	if (abs(az-preaz) > 0.05){
        vz = vz + az;
		GLInface.GLpos.at(2) = GLInface.GLpos.at(2) + vz;
	}
	preaz = az;


	if (resetpos){
		GLInface.GLpos.at(0) = 100;
		GLInface.GLpos.at(2) = 100;
		GLInface.GLpos.at(1) = 0;
	}
	resetpos = false;

	GLInface.GLgyro.at(0) = imuPoseData.x();
	GLInface.GLgyro.at(2) = imuPoseData.y();
	GLInface.GLgyro.at(1) = imuPoseData.z();

}


void filter3(RTVector3 imuData, RTVector3 imuPoseData){

	ax = imuData.x();	
	vx = vx + imuData.x();
	if (abs(ax-preax) > 0.05 && abs(ax-preax) < 10){
		if (sampleCount > order) {
			vx = (b1 * vx + b2 * vxn1 + a2 * resultaxn1) / a1;
			resultaxn1 = vx;
		}
		vxn1 = vx;
		GLInface.GLpos.at(0) = GLInface.GLpos.at(0) + vx;

		if (sampleCount > order) {
			GLInface.GLpos.at(0) = (b1 * GLInface.GLpos.at(0) + b2 * dxn1 + a2 * resultvxn1) / a1;
			resultvxn1 = GLInface.GLpos.at(0);
		}
		dxn1 = GLInface.GLpos.at(0);
	}
	else{
		resultaxn1 = 0.0;
		resultvxn1 = 0.0;
	}
	preax = ax;


	ay = imuData.y();	
	vy = vy + imuData.y();
	if (abs(ay-preay) > 0.05 && abs(ay-preay) < 10){
		if (sampleCount > order) {
			vy = (b1 * vy + b2 * vyn1 + a2 * resultayn1) / a1;
			resultayn1 = vy;
		}
		vyn1 = vy;
		GLInface.GLpos.at(1) = GLInface.GLpos.at(1) + vy;

		if (sampleCount > order) {
			GLInface.GLpos.at(1) = (b1 * GLInface.GLpos.at(1) + b2 * dyn1 + a2 * resultvyn1) / a1;
			resultvyn1 = GLInface.GLpos.at(1);
		}
		dyn1 = GLInface.GLpos.at(1);
	}
	else{
		resultayn1 = 0.0;
		resultvyn1 = 0.0;
	}
	preay = ay;


	az = imuData.z();
	vz = vz + imuData.z();
	if (abs(az-preaz) > 0.05 && abs(az-preaz) < 10){
		if (sampleCount > order) {
			vz = (b1 * vz + b2 * vzn1 + a2 * resultazn1) / a1;
			resultazn1 = vz;
		}
		vzn1 = vz;
		GLInface.GLpos.at(2) = GLInface.GLpos.at(2) + vz;

		if (sampleCount > order) {
			GLInface.GLpos.at(2)  = (b1 * GLInface.GLpos.at(2)  + b2 * dzn1 + a2 * resultvzn1) / a1;
			resultvzn1 = GLInface.GLpos.at(2) ;
		}
		dzn1 = GLInface.GLpos.at(2);
	}
	else{
		resultazn1 = 0.0;
		resultvzn1 = 0.0;
	}
	preaz = az;

	/*if (sampleCount%1== 0){
		GLInface.GLpos.at(0) = x+100;
		GLInface.GLpos.at(2) = y+100;
		GLInface.GLpos.at(1) = z+100;

	}*/

	if (resetpos){
		GLInface.GLpos.at(0) = 100;
		GLInface.GLpos.at(2) = 100;
		GLInface.GLpos.at(1) = 100;
	}
	resetpos = false;

	GLInface.GLgyro.at(0) = imuPoseData.x();
	GLInface.GLgyro.at(2) = imuPoseData.y();
	GLInface.GLgyro.at(1) = imuPoseData.z();

}


void filter4(RTVector3 imuData, RTVector3 imuPoseData){

	ax = imuData.x();	
	ay = imuData.y();	
	az = imuData.z();	
	vx = vx + ax / 9.8;
	vy = vy + ay / 9.8;
	vz = vz + az / 9.8;

	
	if (sampleCount > order) {
		vx = (b1 * vx + b2 * vxn1 + a2 * resultaxn1) / a1;
		vy = (b1 * vy + b2 * vyn1 + a2 * resultayn1) / a1;
		vz = (b1 * vz + b2 * vzn1 + a2 * resultazn1) / a1;
		resultaxn1 = vx;
		resultayn1 = vy;
		resultazn1 = vz;
	}

	vxn1 = vx;
	vyn1 = vy;
	vzn1 = vz;
	
	
	x = x + vx;
	y = y + vy;
	z = z + vz;

	

	if (sampleCount > order) {
		x = (b1 * x + b2 * dxn1 + a2 * resultvxn1) / a1;
		y = (b1 * y + b2 * dyn1 + a2 * resultvyn1) / a1;
		z = (b1 * z + b2 * dzn1 + a2 * resultvzn1) / a1;
		resultvxn1 = x;
		resultvyn1 = y;
		resultvzn1 = z;
	}

	dxn1 = x;
	dyn1 = y;
	dzn1 = z;

    
	if (sampleCount%1== 0){
		GLInface.GLpos.at(0) = 100*x+100;
		GLInface.GLpos.at(2) = 100*y+100;
		GLInface.GLpos.at(1) = 100*z+100;

	}

	GLInface.GLgyro.at(0) = imuPoseData.x();
	GLInface.GLgyro.at(2) = imuPoseData.y();
	GLInface.GLgyro.at(1) = imuPoseData.z();
	

}


void display(){
	sampleCount++;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef (-135, 0, -800);
	glTranslatef (movefx, -movefy, zone);

	glRotatef(40,1,1,0);

	glRotatef(rotateAnglex, 0.0, 0.5, 0.0);
	glRotatef(rotateAngley, 0.35, 0.0, -0.35);

	GLInface.drawGrid();
	GLInface.theAxis();
	GLInface.drawCube(4.0);
	
	RTVector3 imuData = imu->getAccelResiduals();
	RTVector3 imuPoseData = imu->getMeasuredPose();

	if(imu->IMURead()){
		printf("Accel: 	x %.4f y %.4f z %.4f\n", imuData.x(), imuData.y(), imuData.z());
	}

	filter4(imuData, imuPoseData);
    //filter2(imuData, imuPoseData);
    //filter3(imuData, imuPoseData);
	
	glutPostRedisplay();

	glutSwapBuffers();
	

}

void init(){

	if ((imu == NULL) || (imu->IMUType() == RTIMU_TYPE_NULL)) {
        printf("No IMU found\n");
        exit(1);
    }

	imu->IMUInit();

	imu->setSlerpPower(0.02);
    imu->setGyroEnable(true);
    imu->setAccelEnable(true);
    imu->setCompassEnable(true);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(35,1.0f,0.1f,1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1,0.1,0.1,1);

}


void keyboard(unsigned char key, int x, int y){

	if(key =='s' || key =='S'){
		resetpos = true;
	}
	
	glutPostRedisplay();

}




