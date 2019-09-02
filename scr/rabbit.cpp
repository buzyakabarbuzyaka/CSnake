#include "rabbit.h"

Rabbit::Rabbit(int n0 ,Snake* sn)
{
	n=n0;
	snake=sn;

	map=new int* [n0];
	for(int i=0;i<n0;i++)
		map[i]=new int [n0];

	srand(time(NULL));
	NewRabbit();
}

void Rabbit::NewRabbit()
{
	int m=n*n-snake->GetLength();
	int indexOfRabbit=0;

	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			map[i][j]=1;

	Segment *sg=snake->head;
	while(sg!=NULL)
	{
		map[sg->x][sg->y]=0;
		sg=sg->prevSeg;
	}

	indexOfRabbit=rand()%m+1;
	//this->x=0;
	//this->y=0;

	for(int i=0;i<n && indexOfRabbit!=0;i++)
		for(int j=0;j<n && indexOfRabbit!=0;j++)
		{
			indexOfRabbit-=map[i][j];

			if(indexOfRabbit==0)
			{
				this->x=i;
				this->y=j;
			}
		}
}

Rabbit::~Rabbit(){}

void Rabbit::Position(int pos[2])
{
	pos[0]=this->x;
	pos[1]=this->y;
}
