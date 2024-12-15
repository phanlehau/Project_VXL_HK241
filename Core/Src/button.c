#include "button.h"

// Define constants for button states if not already defined

// Button state registers for debouncing
int Button1Reg0 = NORMAL_STATE, Button1Reg1 = NORMAL_STATE, Button1Reg2 = NORMAL_STATE, Button1Reg3 = NORMAL_STATE;
int Button2Reg0 = NORMAL_STATE, Button2Reg1 = NORMAL_STATE, Button2Reg2 = NORMAL_STATE, Button2Reg3 = NORMAL_STATE;
int Button3Reg0 = NORMAL_STATE, Button3Reg1 = NORMAL_STATE, Button3Reg2 = NORMAL_STATE, Button3Reg3 = NORMAL_STATE;

// Flags for button presses
int button1_flag = 0, button2_flag = 0, button3_flag = 0;


// Function to handle button input with debouncing
void getKeyInput() {
    // Button 1
    Button1Reg2 = Button1Reg1;
    Button1Reg1 = Button1Reg0;
    Button1Reg0 = HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin);

    if ((Button1Reg1 == Button1Reg0) && (Button1Reg1 == Button1Reg2)) {
        if (Button1Reg2 != Button1Reg3) {
            Button1Reg3 = Button1Reg2;
            if (Button1Reg3 == PRESSED_STATE) button1_flag = 1;
        }
    }

    // Button 2
    Button2Reg2 = Button2Reg1;
    Button2Reg1 = Button2Reg0;
    Button2Reg0 = HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin);

    if ((Button2Reg1 == Button2Reg0) && (Button2Reg1 == Button2Reg2)) {
        if (Button2Reg2 != Button2Reg3) {
            Button2Reg3 = Button2Reg2;
            if (Button2Reg3 == PRESSED_STATE) button2_flag = 1;
        }
    }

    // Button 3
    Button3Reg2 = Button3Reg1;
    Button3Reg1 = Button3Reg0;
    Button3Reg0 = HAL_GPIO_ReadPin(BUTTON3_GPIO_Port, BUTTON3_Pin);

    if ((Button3Reg1 == Button3Reg0) && (Button3Reg1 == Button3Reg2)) {
        if (Button3Reg2 != Button3Reg3) {
            Button3Reg3 = Button3Reg2;
            if (Button3Reg3 == PRESSED_STATE) button3_flag = 1;
        }
    }
}

// Function to update button press states

