#ifndef GAME_H
#define GAME_H

#define COL1 Scalar(60,60,60)
#define COL2 Scalar(120,120,120)
#define COL3 Scalar(0,0,100)
#define COL4 Scalar(0,80,0)

#define END 0
#define PAUSE 1
#define RUNNING 2

#include <iostream>

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

#include "rabbit.h"
#include "timer.h"

class Frame
{
	protected:
		int high;
		int width;
		int fieldSize;
		int frameSize=1;
		Rabbit* rabbit;
		Snake* snake;

		cv::Mat gameField;
		cv::Mat frame;

	public:
		Frame(int a,int b, int n, Rabbit* rb, Snake *sn);
		~Frame();	

	protected:
		int snakeFrameSize=5;
		void DrawHead();
		void DrawBack();
		void DrawBlocks();

	public:
		void DrawField(void);
		void DrawSnake(void);
		void DrawRabbit(void);
		void NewFrame(void);
};

class KeyBuffer
{
	public:
		bool isChanged;
		int keyBuf;

	public:
		KeyBuffer();
		~KeyBuffer();
	
	public:
		bool IsArrow(int key);
		char returnDirection();
};

class Game
{	
	private:
		int fieldSize;
		double difficulty;
		int stateFlag=PAUSE;
		
		Snake* snake;
		Rabbit* rabbit;
		cTimer* timer;
		KeyBuffer* keyBuf;
		Frame* frame;

	public:
		Game(int a, int b, int n,double dif);
		~Game();

	public:
		void Loop();
		bool CheckBorders(int snPos[2]);
		bool Tick();
		void GameEnd();
		void GamePause();
};

#endif
