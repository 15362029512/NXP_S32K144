#include "timer.h"
#include "uart.h"



static  void FTM0_IRQHandler(void);

 



static ftm_state_t ftm_struct;
s_timer_t timer_array[timer_max];



//5ms interrupt once
static void FTM0_IRQHandler(void)
{
	FTM_DRV_ClearStatusFlags(INST_FLEXTIMER_MC1,FTM_TIME_OVER_FLOW_FLAG);
	if (timer_array[timer_10ms].flg == 0)
	{
			if (timer_array[timer_10ms].cnt++ >= 2) 
			{
				timer_array[timer_10ms].cnt = 0;
				timer_array[timer_10ms].flg = 1;
			}
	}

	if (timer_array[timer_50ms].flg == 0)
	{
			if (timer_array[timer_50ms].cnt++ >= 10) 
			{
				timer_array[timer_50ms].cnt = 0;
				timer_array[timer_50ms].flg = 1;
			}
	}

	if (timer_array[timer_100ms].flg == 0)
	{
			if (timer_array[timer_100ms].cnt++ >= 20) 
			{
				timer_array[timer_100ms].cnt = 0;
				timer_array[timer_100ms].flg = 1;
			}
	}

	if (timer_array[timer_500ms].flg == 0)
	{
		if (timer_array[timer_500ms].cnt++ >= 100) 
		{
			timer_array[timer_500ms].cnt = 0;
			timer_array[timer_500ms].flg = 1;
		}
	}
}


static void  timer_array_init(s_timer_t* _timer_array)
{
	uint8_t i = 0;
	for (i = 0; i < timer_max; ++i)
	{
		_timer_array[i].cnt = 0;
		_timer_array[i].flg = 0;
	}
}

static void timer_HW_init(void)
{
	FTM_DRV_Init(INST_FLEXTIMER_MC1, &flexTimer_mc1_InitConfig,&ftm_struct);
	FTM_DRV_InitCounter(INST_FLEXTIMER_MC1, &flexTimer_mc1_TimerConfig);
	FTM_DRV_CounterStart(INST_FLEXTIMER_MC1);
	INT_SYS_InstallHandler(FTM0_Ovf_Reload_IRQn,&FTM0_IRQHandler,(isr_t*)0);
	INT_SYS_EnableIRQ(FTM0_Ovf_Reload_IRQn);
}


void timer_all_init(void)
{
	timer_array_init(timer_array);
	timer_HW_init();
}



