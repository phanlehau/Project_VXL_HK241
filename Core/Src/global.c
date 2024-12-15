#include "global.h"
int currentState;
int TRANGTHAI = 0;
int check = 1;
void setuptrangthai()
{
	 switch(TRANGTHAI) {
	          case AUTOMATIC:
	              if(check == 1)
	             {
	            	  init_automatic();
	            	  check = 0;
	             }
	             // fsm_automatic();
	              break;
	          case MANUAL:
	              if(check == 1)
	              {
	            	  init_manual();
	            	  check = 0;
	              }
	             // fsm_manual();
	              break;
	          case SET_DO:
	              if(check == 1)
	              {
	            	  init_setting();
	            	  check = 0;
	              }
	             // fsm_setting();
	              break;
	          case SET_XANH:
	              if(check == 1)
	             {
	        	  currentState = XANH;
	        		lcd_clear_display();
	        	    lcd_goto_XY (1,1);
	        	    lcd_send_string("CHE DO SETTING");
	        	    lcd_goto_XY (2,0);
	        	    lcd_send_string("TIME XANH :");
	        	    lcd_goto_XY (2,12);
	        	    lcd_send_number(timeXANH);
	            	  check = 0;
	             }
	        	 // fsm_setting();
	              break;
	          case SET_VANG:
	              if(check == 1)
	             {
	        	  currentState = VANG;
	        		lcd_clear_display();
	        	    lcd_goto_XY (1,1);
	        	    lcd_send_string("CHE DO SETTING");
	        	    lcd_goto_XY (2,0);
	        	    lcd_send_string("TIME VANG :");
	        	    lcd_goto_XY (2,12);
	        	    lcd_send_number(timeVANG);
	            	  check = 0;
	             }
	        	 // fsm_setting();
	              break;
	          case CHECK_MODE:
	              if(check == 1)
	              {
	                if(timeDO == timeXANH + timeVANG)TRANGTHAI = 0;
	                else TRANGTHAI = 6;
	              }
	              break;
	          case ERROR_STATE:
	              if(check == 1)
	              {
	            	  	 // hien thi tren man hinh lcd

	            		HAL_GPIO_WritePin(BIT0_LED1_GPIO_Port, BIT0_LED1_Pin, GPIO_PIN_RESET);
	            		HAL_GPIO_WritePin(BIT1_LED1_GPIO_Port, BIT1_LED1_Pin, GPIO_PIN_RESET);
	            		HAL_GPIO_WritePin(BIT0_LED2_GPIO_Port, BIT0_LED2_Pin, GPIO_PIN_RESET);
	            		HAL_GPIO_WritePin(BIT1_LED2_GPIO_Port, BIT1_LED2_Pin, GPIO_PIN_RESET);

	            		lcd_clear_display();
	            	    lcd_goto_XY (1,2);
	            	    lcd_send_string("THIEI LAP LOI");
	            	    lcd_goto_XY (2,2);
	            	    lcd_send_string("RESET TIME!");

	               		timeDO = 5;
	               		timeXANH = 3;
	               		timeVANG = 2;
	               		check = 0;
	              }
	              break;
	          default:
	              break;
	      }
     if(button1_flag == 1)
     {

         check = 1;

    	 if(TRANGTHAI < 5)TRANGTHAI++;
    	 else TRANGTHAI = 0;
    	 button1_flag = 0;
     }
}
