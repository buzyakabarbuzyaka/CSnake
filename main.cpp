/*#include "game.h"

//#include "opencv2/videoio.hpp"

using namespace cv;

int main(void)
{
	//Game* game = new Game(1000,1000,20,1.0);
	//game->Loop();

	Mat img = imread("../1.png", IMREAD_COLOR);//CV_HAL_DFT_STAGE_COLS);//CV_LOAD_IMAGE_COLOR);
	int a = 120;

	Rect centerRec = Rect(img.cols / 2 - a, img.rows / 2 - a, 2 * a, 2 * a);
	img(centerRec).copyTo(img);

	namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
	imshow("Display window", img);
	imwrite("../2.png", img);
	while (waitKey(33) == -1);
	return 0;
}*/

#include "game.h"

int main(void)
{
	Game* game = new Game(600,600,7,1.0);
	game->Loop();
	return 0;
}
