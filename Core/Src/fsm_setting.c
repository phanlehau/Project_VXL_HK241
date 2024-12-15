#include"fsm_setting.h"
	uint8_t check_denxanh = 0;
	uint8_t check_denvang = 0;
void init_setting()
{
	HAL_GPIO_WritePin(BIT0_LED1_GPIO_Port, BIT0_LED1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BIT1_LED1_GPIO_Port, BIT1_LED1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BIT0_LED2_GPIO_Port, BIT0_LED2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BIT1_LED2_GPIO_Port, BIT1_LED2_Pin, GPIO_PIN_RESET);
	currentState = DO;
	HAL_GPIO_WritePin(BIT0_LED1_GPIO_Port, BIT0_LED1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(BIT1_LED1_GPIO_Port, BIT1_LED1_Pin, GPIO_PIN_SET);
	setTimer (2 ,250 );
	check_denxanh = 0;
	check_denvang = 0;

	lcd_clear_display();
    lcd_goto_XY (1,1);
    lcd_send_string("CHE DO SETTING");
    lcd_goto_XY (2,0);
    lcd_send_string(" TIME DO  :");
    lcd_goto_XY (2,12);
    lcd_send_number(timeDO);

}
void fsm_setting()
{

    if((TRANGTHAI == 2 || TRANGTHAI == 3 || TRANGTHAI == 4))
    {
    if(button2_flag || button3_flag)
    {
    if (button2_flag == 1) { // btnB Pressed
    	                   // chinh tang time do
    			if(currentState == DO)
    			{

    			           timeDO++;
    			}
    			           // chinh tang time xanh
    			else if (currentState == XANH)
    			{
    				      timeXANH++;

    			}
    			else
    			{
    				      timeVANG++;
    			}
    			button2_flag = 0;
    		      }
    else if (button3_flag == 1) { // btnB Pressed
    	                   // chinh giam time do
    			if(currentState == DO)
    			{

    			           timeDO--;
    			}
    			           // chinh tang time xanh
    			else if (currentState == XANH)
    			{
    				      timeXANH--;

    			}
    			else
    			{
    				      timeVANG--;
    			}

    			button3_flag = 0;
    		  	  }

    countdown2 = (currentState == DO) ? timeDO :
                 (currentState == VANG) ? timeVANG :
                		 timeXANH;

	lcd_clear_display();
    lcd_goto_XY (1,1);
    lcd_send_string("CHE DO SETTING");
    lcd_goto_XY (2,0);
    if(currentState == DO) lcd_send_string(" TIME DO  :");
    else if(currentState == XANH) lcd_send_string("TIME XANH :");
    else lcd_send_string("TIME VANG :");
    lcd_goto_XY (2,12);
    lcd_send_number(countdown2);

    }

	// nhap nhay den
	if(timer_flag[2] == 1)
	{
	if(currentState == DO)
	{
      HAL_GPIO_TogglePin(BIT0_LED1_GPIO_Port, BIT0_LED1_Pin);
      HAL_GPIO_TogglePin(BIT1_LED1_GPIO_Port, BIT1_LED1_Pin);
	}
	else if (currentState == XANH)
	{
          if(check_denxanh == 0)
          {
        		HAL_GPIO_WritePin(BIT0_LED1_GPIO_Port, BIT0_LED1_Pin, GPIO_PIN_RESET);
        		HAL_GPIO_WritePin(BIT1_LED1_GPIO_Port, BIT1_LED1_Pin, GPIO_PIN_RESET);
        		check_denxanh = 1;
          }
          else
          {
      		HAL_GPIO_WritePin(BIT0_LED1_GPIO_Port, BIT0_LED1_Pin, GPIO_PIN_SET);
      		HAL_GPIO_WritePin(BIT1_LED1_GPIO_Port, BIT1_LED1_Pin, GPIO_PIN_RESET);
      		check_denxanh = 0;
          }
	}
	else
	{
        if(check_denvang == 0)
        {
      		HAL_GPIO_WritePin(BIT0_LED1_GPIO_Port, BIT0_LED1_Pin, GPIO_PIN_RESET);
      		HAL_GPIO_WritePin(BIT1_LED1_GPIO_Port, BIT1_LED1_Pin, GPIO_PIN_RESET);
      		check_denvang = 1;
        }
        else
        {
    		HAL_GPIO_WritePin(BIT0_LED1_GPIO_Port, BIT0_LED1_Pin, GPIO_PIN_RESET);
    		HAL_GPIO_WritePin(BIT1_LED1_GPIO_Port, BIT1_LED1_Pin, GPIO_PIN_SET);
    		check_denvang = 0;
        }
	}
	setTimer (2 ,250 );
	}

    }
}
