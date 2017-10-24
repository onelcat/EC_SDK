
#include "user_switch.h"

#define EC_ALARM_MAX 10

// 开启一次的定时开关 我会放到延时任务队列中

// 定时任务 会多次开启
typedef struct ec_alarm_t
{
	int on;  // 开关
	// | 周六 | ... | 周二 | 周一 | 周日 |
	int ing; //标识循环次数
	int hour;
	int min;
};


static int user_alarm_cout = 0;
static ec_alarm_t user_alarm[10];

// 延时任务 只会开启一次
typedef struct ec_delay_t
{
	int on; // 开关
	int delay;
	os_timer_t timer;
	ec_delay_t *next;
};


void ICACHE_FLASH_ATTR
switch_on(void *arg)
{

}

void ICACHE_FLASH_ATTR
switch_off(void *arg)
{

}

void ICACHE_FLASH_ATTR
stop_all_user_alarm()
{
	user_alarm_cout = 0;
}

void ICACHE_FLASH_ATTR
add_user_alarm(int ing, int on, int hour, int min)
{
	// 每次的增加都会重置所有的数据
	user_alarm[user_alarm_cout].ing = ing;
	user_alarm[user_alarm_cout].on = on;
	user_alarm[user_alarm_cout].hour = hour;
	user_alarm[user_alarm_cout].min = min;
	user_alarm_cout ++ ;
}

static void ICACHE_FLASH_ATTR
check_user_alarm(int wday, int hour, int min)
{
    int i = 0;
    for (i ; i < user_alarm_cout; i++)
    {
        // 表示周几
    	if( (user_alarm[i].ing >> wday) & 0x1 )
    	{
    		// 判断时间
    		if (hour == user_alarm[i].hour && min == user_alarm[i].min)
    		{
    			if(on)
	            {
		            switch_on(NULL);
	            }
	            else
	            {
		            switch_off(NULL);
	            }
    		}
    	}
    }
}

static ec_delay_t user_delay;

void ICACHE_FLASH_ATTR
add_user_delay(int on, int delay)
{

	ec_delay_t *tmp;
	tmp = os_malloc(sizoef(ec_delay_t));
	tmp->on = on;
	tmp->delay = delay;

	os_timer_disarm(tmp->timer);
	if(on)
	{
		os_timer_setfn(tmp->timer, (os_timer_func_t *)switch_on, NULL);
	}
	else
	{
        os_timer_setfn(tmp->timer, (os_timer_func_t *)switch_off, NULL);
	}
    os_timer_arm(tmp->timer, delay, 0); // ms 单位

    tmp->next = user_delay.next;
    user_delay.next = tmp;
}

void ICACHE_FLASH_ATTR
stop_all_user_delay(void)
{
	ec_delay_t *tmp = user_delay.next;
	while(tmp)
	{
		ec_delay_t *tt;
		os_timer_disarm(tmp->timer);
		tt = tmp;
		tmp = tmp->next;
	    os_free(tt);
		tt = NULL;
	}
	user_delay.next = NULL;
}