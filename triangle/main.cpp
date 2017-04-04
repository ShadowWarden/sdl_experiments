/* main.cpp
 *
 *  Omkar H. Ramachandran
 *  omkar.ramachandran@colorado.edu
 *
 *  Rotating triangle : OpenGL + SDL
 */

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include "triangles.h"

#include <cstdlib>

float speed = 10.0f;

void ChangeSpeed(float dv){
	speed += dv;
}

static int fps=0,sec0=0,count=0;
int FramesPerSecond(void){
	int sec = glutGet(GLUT_ELAPSED_TIME)/1000;
	if (sec!=sec0){
		sec0 = sec;
		fps = count;
		count=0;
	}
	count++;
	return fps;
}


static void quit(int code){
	SDL_Quit();
	exit(code);
}

static void key_press(SDL_keysym* keysym, Triangle *T, Camera *C, int * fps){
	switch(keysym->sym){
		case SDLK_ESCAPE:
			quit(0);
			break;
		case SDLK_SPACE:
			fprintf(stderr,"FPS = %d\n",*fps);
			break;
		case SDLK_KP_PLUS:
			ChangeSpeed(5.0f);
			break;
		case SDLK_KP_MINUS:
			ChangeSpeed(-5.0f);
			break;
		case SDLK_i:
			T->print();
			break;
		case SDLK_UP:
			C->Move(1);
			break;
		case SDLK_DOWN:
			C->Move(-1);
			break;
		case SDLK_LEFT:
			C->Move(-2);
			break;
		case SDLK_RIGHT:
			C->Move(2);
			break;
		case SDLK_p:
			C->print();
			break;
		default:
			break;
	}
}

static void process_events(Triangle *T,Camera *C,int *fps){
	SDL_Event event;

	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_KEYDOWN:
				key_press(&event.key.keysym,T,C,fps);
				break;
			case SDL_QUIT:
				quit(0);
				break;
		}
	}
}

static void draw_screen(Triangle T,Camera C,int * fps){
	float time = 0.001*glutGet(GLUT_ELAPSED_TIME);
	T.prepare(time);
	T.render(C);
	*fps = FramesPerSecond();
	SDL_GL_SwapBuffers();
}

static void setup_opengl( int width, int height ){
	float ratio = (float) width / (float) height;

	/* Our shading model--Gouraud (smooth). */
	glShadeModel( GL_SMOOTH );

	/* Culling. */
//	glCullFace( GL_BACK );
//	glFrontFace( GL_CCW );
//	glEnable( GL_CULL_FACE );

	/* Set the clear color. */
	glClearColor( 0, 0, 0, 0 );

	/* Setup our viewport. */
	glViewport( 0.0, 0.0, width, height );

	/*
	 * Change to the projection matrix and set
	 * our viewing volume.
	 */
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	/*
	 * EXERCISE:
	 * Replace this with a call to glFrustum.
	 */
	gluPerspective( 60.0f, ratio, 1.0, 100.0f );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char ** argv){
	const SDL_VideoInfo* info = NULL;

	int width = 0;
	int height = 0;
	/* Colour depth */
	int bpp = 0;
	int flags = 0;

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		fprintf(stderr, "Video init failed: %s\n",SDL_GetError());
		quit(1);
	}

	info = SDL_GetVideoInfo();

	if(!info){
		fprintf(stderr, "Video query failed: %s\n", SDL_GetError());
		quit(1);
	}

	width = 640;
	height = 480;
	bpp = info->vfmt->BitsPerPixel;

	flags = SDL_OPENGL;

	if(SDL_SetVideoMode(width, height, bpp, flags) == 0){
		fprintf(stderr, "Video mode set failed: %s\n", SDL_GetError());
		quit(1);
	}

	Triangle T;
	Camera C;
	int fps;
	setup_opengl(width, height);

	while(1){
		process_events(&T,&C,&fps);
		draw_screen(T,C,&fps);
	}

	return 0;
}
