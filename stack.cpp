#include <stdio.h>
#include "stack.h"

CStack::CStack()
{
	bufferSize=10;
	list=new unsigned char[bufferSize];
	pi=0;
	po=bufferSize-1;
	size=0;
}
CStack::~CStack()
{
	delete[]list;
}
void CStack::expand()
{
	unsigned char *temp=new unsigned char[bufferSize+10];
	for(int n=0;n<bufferSize;n++)
	{
		temp[n]=list[(n+po+1)%bufferSize];
	}
	pi=bufferSize-1;
	bufferSize+=10;
	po=bufferSize-1;
	delete[]list;
	list=temp;
}
void CStack::push(unsigned char in)
{
	list[pi]=in;
	if(pi==po)
		expand();
	pi=(pi+1)%bufferSize;
	size++;
};
unsigned char CStack::popTail()
{
	if(size>0)
	{
		size--;
		po=(po+1)%bufferSize;
		return list[po];
	}
	return 255;
};
unsigned char CStack::pop()
{
	if(size>0)
	{
		size--;
		pi=(pi+bufferSize-1)%bufferSize;
		return list[pi];
	}
	return 255;
}
unsigned char CStack::get(int n)
{
	return list[(po+1+n)%bufferSize];
}
void CStack::reset()
{
	pi=0;
	po=bufferSize-1;
	size=0;
}
