#ifndef __USER_CONFIG_H__
#define __USER_CONFIG_H__

#include "user_interface.h"

#define AP_DEFINE_NAME_RAND_LEN 5
#define AP_DEFINE_NAME "WSLP_"
#define AP_DEFINE_PASSWORD "12345678"

/// 支持AT指令
#define AT_CUSTOM 1

/// LOG信息输出模式
#define DEBUG_ON 1

#define XMPP_DEBUG_ON 1

#define HTTP_DEBUG_ON 1

#define ESPCONN_DEBUG_ON 1

#define WIFI_DEBUG_ON 1

/// 用户信息存储起始位置
#define CFG_LOCATION 0xD0

void CFG_Save(void);
void CFG_Load(void);
int ICACHE_FLASH_ATTR user_get_is_regisrer(void);
#include "jabber_config.h"
void ICACHE_FLASH_ATTR xmpp_init(struct jabber_config *config);
void ICACHE_FLASH_ATTR timer_init(void);
#endif