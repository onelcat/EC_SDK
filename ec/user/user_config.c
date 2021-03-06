
#include "user_interface.h"
#include "user_config.h"
#include "user_debug.h"
#include "jabber_config.h"
#include "spi_flash.h"
#include "osapi.h"
#include "user_debug.h"
#include "wifi.h"

#ifdef HTTP_DEBUG_ON
char log_buffer[1024];
#endif

static int user_isRegisrer = 0;

/// 保存用户配置信息
void ICACHE_FLASH_ATTR
CFG_Save(void)
{
	// TODO: 保存用户配置信息

	spi_flash_erase_sector(CFG_LOCATION + 0);
	spi_flash_erase_sector(CFG_LOCATION + 1);
    user_isRegisrer = 1;
	// MARK: 保存注册信息
	// MARK: 保存XMPP配置信息
	if (user_isRegisrer == 1)
	{
		spi_flash_write((CFG_LOCATION + 0) * SPI_FLASH_SEC_SIZE,
						(uint32 *)&user_isRegisrer, sizeof(user_isRegisrer));

		spi_flash_write((CFG_LOCATION + 1) * SPI_FLASH_SEC_SIZE,
						(uint32 *)&j_config, sizeof(j_config));

        spi_flash_write((CFG_LOCATION + 2) * SPI_FLASH_SEC_SIZE,
						(uint32 *)&w_config, sizeof(w_config));
	}
}

/// 加载用户配置信息
void ICACHE_FLASH_ATTR
CFG_Load(void)
{
	// TODO: 读取用户配置信息
	user_isRegisrer = 0;
	spi_flash_read((CFG_LOCATION + 0) * SPI_FLASH_SEC_SIZE,
				   (uint32 *)&user_isRegisrer, sizeof(user_isRegisrer));
	os_memset(&j_config, 0x0, sizeof(j_config));
	spi_flash_read((CFG_LOCATION + 1) * SPI_FLASH_SEC_SIZE,
				   (uint32 *)&j_config, sizeof(j_config));
    
    os_memset(&w_config, 0x0, sizeof(w_config));
	spi_flash_read((CFG_LOCATION + 2) * SPI_FLASH_SEC_SIZE,
						(uint32 *)&w_config, sizeof(w_config));
}

/// 判断客户端是否被用户注册(也就是绑定) - 复位的时候才会发生值的一个变化
int ICACHE_FLASH_ATTR
user_get_is_regisrer(void)
{
	return user_isRegisrer;
}

int ICACHE_FLASH_ATTR
get_random_string(int length, char *ouput)
{
	int flag, i;
	// srand((unsigned)time(NULL));
	for (i = 0; i < length - 1; i++)
	{
		flag = os_random() % 3;
		switch (flag)
		{
		case 0:
			ouput[i] = 'A' + os_random() % 26;
			break;
		case 1:
			ouput[i] = 'a' + os_random() % 26;
			break;
		case 2:
			ouput[i] = '0' + os_random() % 10;
			break;
		default:
			ouput[i] = 'x';
			break;
		}
	}
	return 0;
}