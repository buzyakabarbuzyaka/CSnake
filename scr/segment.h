#ifndef SEGMENT_H
#define SEGMENT_H

#include<stdlib.h>

class Segment
{
	public:
		Segment *prevSeg;
		int x;
		int y;

	public:
		Segment(int x,int y);
		Segment(int x, int y, Segment *sg);
		~Segment();
};

#endif
