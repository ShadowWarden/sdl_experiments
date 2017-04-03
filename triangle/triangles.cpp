/* triangles.cpp
 *  
 *  Omkar H. Ramachandran
 *  omkar.ramachandran@colorado.edu
 *
 *  Simple rotating triangle
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include "triangles.h"

Triangle::Triangle(){
	m_rotationAngle = 0.0f;
}

bool Triangle::init(){
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5f,0.5f,0.5f,0.5f);

	return true;
}

void Triangle::prepare(float dt){
	const float SPEED = 15.0f;
	m_rotationAngle += SPEED*dt;
	if(m_rotationAngle > 360.0f){
		m_rotationAngle -= 360.0f;
	}
}

void Triangle::render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();

	gluLookAt(1.0,1.0,1.0,0.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef(m_rotationAngle, 0.0f, 0.0f, 1.0f);

	glBegin(GL_TRIANGLES);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(-0.5f,-0.5f,0.0f);
		glColor3f(1.0f,1.0f,0.0f);
		glVertex3f(0.5f,-0.5f,0.0f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.5f,0.0f);
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

