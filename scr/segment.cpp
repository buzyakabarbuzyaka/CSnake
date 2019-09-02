#include "segment.h"

Segment::Segment(int x,int y)
{
	this->x=x;
	this->y=y;
	this->prevSeg=NULL;
}

Segment::Segment(int x, int y, Segment *sg)
{
	this->x=x;
	this->y=y;
	this->prevSeg=sg;
}

Segment::~Segment(){}
