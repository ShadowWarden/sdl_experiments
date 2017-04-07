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
#include "object.h"

#include <cstdlib>

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

static void key_press(SDL_keysym* keysym, Object *T, Camera *C, int * fps){
	switch(keysym->sym){
		case SDLK_ESCAPE:
			quit(0);
			break;
		case SDLK_SPACE:
			fprintf(stderr,"FPS = %d\n",*fps);
			break;
		case SDLK_KP_PLUS:
			T->ChangeSpeed(5.0f);
			break;
		case SDLK_KP_MINUS:
			T->ChangeSpeed(-5.0f);
			break;
		case SDLK_i:
			T->print();
			break;
		case SDLK_UP:
		case SDLK_KP8:
			C->Move(-1);
			break;
		case SDLK_DOWN:
		case SDLK_KP2:
			C->Move(+1);
			break;
		case SDLK_KP4:
		case SDLK_LEFT:
			C->Move(-2);
			break;
		case SDLK_KP6:
		case SDLK_RIGHT:
			C->Move(2);
			break;
		case SDLK_p:
			C->print();
			break;
		case SDLK_w:
			C->Zoom(-0.05f);
			break;
		case SDLK_x:
			C->Zoom(0.05f);
			break;	
		default:
			break;
	}
}

static void process_events(Object *T,Camera *C,int *fps){
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

static void draw_screen(Object T,Camera C,int * fps){
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
	//glCullFace( GL_BACK );
	//glFrontFace( GL_CCW );
	//glEnable( GL_CULL_FACE );

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
	gluPerspective( 45.0f, ratio, 1.0f, 100.0f );
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

	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 0 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	if(SDL_SetVideoMode(width, height, bpp, flags) == 0){
		fprintf(stderr, "Video mode set failed: %s\n", SDL_GetError());
		quit(1);
	}

	Object T = Object("solid_triangle.in");
	Camera C;
	int fps;
	setup_opengl(width, height);

	while(1){
		process_events(&T,&C,&fps);
		draw_screen(T,C,&fps);
	}

	return 0;
}
