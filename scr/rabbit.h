#ifndef RABBIT_H
#define RABBIT_H

#include <math.h>
#include <time.h>

#include "snake.h"

class Rabbit
{
	private:
		int n;
		int** map;
		Snake* snake;
	public:
		int x;
		int y;

	public:
		Rabbit(int n0 ,Snake* sn);
		~Rabbit();
	public:
		void NewRabbit();
		void Position(int pos[2]);
};
#endif
