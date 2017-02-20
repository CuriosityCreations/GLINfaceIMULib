#include <GL/glut.h>
#include <iostream>
#include "RTIMULib.h"
#include "GLINface.h"


int main(int argc, char **argv){

	//RTIMUSettings *settings = new RTIMUSettings("RTIMULib");
	//RTIMU *imu = RTIMU::createIMU(settings);

	GLINface GLshow;
	GLshow.GLmain(argc, argv);
	

}
