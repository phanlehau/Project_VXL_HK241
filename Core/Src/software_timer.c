#include "software_timer.h"
int timer_counter[10];
int timer_flag[10];
int TIMER_CYCLE = 10;

void setTimer(int number, int duration) {
    if (number >= 0 && number < 10) {  // Kiểm tra giới hạn của mảng
        timer_counter[number] = duration / TIMER_CYCLE;
        timer_flag[number] = 0;
    }
}

void timer_run() {
    for(int i = 0; i < 10; i++) {  // Sửa thành i < 10
        if(timer_counter[i] > 0) {
            timer_counter[i]--;
            if(timer_counter[i] == 0) timer_flag[i] = 1;
        }
    }
}
