#include "stack.h"
#include "window.h"
#include "pos.h"

#ifndef _GRTD
#define _GRID
class CGrid:public CWindow
{
public:
	static const unsigned char space=0;
	static const unsigned char wall=1;
	static const unsigned char snake=2;
private:
	int width;
	int height;
	int cellSize;
	struct _CELL
	{
		unsigned char type;
		int v;
	}*cell;
public:
	CGrid();
	CGrid(int x,int y,int w,int h,int s);
	void define(int x,int y,int w,int h,int s);
	~CGrid();
	void plot();
	void makeMaze();
	void set(int x,int y,unsigned char n,int val){cell[x+y*height]=_CELL{n,val};};
	void set(CPos &p,unsigned char n,int val){cell[p.x+p.y*height]=_CELL{n,val};};
	unsigned char *typeAt(int x,int y);
	unsigned char *typeAt(CPos &p);
	unsigned char *typeAt(int x,int y,int dx,int dy,int dir);
	unsigned char *typeAt(CPos &p,int dx,int dy,int dir);

	void copyFrom(CGrid &from,int x,int y,int dir);
};
#endif
