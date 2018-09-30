//gcc -lglut -lGL -lGLU
#include <GL/freeglut.h>
#include <GL/gl.h>
#include "game.h"
CGame theGame;
void glStart(int argc,char *argv[],int w,int h);
void glKey(unsigned char key,int x,int y);
void glMouse(int button,int state,int x,int y);
void glReshape(int w,int h);
void glLoop();
int glWindowHeight;
//
void glStart(int argc,char *argv[],int w,int h,char *name)
{
	glutInit(&argc,argv);
	glutInitDisplayMode( GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize( w,h );
	glutCreateWindow(name);
	glutDisplayFunc(glLoop);
	glutIdleFunc(glLoop);
	glutKeyboardFunc(glKey);
	glutMouseFunc(glMouse);
	glutReshapeFunc(glReshape);
	glutSetOption( GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS );
}
//
//
void glKey(unsigned char key,int x,int y)
{
	if(key=='x'){glutLeaveMainLoop();};
	theGame.keyboard(key,x,y);
};
void glMouse(int button,int state,int x,int y)
{
	theGame.mouse(button,state,x,y);
};
void glReshape(int w,int h)
{
	CWindow::setWindowHeight(h);
	theGame.reshape(w,h);
	glFlush();
};
void glLoop()
{
	theGame.loop();
	glFlush();
}
//
int main(int argc,char *argv[])
{
	glStart(argc,argv,500,500,(char *)"Snake");
	theGame.start();
	glutMainLoop();
}
