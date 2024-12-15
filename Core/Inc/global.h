

#ifndef GLOBAL_H_
#define GLOBAL_H_

#define AUTOMATIC 0
#define MANUAL 1
#define SET_DO 2
#define SET_XANH 3
#define SET_VANG 4
#define CHECK_MODE 5
#define ERROR_STATE 6

#include "main.h"
#include "button.h"
#include "software_timer.h"
#include "traffic_light.h"
#include "fsm_automatic.h"
#include "fsm_setting.h"
#include "fsm_manual.h"
#include "scheduler.h"
#include <stdio.h>
#include "i2c-lcd.h"

extern int currentState;
extern int TRANGTHAI;

void setuptrangthai();

void fsm_automatic();

extern int check;

#endif
