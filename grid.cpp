#include "window.h"
#include "grid.h"

CGrid::CGrid()
{
	cell=0;
};
CGrid::~CGrid()
{
	if(cell)delete[]cell;
}
CGrid::CGrid(int x,int y,int w,int h,int s)
{
	cell=0;
	define(x,y,w,h,s);
}
void CGrid::define(int x,int y,int w,int h,int s)
{
	CWindow::define(x,y,s*(w+1),s*(h+1),-1,-1,w,h);
	if(cell)delete[]cell;
	width=w;
	height=h;
	cellSize=s;
	cell=new _CELL[w*h];
	for(int n=0;n<(w*h);n++)
		cell[n]=_CELL{wall,0};
};
void CGrid::plot()
{
	CWindow::clear(0,0,0);
	CWindow::adjust();
	for(int y=0;y<height;y++)
	{
		for(int x=0;x<width;x++)
		{
			unsigned char q=cell[y*width+x].type;
			if(q==space)
			{
				CWindow::dot(x,y,cellSize-1.0,0.4,0.1,0);
			}else if(q==wall)
			{
				CWindow::dot(x,y,cellSize-1.0,1,0.9,0.0);
			}else if(q==snake)
			{
				CWindow::dot(x,y,cellSize-1.0,0.9,0.0,0.0);
			}		
		}
	}
}
/*
unsigned char CGrid::get(unsigned px,unsigned py,int dx,int dy,unsigned d)
{
	px=(px+width+dx*((d==0)-(d==2))+dy*((d==1)-(d==3)))%width;
	py=(py+height+dx*((d==3)-(d==1))+dy*((d==0)-(d==2)))%height;
	return buffer[px+py*width];
	
};
*/
unsigned char *CGrid::typeAt(int x,int y)
{
	return &cell[x+y*width].type;
};
unsigned char *CGrid::typeAt(CPos &p)
{
	return &cell[p.x+p.y*width].type;
};
unsigned char *CGrid::typeAt(int x,int y,int dx,int dy,int dir)
{
	x=(x+width+dx*((dir==0)-(dir==2))+dy*((dir==1)-(dir==3)))%width;
	y=(y+height+dx*((dir==3)-(dir==1))+dy*((dir==0)-(dir==2)))%height;
	return &cell[x+y*width].type;
};
unsigned char *CGrid::typeAt(CPos &p,int dx,int dy,int dir)
{
	return typeAt(p.x,p.y,dx,dy,dir);
}

void CGrid::copyFrom(CGrid &from,int x,int y,int dir)
{
	for(int py=0;py<height;py++)
	{
		for(int px=0;px<width;px++)
		{
			cell[px+width*py].type=*from.typeAt(x,y,px-int(width/2),py-int(height/2),dir);
		}
	}
}
void CGrid::makeMaze()
{
	CStack stack;
	for(int n=0;n<(width*height);n++)
		cell[n]=_CELL{wall,0};

	int x=1;
	int y=1;
	int x1,y1;
	bool move;
	int d;
	do{
		cell[x+y*width]=_CELL{space,0};
		int t=0;
		do{
			d=rand()%4;
			x1=x+2*((d==1)-(d==3));
			y1=y+2*((d==0)-(d==2));
			move=((x1>0)&&(x1<(width-1))&&(y1>0)&&(y1<(height-1)));
			if(move)move=(cell[x1+y1*width].type==wall);
		}while((t++<10)&&(!move));
		if(move)
		{
			stack.push(d);
			cell[x1+y1*width].type=space;
			x=x1;
			y=y1;
			x1=x+(d==3)-(d==1);
			y1=y+(d==2)-(d==0);
			cell[x1+y1*width].type=space;
		}else
		{
			d=stack.pop();
			x=x+2*((d==3)-(d==1));
			y=y+2*((d==2)-(d==0));
		}	
	}while(d!=255);		
		
}
