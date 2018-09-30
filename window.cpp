#include "window.h"
int CWindow::windowHeight;
CWindow::CWindow()
{
	visible=true;
	posx=20;
	posy=20;
	width=100;
	height=50;
	xmin=-1;
	ymin=-1;
	xmax=1;
	ymax=1;
};
CWindow::CWindow(int x,int y,int w,int h,double minx,double miny,double maxx,double maxy)
{
	define(x,y,w,h,minx,miny,maxx,maxy);
};

void CWindow::define(int x,int y,int w,int h,double minx,double miny,double maxx,double maxy)
{
	visible=true;
	posx=x;
	posy=y+h;
	width=w;
	height=h;
	xmin=minx;
	ymin=miny;
	xmax=maxx;
	ymax=maxy;
};
void CWindow::range(double minx,double miny,double maxx,double maxy)
{
	xmin=minx;
	ymin=miny;
	xmax=maxx;
	ymax=maxy;
};

void CWindow::setVisible(bool v)
{
	if((visible=1)&&(v==0))clear(0,0,0);
	visible=v;
};
void CWindow::adjust()
{
	glViewport(posx,windowHeight-posy,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glScalef(2/(xmax-xmin),2/(ymax-ymin),1);
	glTranslatef(-(xmax+xmin)/2.0,-(ymax+ymin)/2.0,0.0);
};
void CWindow::clear(double r,double g,double b)
{
	if(!visible)return;
	adjust();
	glColor4f(r,g,b,1.0);
	glBegin(GL_QUADS);
	glVertex2f(xmin,ymin);
	glVertex2f(xmax,ymin);
	glVertex2f(xmax,ymax);
	glVertex2f(xmin,ymax);
	glEnd();
};
void CWindow::axis(double r,double g,double b)
{
	if(!visible)return;
	adjust();
	glColor4f(r,g,b,1.0);
	glBegin(GL_LINES);
	glVertex2f(xmin,0);
	glVertex2f(xmax,0);
	glVertex2f(0,ymin);
	glVertex2f(0,ymax);
	glEnd();
};
double CWindow::xStep()
{
	return (xmax-xmin)/double(width);
}
double CWindow::yStep()
{
	return (ymax-ymin)/double(height);
}
double CWindow::screenToMouseX(int x)
{
	return xmin+((x-posx)/double(width))*(xmax-xmin);
}
double CWindow::screenToMouseY(int y)
{
	return ymin+(((windowHeight-y)-posy)/double(height))*(ymax-ymin);
}
double CWindow::ratio()
{
	return yStep()/xStep();
}
void CWindow::print(int x, int y, char *string, ...)
{
 	if(!visible)return;
	va_list st;
    va_start(st, string);
	adjust();
    char str[100];
    vsnprintf(str,100, string, st);
    va_end(st);
	glColor4f(1,1,1,1.0);
    glRasterPos2f(x,height-y-16);
	for(int i=0;str[i]!=0;i++)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str[i]);
	cursory=y+16;
}
void CWindow::print(char *string, ...)
{
	if(!visible)return;
    va_list st;
    va_start(st, string);
	adjust();
    char str[100];
    vsnprintf(str,100, string, st);
    va_end(st);
	glColor4f(1,1,1,1.0);
    glRasterPos2f(0,height-cursory-16);
	for(int i=0;str[i]!=0;i++)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str[i]);
	cursory=cursory+16;
}
void CWindow::dot(double x,double y,double size,double r,double g,double b)
{
	if(!visible)return;
	adjust();
	glColor4f(r,g,b,1.0);
	glPointSize(size);
	glBegin(GL_POINTS);
		glVertex2f(x,y);
	glEnd();
};
void CWindow::dot(double x,double y,double size,const double *color)
{
	if(!visible)return;
	adjust();
	glColor4f(color[0],color[1],color[2],1.0);
	glPointSize(size);
	glBegin(GL_POINTS);
		glVertex2f(x,y);
	glEnd();
};
void CWindow::line(double x1,double y1,double x2,double y2,double r,double g,double b)
{
	if(!visible)return;
	adjust();
	glColor4f(r,g,b,1.0);
	glBegin(GL_LINES);
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
	glEnd();
};

void CWindow::function(double(*f)(double),double r,double g,double b)
{
	if(!visible)return;
	adjust();
	glColor4f(r,g,b,1.0);
	glPointSize(1.0);
	glBegin(GL_POINTS);
	for(double x=xmin;x<xmax;x+=xStep())
	{
		glVertex2f(x,f(x));
	}
	glEnd();
};
bool CWindow::isHover(int x,int y)
{
	if(!visible)return false;
	double px=screenToMouseX(x);
	double py=screenToMouseY(y);
	return((px>xmin)&&(px<xmax)&&(py>ymin)&&(py<ymax));
}
