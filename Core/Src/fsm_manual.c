#include "fsm_manual.h"

// Khai báo biến lưu trạng thái đèn tín hiệu và nút bấm
uint8_t red_led_state1, red_led_state2;

void init_manual()
{


	HAL_GPIO_WritePin(BIT0_LED1_GPIO_Port, BIT0_LED1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BIT1_LED1_GPIO_Port, BIT1_LED1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BIT0_LED2_GPIO_Port, BIT0_LED2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BIT1_LED2_GPIO_Port, BIT1_LED2_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(BIT0_LED1_GPIO_Port, BIT0_LED1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(BIT1_LED1_GPIO_Port, BIT1_LED1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(BIT0_LED2_GPIO_Port, BIT0_LED2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(BIT1_LED2_GPIO_Port, BIT1_LED2_Pin, GPIO_PIN_RESET);

	lcd_clear_display();
    lcd_goto_XY (1,2);
    lcd_send_string("CHE DO MANUAL");

}

void fsm_manual()
{
	if(TRANGTHAI == 1)
	{
		if(HAL_GPIO_ReadPin(BIT0_LED1_GPIO_Port, BIT0_LED1_Pin) && HAL_GPIO_ReadPin(BIT1_LED1_GPIO_Port, BIT1_LED1_Pin)) red_led_state1 = 1;
		else red_led_state1 = 0;
		if(HAL_GPIO_ReadPin(BIT0_LED2_GPIO_Port, BIT0_LED2_Pin) && HAL_GPIO_ReadPin(BIT1_LED2_GPIO_Port, BIT1_LED2_Pin)) red_led_state2 = 1;
		else red_led_state2 = 0;
    // Đọc trạng thái của các đèn tín hiệu
    // Xử lý nút nhấn 2
    if (button2_flag == 1) // Nếu nút nhấn 2 được nhấn và chưa được xử lý
    {
        if (red_led_state2 == 1) // Nếu RED_LED2 đang sáng
        {
            // Nếu GREEN_LED1 đang sáng, chuyển sang YELLOW
            if (HAL_GPIO_ReadPin(BIT0_LED1_GPIO_Port, BIT0_LED1_Pin) == GPIO_PIN_SET)
            {
            	HAL_GPIO_WritePin(BIT0_LED1_GPIO_Port, BIT0_LED1_Pin, GPIO_PIN_RESET);
            	HAL_GPIO_WritePin(BIT1_LED1_GPIO_Port, BIT1_LED1_Pin, GPIO_PIN_SET);
            }
            // Nếu YELLOW_LED1 đang sáng, chuyển sang RED
            else if (HAL_GPIO_ReadPin(BIT1_LED1_GPIO_Port, BIT1_LED1_Pin) == GPIO_PIN_SET)
            {
            	HAL_GPIO_WritePin(BIT0_LED1_GPIO_Port, BIT0_LED1_Pin, GPIO_PIN_SET);
            	HAL_GPIO_WritePin(BIT1_LED1_GPIO_Port, BIT1_LED1_Pin, GPIO_PIN_SET);
            	HAL_GPIO_WritePin(BIT0_LED2_GPIO_Port, BIT0_LED2_Pin, GPIO_PIN_SET);
            	HAL_GPIO_WritePin(BIT1_LED2_GPIO_Port, BIT1_LED2_Pin, GPIO_PIN_RESET);
            }
        }
        button2_flag = 0;
    }

    // Xử lý nút nhấn 3
    if (button3_flag == 1) // Nếu nút nhấn 3 được nhấn và chưa được xử lý
    {
        if (red_led_state1 == 1) // Nếu RED_LED1 đang sáng
        {
            // Nếu GREEN_LED2 đang sáng, chuyển sang YELLOW
            if (HAL_GPIO_ReadPin(BIT0_LED2_GPIO_Port, BIT0_LED2_Pin) == GPIO_PIN_SET)
            {
            	HAL_GPIO_WritePin(BIT0_LED2_GPIO_Port, BIT0_LED2_Pin, GPIO_PIN_RESET);
            	HAL_GPIO_WritePin(BIT1_LED2_GPIO_Port, BIT1_LED2_Pin, GPIO_PIN_SET);
            }
            // Nếu YELLOW_LED1 đang sáng, chuyển sang RED
            else if (HAL_GPIO_ReadPin(BIT1_LED2_GPIO_Port, BIT1_LED2_Pin) == GPIO_PIN_SET)
            {
            	HAL_GPIO_WritePin(BIT0_LED2_GPIO_Port, BIT0_LED2_Pin, GPIO_PIN_SET);
            	HAL_GPIO_WritePin(BIT1_LED2_GPIO_Port, BIT1_LED2_Pin, GPIO_PIN_SET);
            	HAL_GPIO_WritePin(BIT0_LED1_GPIO_Port, BIT0_LED1_Pin, GPIO_PIN_SET);
            	HAL_GPIO_WritePin(BIT1_LED1_GPIO_Port, BIT1_LED1_Pin, GPIO_PIN_RESET);
            }
        }
        button3_flag = 0;
        }
    }

	}
