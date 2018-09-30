#include "pos.h"
CPos::CPos(int px,int py,int w,int h)
{
	x=px;
	y=py;
	width=w;
	height=h;
}
void CPos::get(int &px,int &py)
{
	px=x;
	py=y;
}
void CPos::move(int dx,int dy,int dir)
{
	x=(x+width+dx*((dir==0)-(dir==2))+dy*((dir==1)-(dir==3)))%width;
	y=(y+height+dx*((dir==3)-(dir==1))+dy*((dir==0)-(dir==2)))%height;
}
