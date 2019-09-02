#include "timer.h"

cTimer::cTimer() {
	clock_gettime(CLOCK_REALTIME, &process_start);
	frame_start = process_start;
}

cTimer::~cTimer() {

}

bool cTimer::Period(double tFrame)
{
	clock_gettime(CLOCK_REALTIME, &current);
	double elapsed = (current.tv_sec + current.tv_nsec/1.0e9 - frame_start.tv_sec -   frame_start.tv_nsec / 1.0e9);
	if(elapsed>=tFrame)
		return true;
	return false;
}

double cTimer::elapsed(bool frame) {
	clock_gettime(CLOCK_REALTIME, &current);
	double elapsed = frame ? (current.tv_sec + current.tv_nsec / 1.0e9 -   frame_start.tv_sec -   frame_start.tv_nsec / 1.0e9) :
				 (current.tv_sec + current.tv_nsec / 1.0e9 - process_start.tv_sec - process_start.tv_nsec / 1.0e9);
	frame_start = current;
	return elapsed;
}
