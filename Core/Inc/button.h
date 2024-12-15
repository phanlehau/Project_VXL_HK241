
#ifndef BUTTON_H_
#define BUTTON_H_

#include "global.h"

#define NORMAL_STATE SET
#define PRESSED_STATE RESET

extern int button1_flag;
extern int button2_flag;
extern int button3_flag;
extern int nhan1;
extern int nhan2;
extern int nhan3;
void getKeyInput();

#endif /* INC_BUTTON_H_ */

