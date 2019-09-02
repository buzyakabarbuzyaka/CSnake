#include "snake.h"

Snake::Snake(int i,int j)
{
	this->head=new Segment(i,j);
}

Snake::~Snake()
{
	while(head->prevSeg!=NULL)
		this->PopBack();
}

int Snake::GetLength()
{
	return length;
}

void Snake::ChangeDirection(char dir)
{
	switch(dir)
	{
		case 'N':
			if(this->direction!='S')
				this->direction='N';
			break;

		case 'E':
			if(this->direction!='W')
				this->direction='E';
			break;

		case 'W':
			if(this->direction!='E')
				this->direction='W';
			break;

		case 'S':
			if(this->direction!='N')
				this->direction='S';
			break;

		case 'O':
			this->direction='O';
			break;
	}
}

void Snake::NextPosition(int point[2])
{
	int newX=this->head->x;
	int newY=this->head->y;

	switch(this->direction)
	{
		case 'N':
			newY--;
			break;

		case 'E':
			newX++;
			break;

		case 'W':
			newX--;
			break;

		case 'S':
			newY++;
			break;

		case 'O':
			break;
	}

	point[0]=newX;
	point[1]=newY;
}

bool Snake::IsNew(int x, int y)
{
	Segment *sg=head;
	while(sg!=NULL)
	{
		if( x==sg->x && y==sg->y )
			return 0;
		sg=sg->prevSeg;
	}
	return 1;
}

bool Snake::IsLast(int x, int y)
{
	Segment *sg=head;
	while(sg->prevSeg!=NULL)
		sg=sg->prevSeg;

	return (x==sg->x && y==sg->y);
}

bool Snake::IsNew(int pos[2])
{
	Segment *sg=head;
	while(sg!=NULL)
	{
		if( pos[0]==sg->x && pos[1]==sg->y )
			return 0;
		sg=sg->prevSeg;
	}
	return 1;
}

bool Snake::IsLast(int pos[2])
{
	Segment *sg=head;
	while(sg->prevSeg!=NULL)
		sg=sg->prevSeg;

	return (pos[0]==sg->x && pos[1]==sg->y);
}

void Snake::PopBack()
{
	Segment *sg1=head;
	Segment *sg2=NULL;
	while(sg1->prevSeg!=NULL)
	{
		sg2=sg1;
		sg1=sg1->prevSeg;
	}
	delete sg1;
	if(sg2!=NULL)
		sg2->prevSeg=NULL;
}

bool Snake::Move()
{
	int newPos[2];

	NextPosition(newPos);

	if(!IsNew(newPos) && !IsLast(newPos))
		return false;

	head=new Segment(newPos[0],newPos[1],head);
	PopBack();
	return true;
}

void Snake::Eat()
{
	int newPos[2];
	this->NextPosition(newPos);
	this->head=new Segment(newPos[0],newPos[1],this->head);
	this->length++;
}
