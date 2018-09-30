#ifndef _STACK
#define _STACK
class CStack
{
private:
	unsigned char *list;
	int bufferSize;
	int size;
	int pi,po;
	void expand();
public:
	CStack();
	~CStack();
	void push(unsigned char in);
	unsigned char popTail();
	unsigned char pop();
	unsigned char get(int n);
	int getSize(){return size;};
	void reset();
};
#endif
