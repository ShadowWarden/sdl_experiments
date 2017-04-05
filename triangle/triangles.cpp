/* triangles.cpp
 *  
 *  Omkar H. Ramachandran
 *  omkar.ramachandran@colorado.edu
 *
 *  Simple rotating triangle
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdio>
#include <cmath>
#include "triangles.h"

#define PI 3.14159265
#define DEGtoRAD 0.0174533
/* Fix radius to 1.0 */
const float r = 2.0f;

Triangle::Triangle(){
	m_rotationAngle = 0.0f;
}

bool Triangle::init(){
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5f,0.5f,0.5f,0.5f);

	return true;
}

void Triangle::prepare(float dt){
	m_rotationAngle += speed*dt;
	if(m_rotationAngle > 360.0f){
		m_rotationAngle = m_rotationAngle-360.0f;
	}
}

void Triangle::render(Camera C){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	float th = C.Getth();
	float ph = C.Getph();

	float Eye_x = r*sin(th*DEGtoRAD)*cos(ph*DEGtoRAD);
	float Eye_y = r*sin(th*DEGtoRAD)*sin(ph*DEGtoRAD);
	float Eye_z = r*cos(th*DEGtoRAD);
	
	float Up_z = (th>=180.0f && th<360.0f)?-1.0f:1.0f;

	gluLookAt(Eye_x,Eye_y,Eye_z,0.0,0.0,0.0,0.0,0.0,Up_z);
	glRotatef(m_rotationAngle, 0.0f, 0.0f, 1.0f);

	glBegin(GL_TRIANGLES);
		// Top
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(-0.5f,-0.5f,0.05f);
		glColor3f(1.0f,1.0f,0.0f);
		glVertex3f(0.5f,-0.5f,0.05f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.5f,0.05f);
		// Bottom
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(-0.5f,-0.5f,-0.05f);
		glColor3f(1.0f,1.0f,0.0f);
		glVertex3f(0.5f,-0.5f,-0.05f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.5f,-0.05f);
		// (-0.5,-0.5)	-> (0.5,-0.5) up
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(-0.5f,-0.5f,0.05f);
		glColor3f(1.0f,1.0f,0.0f);
		glVertex3f(0.5f,-0.5f,0.05f);
		glColor3f(1.0f,1.0f,0.0f);
		glVertex3f(0.5f,-0.5f,-0.05f);
		// (-0.5,-0.5)	-> (0.5,-0.5) down
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(-0.5f,-0.5f,-0.05f);
		glColor3f(1.0f,1.0f,0.0f);
		glVertex3f(0.5f,-0.5f,-0.05f);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(-0.5f,-0.5f,0.05f);
		// (0.5,-0.5) Yellow-> (0.0,0.5) Blue up
		glColor3f(1.0f,1.0f,0.0f);
		glVertex3f(0.5f,-0.5f,0.05f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.5f,0.05f);
		glColor3f(1.0f,1.0f,0.0f);
		glVertex3f(0.5f,-0.5f,-0.05f);
		// (0.5,-0.5) Yellow-> (0.0,0.5) Blue down
		glColor3f(1.0f,1.0f,0.0f);
		glVertex3f(0.5f,-0.5f,-0.05f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.5f,-0.05f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.5f,0.05f);
		// (0.0,0.5) Blue-> (-0.5,-0.5) Red up
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.5f,0.05f);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(-0.5f,-0.5f,0.05f);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(-0.5f,-0.5f,-0.05f);
		// (0.0,0.5) Blue-> (-0.5,-0.5) Red down
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.5f,-0.05f);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(-0.5f,-0.5f,-0.05f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.5f,0.05f);
	glEnd();

	glBegin(GL_LINES);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(1.0f,0.0f,0.0f);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,1.0f,0.0f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,1.0f);
	glEnd();
}

void Triangle::onResize(int width, int height){
	glViewport(0,0,width,height);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(45.0f, float(width)/float(height), 1.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Triangle::print(){
	fprintf(stderr,"speed = %f ; m_rotationAngle = %f\n",speed,m_rotationAngle);
}

float Triangle::GetAngle(){
	return m_rotationAngle;
}
