#include <GL/glut.h>
#include <iostream>
#include "RTIMULib.h"
#include "GLINface.h"
#include "GLCallback.h"


GLINface::GLINface(){

    GLpos.push_back(100);
	GLpos.push_back(100);
	GLpos.push_back(100);
	GLgyro.push_back(0.0);
	GLgyro.push_back(0.0);
	GLgyro.push_back(0.0);
}

GLINface::~GLINface(){

	//--intended left blank
}


void GLINface::drawCube(float size){

	glTranslatef(GLpos.at(0),GLpos.at(1),GLpos.at(2));
	glRotatef(GLgyro.at(0)/3.1416*180, 1.0f, 0.0f, 0.0f);
	glRotatef(GLgyro.at(1)/3.1416*180, 0.0f, 1.0f, 0.0f);
	glRotatef(GLgyro.at(2)/3.1416*180, 0.0f, 0.0f, 1.0f);


	glBegin(GL_QUADS);
		
		//front face
		glColor3f(1.0,0.0,0.0);
		glVertex3f(size/2,size/2,size/2);
		glVertex3f(-size/2,size/2,size/2);
		glVertex3f(-size/2,-size/2,size/2);
		glVertex3f(size/2,-size/2,size/2);

		//left face
		glColor3f(0.0,1.0,0.0);
		glVertex3f(-size/2,size/2,size/2);
		glVertex3f(-size/2,size/2,-size/2);
		glVertex3f(-size/2,-size/2,-size/2);
		glVertex3f(-size/2,-size/2,size/2);

		
		//back face
		glColor3f(0.0,0.0,1.0);
		glVertex3f(size/2,size/2,-size/2);
		glVertex3f(-size/2,size/2,-size/2);
		glVertex3f(-size/2,-size/2,-size/2);
		glVertex3f(size/2,-size/2,-size/2);

		//right face
		glColor3f(1.0,0.0,1.0);
		glVertex3f(size/2,size/2,-size/2);
		glVertex3f(size/2,size/2,size/2);
		glVertex3f(size/2,-size/2,size/2);
		glVertex3f(size/2,-size/2,-size/2);

		//top face
		glColor3f(0.0,1.0,1.0);
		glVertex3f(size/2,size/2,size/2);
		glVertex3f(-size/2,size/2,size/2);
		glVertex3f(-size/2,size/2,-size/2);
		glVertex3f(size/2,size/2,-size/2);

		//bottom face
		glColor3f(1.0,1.0,0.0);
		glVertex3f(size/2,-size/2,size/2);
		glVertex3f(-size/2,-size/2,size/2);
		glVertex3f(-size/2,-size/2,-size/2);
		glVertex3f(size/2,-size/2,-size/2);
	glEnd();

}


void GLINface::theAxis(){

	glPushMatrix();
	
	glTranslatef(GLpos.at(0),GLpos.at(1),GLpos.at(2));

	glRotatef(GLgyro.at(0)/3.1416*180, 1.0f, 0.0f, 0.0f);
	glRotatef(GLgyro.at(1)/3.1416*180, 0.0f, 1.0f, 0.0f);
	glRotatef(GLgyro.at(2)/3.1416*180, 0.0f, 0.0f, 1.0f);

	//cout<<GLgyro.at(0)<<"xx"<<GLgyro.at(1)<<"xx"<<GLgyro.at(2)<<"\n";

	glLineWidth(4);

	glBegin(GL_LINES);
	
	glColor3f(1,0,0); 
	glVertex3f(0,0,0); glVertex3f(20,0,0);

	glColor3f(0,1,0);
	glVertex3f(0,0,0); glVertex3f(0,20,0);

	glColor3f(0,0,1);
	glVertex3f(0,0,0); glVertex3f(0,0,20);
	

	glEnd();

	glPopMatrix();
}


void GLINface::GLmain(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800,800);
	glutCreateWindow("");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseEvent);
	glutMotionFunc(mouseMotion);
	glutMainLoop();

}


void GLINface::drawGrid(){

	int i;
	glLineWidth(1);
	for (i=0; i<400; i=i+4){
		glPushMatrix();
		if(i<200){ glTranslatef(0,0,i);}
		if(i>=200){ glTranslatef(i-200,0,0); glRotatef(-90,0,1,0);};

		glBegin(GL_LINES);
		glColor3f(1,1,1); glLineWidth(1);
		glVertex3f(0,-0.1,0); glVertex3f(200,-0.1,0);
		glEnd();
		glPopMatrix();
	}
	
}



