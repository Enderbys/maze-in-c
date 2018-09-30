#ifndef _GAME
#define _GAME
#include <GL/freeglut.h>
#include <GL/gl.h>
#include "pos.h"
#include "window.h"
#include "grid.h"
class CGame
{
public:
	virtual void start();
	virtual void keyboard(unsigned char key,int x,int y);
	virtual void mouse(int button,int state,int x,int y);
	virtual void reshape(int w,int h);
	virtual void loop();
};
#endif

