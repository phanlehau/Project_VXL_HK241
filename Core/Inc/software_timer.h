#ifndef SOFTWARE_TIMER_H_
#define SOFTWARE_TIMER_H_

#include "global.h"
extern int timer_counter[10];
extern int timer_flag[10];

void setTimer(int number, int duration);
void timer_run();

#endif /* SOFTWARE_TIMER_H_ */
