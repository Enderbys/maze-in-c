#ifndef _POS
#define _POS
class CPos
{
public:
	int x,y;
	int width,height;
public:
	CPos(int px,int py,int w,int h);
	void get(int &px,int &py);
	void move(int dx,int dy,int dir);
};
#endif

