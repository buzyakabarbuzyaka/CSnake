#ifndef SNAKE_H
#define SNAKE_H

#include "segment.h"

class Snake
{
	private:
		int length=1;	
	public:
		char direction='O';
		Segment *head;

	public:
		Snake(int i,int j);
		~Snake();

	public:
		int GetLength();
		
		void NextPosition(int point[2]);
		bool IsNew(int x, int y);
		bool IsLast(int x, int y);
		
		bool IsNew(int pos[2]);
		bool IsLast(int pos[2]);		

		void PopBack();
		
		void ChangeDirection(char dir);
		bool Move();
		void Eat();
};
#endif
