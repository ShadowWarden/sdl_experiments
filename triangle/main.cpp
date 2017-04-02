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

static void quit(int code){
	SDL_Quit();
	exit(code);
}

static void key_press(SDL_keysym* keysym){
	switch(keysym->sym){
		case SDLK_ESCAPE:
			quit(0);
			break;
		default:
			break;
	}
}

static void process_events(void){
	SDL_Event event;

	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_KEYDOWN:
				key_press(&event.key.keysym);
				break;
			case SDL_QUIT:
				quit(0);
				break;
		}
	}
}

static void draw_screen(Triangle T){
	float time = 0.001*glutGet(GLUT_ELAPSED_TIME);
	T.prepare(time);
	T.render();
	SDL_GL_SwapBuffers();
}

static void setup_opengl( int width, int height ){
	float ratio = (float) width / (float) height;

	/* Our shading model--Gouraud (smooth). */
	glShadeModel( GL_SMOOTH );

	/* Culling. */
	glCullFace( GL_BACK );
	glFrontFace( GL_CCW );
	glEnable( GL_CULL_FACE );

	/* Set the clear color. */
	glClearColor( 0, 0, 0, 0 );

	/* Setup our viewport. */
	glViewport( 0, 0, width, height );

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
	gluPerspective( 45.0f, ratio, 1.0, 100.0f );
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

	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	flags = SDL_OPENGL;

	if(SDL_SetVideoMode(width, height, bpp, flags) == 0){
		fprintf(stderr, "Video mode set failed: %s\n", SDL_GetError());
		quit(1);
	}

	Triangle T;

	setup_opengl(width, height);

	while(1){
		process_events();
		draw_screen(T);
	}
	
	return 0;
}
