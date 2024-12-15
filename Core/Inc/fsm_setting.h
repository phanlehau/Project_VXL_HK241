#ifndef SETTING_H_
#define SETTING_H_

#include "global.h"

#define SETTINGDO 0
#define SETTINGXANH 1
#define SETTINGVANG 2

extern uint8_t check_dexanh;
extern uint8_t check_devang;

void init_setting();
void fsm_setting();


#endif
