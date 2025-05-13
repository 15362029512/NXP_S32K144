/*
 * 品智科技S32K144开发板
 * 01-基础工程
 * 建立一个常用的工程,包含数个常用函数
 *
 * IO配置
 * KEY1 PTC12
 * KEY2 PTC13
 * KEY3 PTB2
 * LED1 PTD16
 * LED2 PTD15
 * LED3 PTD1
 * LED4 PTD0
*/
#include "Cpu.h"
#include "delay.h"
#include "uart.h"
#include"key.h"
#include"oled.h"
  volatile int exit_code = 0;

#define LED1(x)  PINS_DRV_WritePin(PTD,16,!x);
#define LED2(x)  PINS_DRV_WritePin(PTD,15,!x);
#define LED3(x)  PINS_DRV_WritePin(PTD,1,!x);
#define LED4(x)  PINS_DRV_WritePin(PTD,0,!x);


int main(void)
{
  /* Write your local variable definition here */
	uint8_t pinstate;
	int MCU_Freq;
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  #ifdef PEX_RTOS_INIT
    PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of Processor Expert internal initialization.                    ***/

	CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT,g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
	CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);
	MCU_Freq = delay_init();//初始化delay函数
	PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr); //初始化IO
	I2C_MasterInit(&i2c1_instance, &i2c1_MasterConfig0);//初始化I2C外设,用于OLED通讯
	LPUART_DRV_Init(INST_LPUART1, &lpuart1_State, &lpuart1_InitConfig0); //初始化串口

	oled_init(); //OLED配置参数初始化
	OLED_TITLE((uint8_t*)"S32K144",(uint8_t*)"01_BASE");//OLED显示标题
	u1_printf("初始化完毕,MCU运行频率为 %d Mhz \r\n",MCU_Freq);
    while(1)
    {
	pinstate = KEY_Proc (1);
	if(pinstate ==BTN1_PRES )
			{
			u1_printf("KEY1 按下 \r\n");
			OLED_ShowString(0,4,(uint8_t*)"KEY 1 PRESS",16,0); //OLED显示字符串
			}

		else if(pinstate ==BTN2_PRES )
			{
			u1_printf("KEY2 按下\r\n");
			OLED_ShowString(0,4,(uint8_t*)"KEY 2 PRESS",16,0);

			}
		else if(pinstate ==BTN3_PRES )
			{
			u1_printf("KEY3 按下\r\n");
			OLED_ShowString(0,4,(uint8_t*)"KEY 3 PRESS",16,0);
			}
		else
		{
			LCD_clear_L(0,4); //OLED清行
			LCD_clear_L(0,5);
		}
//    	delay_ms(100);
//    	PINS_DRV_TogglePins(PTD, 1 << 0);
//    	PINS_DRV_TogglePins(PTD, 1 << 1);
//    	PINS_DRV_TogglePins(PTD, 1 << 15);
//    	PINS_DRV_TogglePins(PTD, 1 << 16);
    }
  /*** Don't write any code pass th5is line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;) {
    if(exit_code != 0) {
      break;
    }
  }
  return exit_code;
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.1 [05.21]
**     for the NXP S32K series of microcontrollers.
**
** ###################################################################
*/
