#include "game.h"

CGrid grid(120,10,31,31,11);
CPos p(1,1,31,31);

CGrid view(10,10,9,9,7);

int x=1;
int y=1;
int dir=0;
void CGame::start()
{
	view.makeMaze();
	grid.makeMaze();
};

void CGame::mouse(int button,int state,int mx,int my)
{
};
void CGame::reshape(int w,int h)
{
	glClearColor(0.1,0.2,0.2,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	view.clear(0.0,0.0,0.0);
	grid.clear(0.4,0.0,0.9);
	grid.plot();
};
void CGame::loop()
{
	*grid.typeAt(x,y)=CGrid::snake;
	grid.plot();
	view.copyFrom(grid,x,y,dir);
	view.plot();
};

void CGame::keyboard(unsigned char keyboard,int kx,int ky)
{
	*grid.typeAt(x,y)=CGrid::space;
	dir=(dir+4+(keyboard=='w')-(keyboard=='q'))%4;
	if(keyboard=='p')
	{
		x+=((dir==1)&&(*grid.typeAt(x+1,y)==CGrid::space))
		-((dir==3)&&(*grid.typeAt(x-1,y)==CGrid::space));
		y+=((dir==0)&&(*grid.typeAt(x,y+1)==CGrid::space))
		-((dir==2)&&(*grid.typeAt(x,y-1)==CGrid::space));
	}		
};
