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
#include "object.h"

#define PI 3.14159265
#define DEGtoRAD 0.0174533
/* Fix radius to 1.0 */
//const float r = 2.0f;

float * read(FILE * fin, int N){
	float *vert = new float[N*18];
	int i;
	for(i=0;i<N*18;i++)
		fscanf(fin,"%f ",vert+i);
	for(i=0;i<18;i++){
		fprintf(stderr,"%f ",vert[18+i]);
		if((i+1)%3==0)
			fprintf(stderr,"\n");
	}
	return vert;
}

int getsize(FILE * fin){
	fseek(fin,SEEK_SET,0);
	int n;
	fscanf(fin,"%d",&n);
	return n;
}

Object::Object(char *fname){
	FILE *fin = fopen(fname,"r");
	N = getsize(fin);
	float *vert = read(fin,N);
	T = new Triangle[N];
	int i;
	for(i=0;i<N;i++){
		T[i] = Triangle(&vert[i*18]);
	}	
	m_rotationAngle = 0.0f;
	speed = 15.0f;
	flag = false;
	T[1].print();	
}

bool Object::init(){
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5f,0.5f,0.5f,0.5f);

	return true;
}

void Object::prepare(float dt){
	if(!flag)
		m_rotationAngle += speed*dt;
	if(m_rotationAngle > 360.0f){
		m_rotationAngle = m_rotationAngle-360.0f;
	}
}

void Object::render(Camera C){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	float th = C.Getth();
	float ph = C.Getph();
	float r = C.Getr();

	float Eye_x = r*sin(th*DEGtoRAD)*cos(ph*DEGtoRAD);
	float Eye_y = r*sin(th*DEGtoRAD)*sin(ph*DEGtoRAD);
	float Eye_z = r*cos(th*DEGtoRAD);
	
	float Up_z = (th>=180.0f && th<360.0f)?-1.0f:1.0f;

	gluLookAt(Eye_x,Eye_y,Eye_z,0.0,0.0,0.0,0.0,0.0,Up_z);
	glRotatef(m_rotationAngle, 0.0f, 0.0f, 1.0f);

	int i;
	glBegin(GL_TRIANGLES);
		for(i=0;i<N;i++){	
			T[i].render();
		}
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

void Object::onResize(int width, int height){
	glViewport(0,0,width,height);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(45.0f, float(width)/float(height), 1.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Object::print(){
	fprintf(stderr,"speed = %f ; m_rotationAngle = %f\n",speed,m_rotationAngle);
}

float Object::GetAngle(){
	return m_rotationAngle;
}

void Object::ChangeSpeed(float dv){
	speed += dv;
	//flag = true;
}
