#include "game.h"

using namespace std;
using namespace cv;
//Frame
Frame::Frame(int a,int b,int n, Rabbit* rb, Snake* sn)
{
	high=(a/n)*n;
	width=(b/n)*n;
	fieldSize=n;

	rabbit=rb;
	snake=sn;

	Mat M(high,width,CV_8UC3,COL1);
	gameField=M;
	//drawSnake=new DrawSnake(sn);

	namedWindow("Snake",WINDOW_AUTOSIZE);
	DrawField();
	NewFrame();
}

Frame::~Frame(){}

void Frame::DrawField(void)
{
	int n=this->fieldSize;
	int a=this->high/n;
	int b=this->width/n;
	int q=this->frameSize;

	Mat scr=this->gameField;

	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			rectangle(scr,Point(i*a+q,j*b+q),Point((i+1)*a-q,(j+1)*b-q),COL2,-1);

	this->gameField=scr;
}

void Frame::DrawHead()
{
	int n=this->fieldSize;
	int a=this->high/n;
	int b=this->width/n;
	int q=this->frameSize;

	int i,j;

	Segment *sg=this->snake->head;
	Mat scr=this->frame;

	i=sg->x;
	j=sg->y;
	rectangle(scr,Point(i*a+q,j*b+q),Point((i+1)*a-q,(j+1)*b-q),COL3,-1);
	//sg=sg->prevSeg;

	this->frame=scr;
}

void Frame::DrawBack()
{
	/*int n=this->fieldSize;
	int a=this->high/n;
	int b=this->width/n;
	int q=this->frameSize;

	int i,j;

	Segment *sg=this->snake->head;
	Mat scr=this->frame;

	while(sg->prevSeg!=NULL)
		sg=sg->prevSeg;

	i=sg->x;
	j=sg->y;
	rectangle(scr,Point(i*a+q,j*b+q),Point((i+1)*a-q,(j+1)*b-q),COL3,-1);
	sg=sg->prevSeg;

	this->frame=scr;*/
}

void Frame::DrawBlocks()
{
	int n=fieldSize;
	int a=high/n;
	int b=width/n;
	int q=frameSize;
	int p=snakeFrameSize;
	int f=q+p;

	int i1,j1,i2,j2,f1,f2;

	Segment *sg1=snake->head;
	Segment *sg2=sg1->prevSeg;

	Mat scr=frame;

	while(sg2!=NULL)
	{
		i1=sg1->x;
		j1=sg1->y;

		i2=sg2->x;
		j2=sg2->y;

		if((i1-i2)<0 || (j1-j2)<0)
		{
			i2++;
			j2++;
			f1=f;
			f2=-f;
		}
		else
		{
			i1++;
			j1++;
			f1=-f;
			f2=f;
		}

		rectangle(scr,Point(i1*a+f1,j1*b+f1),Point(i2*a+f2,j2*b+f2),COL3,-1);
		sg1=sg2;
		sg2=sg2->prevSeg;
	}

	this->frame=scr;
}

void Frame::DrawSnake(void)
{
	DrawHead();
	DrawBlocks();
	if(snake->GetLength()>1)
		DrawBack();
}

void Frame::DrawRabbit(void)
{
	int n=this->fieldSize;
	int a=this->high/n;
	int b=this->width/n;
	int q=this->frameSize;

	int i,j;

	int rbPos[2];
	this->rabbit->Position(rbPos);
	Mat scr=this->frame;

	i=rbPos[0];
	j=rbPos[1];
	rectangle(scr,Point(i*a+q,j*b+q),Point((i+1)*a-q,(j+1)*b-q),COL4,-1);
}

void Frame::NewFrame(void)
{
	this->gameField.copyTo(this->frame);
	DrawSnake();
	this->DrawRabbit();

	imshow("Snake",this->frame);
}

//KeyBuffer
enum {LEFT=81, UP, RIGHT, DOWN, ESC=27, ENTER=13};

KeyBuffer::KeyBuffer()
{
	isChanged=false;
	keyBuf=-1;
}

bool KeyBuffer::IsArrow(int key)
{
	switch (key)
	{
		case UP:
			isChanged=true;
			keyBuf=UP;
			return true;

		case DOWN:
			isChanged=true;
			keyBuf=DOWN;
			return true;

		case LEFT:
			isChanged=true;
			keyBuf=LEFT;
			return true;

		case RIGHT:
			isChanged=true;
			keyBuf=RIGHT;
			return true;
	}

	return false;
}

char KeyBuffer::returnDirection()
{
	switch (keyBuf)
	{
		case UP:
			return 'N';
		case DOWN:
			return 'S';
		case LEFT:
			return 'W';
		case RIGHT:
			return 'E';
	}
	return 'O';
}

//Game
Game::Game(int a, int b, int n,double dif)
{
	fieldSize=n;
	difficulty=dif;

	snake=new Snake(n/2,n/2);
	rabbit=new Rabbit(n,this->snake);
	timer=new cTimer();
	keyBuf=new KeyBuffer();
	frame=new Frame(a,b,n,rabbit,snake);

	frame->NewFrame();
}

void Game::Loop()
{
	char key=-1;
	while(stateFlag!=END)//key!=ESC) //&& stateFlag!=END)
	{
		key=waitKey(500);

		if(key==ESC)
			GameEnd();
		else
		{
			if(key!=-1 && stateFlag==PAUSE)
				stateFlag=RUNNING;

			if(stateFlag==RUNNING)
			{
				if(keyBuf->IsArrow(key))
					snake->ChangeDirection(keyBuf->returnDirection());

				if(Tick())
					frame->NewFrame();
				else
					GameEnd();
			}
		}
	}

	cout<<"Score: "<<snake->GetLength()<<endl;

}

bool Game::Tick()
{
	int snPos[2];
	int rbPos[2];

	snake->NextPosition(snPos);
	rabbit->Position(rbPos);

	if(snPos[0]==rbPos[0] && snPos[1]==rbPos[1])
	{
		snake->Eat();
		rabbit->NewRabbit();
	}
	else
		if(!CheckBorders(snPos))
			return false;
		else
			if(!snake->Move())
			{
				GameEnd();
				return false;
			}

	return true;
}

bool Game::CheckBorders(int snPos[2])
{
	if(snPos[0]>fieldSize-1 || snPos[0]<0)
		return false;

	if(snPos[1]>fieldSize-1 || snPos[1]<0)
		return false;

	return true;
}

void Game::GameEnd()
{
	stateFlag=END;
}

void Game::GamePause()
{
	stateFlag=PAUSE;
}
