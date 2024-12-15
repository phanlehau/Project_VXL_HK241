#include "fsm_automatic.h"

void init_automatic()
{
    //setup timer
	setTimer (0 ,1000);
	//setup đèn giao thông
	HAL_GPIO_WritePin(BIT0_LED1_GPIO_Port, BIT0_LED1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BIT1_LED1_GPIO_Port, BIT1_LED1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BIT0_LED2_GPIO_Port, BIT0_LED2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BIT1_LED2_GPIO_Port, BIT1_LED2_Pin, GPIO_PIN_RESET);
	status1 = DO;
	status2 = XANH;
	HAL_GPIO_WritePin(BIT0_LED1_GPIO_Port, BIT0_LED1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(BIT1_LED1_GPIO_Port, BIT1_LED1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(BIT0_LED2_GPIO_Port, BIT0_LED2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(BIT1_LED2_GPIO_Port, BIT1_LED2_Pin, GPIO_PIN_RESET);
	counter1 = 0;
	counter2 = 0;

	lcd_clear_display();
	lcd_goto_XY (1,0);
	lcd_send_string(" TIME DO  :");
    lcd_goto_XY (1,12);
    lcd_send_number(timeDO);

	lcd_goto_XY (2,0);
	lcd_send_string("TIME XANH :");
    lcd_goto_XY (2,12);
    lcd_send_number(timeXANH);

}


void fsm_automatic()
{
	if(TRANGTHAI == 0 )
		{
	    if (timer_flag[0] == 1) {
	        switch(status1) {
	            case DO:
	                counter1++;
	                if (counter1 >= timeDO) {
	                    // Switch to green
	                	HAL_GPIO_WritePin(BIT0_LED1_GPIO_Port, BIT0_LED1_Pin, GPIO_PIN_SET);
	                	HAL_GPIO_WritePin(BIT1_LED1_GPIO_Port, BIT1_LED1_Pin, GPIO_PIN_RESET);
	                    status1 = XANH;
	                    counter1 = 0;
	                }
	                break;
	            case XANH:
	                counter1++;
	                if (counter1 >= timeXANH) {
	                    // Switch to yellow
	                	HAL_GPIO_WritePin(BIT0_LED1_GPIO_Port, BIT0_LED1_Pin, GPIO_PIN_RESET);
	                	HAL_GPIO_WritePin(BIT1_LED1_GPIO_Port, BIT1_LED1_Pin, GPIO_PIN_SET);
	                    status1 = VANG;
	                    counter1 = 0;
	                }
	                break;
	            case VANG:
	                counter1++;
	                if (counter1 >= (timeDO - timeXANH)) {
	                    // Switch to red
	                	HAL_GPIO_WritePin(BIT0_LED1_GPIO_Port, BIT0_LED1_Pin, GPIO_PIN_SET);
	                	HAL_GPIO_WritePin(BIT1_LED1_GPIO_Port, BIT1_LED1_Pin, GPIO_PIN_SET);
	                    status1 = DO;
	                    counter1 = 0;
	                }
	                break;
	            default:
	                break;
	        }

	        switch(status2) {
	            case DO:
	                counter2++;
	                if (counter2 >= timeDO) {
	                	HAL_GPIO_WritePin(BIT0_LED2_GPIO_Port, BIT0_LED2_Pin, GPIO_PIN_SET);
	                	HAL_GPIO_WritePin(BIT1_LED2_GPIO_Port, BIT1_LED2_Pin, GPIO_PIN_RESET);
	                    status2 = XANH;
	                    counter2 = 0;
	                }
	                break;
	            case XANH:
	                counter2++;
	                if (counter2 >= timeXANH) {
	                	HAL_GPIO_WritePin(BIT0_LED2_GPIO_Port, BIT0_LED2_Pin, GPIO_PIN_RESET);
	                	HAL_GPIO_WritePin(BIT1_LED2_GPIO_Port, BIT1_LED2_Pin, GPIO_PIN_SET);
	                    status2 = VANG;
	                    counter2 = 0;
	                }
	                break;
	            case VANG:
	                counter2++;
	                if (counter2 >= (timeDO - timeXANH)) {
	                	HAL_GPIO_WritePin(BIT0_LED2_GPIO_Port, BIT0_LED2_Pin, GPIO_PIN_SET);
	                	HAL_GPIO_WritePin(BIT1_LED2_GPIO_Port, BIT1_LED2_Pin, GPIO_PIN_SET);
	                    status2 = DO;
	                    counter2 = 0;
	                }
	                break;
	            default:
	                break;
	        }

	        countdown1 = (status1 == DO) ? (timeDO - counter1) :
	                     (status1 == VANG) ? (timeDO - timeXANH - counter1) :
	                     (timeXANH - counter1);

	        countdown2 = (status2 == DO) ? (timeDO - counter2) :
	                     (status2 == VANG) ? (timeDO - timeXANH - counter2) :
	                     (timeXANH - counter2);


	        lcd_clear_display();
	        lcd_goto_XY (1,0);
	        if(status1 == DO) lcd_send_string(" TIME DO  :");
	        else if(status1 == XANH) lcd_send_string("TIME XANH :");
	        else lcd_send_string("TIME VANG :");
	        lcd_goto_XY (1,12);
	        lcd_send_number(countdown1);


	        lcd_goto_XY (2,0);
	        if(status2 == DO) lcd_send_string(" TIME DO  :");
	        else if(status2 == XANH) lcd_send_string("TIME XANH :");
	        else lcd_send_string("TIME VANG :");
	        lcd_goto_XY (2,12);
	        lcd_send_number(countdown2);
	        // Reset timer for traffic light logic
	        setTimer(0, 1000);
	    }
		}
}
