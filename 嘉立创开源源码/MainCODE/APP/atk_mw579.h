/**
 ****************************************************************************************************
 * @file        atk_mw579.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2022-06-21
 * @brief       ATK-MW579模块驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32F103开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#ifndef __ATK_MW579_H
#define __ATK_MW579_H

#include "stm32f10x.h"
#include "atk_mw579_uart.h"

/* 引脚定义 */
#define ATK_MW579_STA_GPIO_PORT             GPIOA
#define ATK_MW579_STA_GPIO_PIN              GPIO_PIN_4
#define ATK_MW579_STA_GPIO_CLK_ENABLE()     do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)
#define ATK_MW579_WKUP_GPIO_PORT            GPIOA
#define ATK_MW579_WKUP_GPIO_PIN             GPIO_PIN_15
#define ATK_MW579_WKUP_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOA_CLK_ENABLE();   \
                                                __HAL_RCC_AFIO_CLK_ENABLE();    \
                                                __HAL_AFIO_REMAP_SWJ_NOJTAG();  \
                                            }while(0)

/* IO操作 */
#define ATK_MW579_READ_STA()                HAL_GPIO_ReadPin(ATK_MW579_STA_GPIO_PORT, ATK_MW579_STA_GPIO_PIN)
#define ATK_MW579_WKUP(x)                   do{ x ?                                                                                     \
                                                HAL_GPIO_WritePin(ATK_MW579_WKUP_GPIO_PORT, ATK_MW579_WKUP_GPIO_PIN, GPIO_PIN_SET) :    \
                                                HAL_GPIO_WritePin(ATK_MW579_WKUP_GPIO_PORT, ATK_MW579_WKUP_GPIO_PIN, GPIO_PIN_RESET);   \
                                            }while(0)

/* 连接状态枚举 */
typedef enum
{
    ATK_MW579_CONNECTED = 0x00,             /* 已连接 */
    ATK_MW579_DISCONNECTED,                 /* 未连接 */
} atk_mw579_conn_sta_t;

/* 发射功率枚举 */
typedef enum
{
    ATK_MW579_TPL_N20DBM = 0x00,            /* -20dBm */
    ATK_MW579_TPL_N14DBM,                   /* -14dBm */
    ATK_MW579_TPL_N8DBM,                    /* -8dBm */
    ATK_MW579_TPL_N3DBM,                    /* -3dBm */
    ATK_MW579_TPL_P0DBM,                    /* +0dBm */
    ATK_MW579_TPL_P1DBM,                    /* +1dBm */
    ATK_MW579_TPL_P2DBM,                    /* +2dBm */
    ATK_MW579_TPL_P3DBM,                    /* +3dBm */
} atk_mw579_tpl_t;

/* 串口波特率枚举 */
typedef enum
{
    ATK_MW579_UART_BAUDRATE_1200 = 0x00,    /* 1200bps */
    ATK_MW579_UART_BAUDRATE_2400,           /* 2400bps */
    ATK_MW579_UART_BAUDRATE_4800,           /* 4800bps */
    ATK_MW579_UART_BAUDRATE_9600,           /* 9600bps */
    ATK_MW579_UART_BAUDRATE_14400,          /* 14400bps */
    ATK_MW579_UART_BAUDRATE_19200,          /* 19200bps */
    ATK_MW579_UART_BAUDRATE_38400,          /* 38400bps */
    ATK_MW579_UART_BAUDRATE_43000,          /* 43000bps */
    ATK_MW579_UART_BAUDRATE_57600,          /* 57600bps */
    ATK_MW579_UART_BAUDRATE_76800,          /* 76800bps */
    ATK_MW579_UART_BAUDRATE_115200,         /* 115200bps */
    ATK_MW579_UART_BAUDRATE_128000,         /* 128000bps */
    ATK_MW579_UART_BAUDRATE_230400,         /* 230400bps */
} atk_mw579_uart_baudrate_t;

/*串口数据位枚举 */
typedef enum
{
    ATK_MW579_UART_DATA_5 = 0x00,           /* 5位数据位 */
    ATK_MW579_UART_DATA_6,                  /* 6位数据位 */
    ATK_MW579_UART_DATA_7,                  /* 7位数据位 */
    ATK_MW579_UART_DATA_8,                  /* 8位数据位 */
} atk_mw579_uart_data_t;

/* 串口校验位枚举 */
typedef enum
{
    ATK_MW579_UART_PARI_NONE = 0x00,        /* 无校验 */
    ATK_MW579_UART_PARI_ODD,                /* 奇校验 */
    ATK_MW579_UART_PARI_EVEN,               /* 偶校验 */
} atk_mw579_uart_pari_t;

/* 串口停止位枚举 */
typedef enum
{
    ATK_MW579_UART_STOP_1 = 0x00,           /* 1位停止位 */
    ATK_MW579_UART_STOP_2,                  /* 2位停止位 */
} atk_mw579_uart_stop_t;

/* 链路匹配连接枚举 */
typedef enum
{
    ATK_MW579_LINKPASSEN_ON = 0x00,         /* 使能链路匹配 */
    ATK_MW579_LINKPASSEN_OFF,               /* 关闭链路匹配 */
} atk_mw579_linkpassen_t;

/* 板载LED枚举 */
typedef enum
{
    ATK_MW579_LEDEN_ON = 0x00,              /* 使能板载LED */
    ATK_MW579_LEDEN_OFF,                    /* 关闭板载LED */
} atk_mw579_leden_t;

/* 从设备断连睡眠枚举 */
typedef enum
{
    ATK_MW579_SLAVESLEEPEN_ON = 0x00,       /* 使能从设备断连睡眠 */
    ATK_MW579_SLAVESLEEPEN_OFF,             /* 关闭从设备断连睡眠 */
} atk_mw579_slavesleepen_t;

/* 通信最大输出枚举 */
typedef enum
{
    ATK_MW579_MAXPUT_ON = 0x00,             /* 使能通信最大输出 */
    ATK_MW579_MAXPUT_OFF,                   /* 关闭通信最大输出 */
} atk_mw579_maxput_t;

/* 工作模式枚举 */
typedef enum
{
    ATK_MW579_MODE_M = 0x00,                /* 主设备模式 */
    ATK_MW579_MODE_S,                       /* 从设备模式 */
    ATK_MW579_MODE_O,                       /* 观察者模式 */
    ATK_MW579_MODE_B,                       /* 广播者模式 */
    ATK_MW579_MODE_I,                       /* iBeacon模式 */
} atk_mw579_mode_t;

/* 自动睡眠枚举 */
typedef enum
{
    ATK_MW579_AUTOSLEEPEN_ON = 0x00,        /* 使能自动睡眠 */
    ATK_MW579_AUTOSLEEPEN_OFF,              /* 关闭自动睡眠 */
} atk_mw579_autosleepen_t;

/* 自动睡眠模式枚举 */
typedef enum
{
    ATK_MW579_AUTOSLEEP_LOW = 0x00,         /* 浅睡眠 */
    ATK_MW579_AUTOSLEEP_DEEP,               /* 深度睡眠 */
} atk_mw579_autosleep_t;

/* 上电睡眠枚举 */
typedef enum
{
    ATK_MW579_POWERSLEEPEN_ON = 0x00,       /* 使能上电睡眠 */
    ATK_MW579_POWERSLEEPEN_OFF,             /* 关闭上电睡眠 */
} atk_mw579_powersleepen_t;

/* 错误代码 */
#define ATK_MW579_EOK      0                /* 没有错误 */
#define ATK_MW579_ERROR    1                /* 错误 */
#define ATK_MW579_ETIMEOUT 2                /* 超时错误 */
#define ATK_MW579_EINVAL   3                /* 参数错误 */

/* 操作函数 */
uint8_t atk_mw579_init(atk_mw579_uart_baudrate_t baudrate);                                                                                         /* ATK-MW579初始化 */
atk_mw579_conn_sta_t atk_mw579_get_conn_sta(void);                                                                                                  /* 获取ATK-MW579连接状态 */
uint8_t atk_mw579_send_at_cmd(char *cmd, char *ack, uint32_t timeout);                                                                              /* ATK-MW579发送AT指令 */
uint8_t atk_mw579_enter_config_mode(void);                                                                                                          /* ATK-MW579进入配置模式 */
uint8_t atk_mw579_at_test(void);                                                                                                                    /* ATK-MW579 AT指令测试 */
uint8_t atk_mw579_set_name(char *name);                                                                                                             /* 设置ATK-MW579蓝牙名称 */
uint8_t atk_mw579_set_hello(char *hello);                                                                                                           /* 设置ATK-MW579开机欢迎语 */
uint8_t atk_mw579_set_tpl(atk_mw579_tpl_t tpl);                                                                                                     /* 设置ATK-MW579发射功率 */
uint8_t atk_mw579_set_uart(atk_mw579_uart_baudrate_t baudrate, atk_mw579_uart_data_t data, atk_mw579_uart_pari_t pari, atk_mw579_uart_stop_t stop); /* 设置ATK-MW579串口参数 */
uint8_t atk_mw579_set_adptim(uint16_t adptim);                                                                                                      /* 设置ATK-MW579广播速度 */
uint8_t atk_mw579_set_linkpassen(atk_mw579_linkpassen_t linkpassen);                                                                                /* 设置ATK-MW579链路匹配 */
uint8_t atk_mw579_set_leden(atk_mw579_leden_t leden);                                                                                               /* 设置ATK-MW579板载LED */
uint8_t atk_mw579_set_slavesleepen(atk_mw579_slavesleepen_t slavesleepen);                                                                          /* 设置ATK-MW579从设备断连睡眠 */
uint8_t atk_mw579_set_maxput(atk_mw579_maxput_t maxput);                                                                                            /* 设置ATK-MW579通信最大输出 */
uint8_t atk_mw579_set_mode(atk_mw579_mode_t mode);                                                                                                  /* 设置ATK-MW579工作模式 */
uint8_t atk_mw579_scan_slave(void);                                                                                                                 /* ATK-MW579扫描周围从设备 */
uint8_t atk_mw579_conn_slave(uint8_t id);                                                                                                           /* ATK-MW579连接周围从设备 */
uint8_t atk_mw579_enter_unvarnished(void);                                                                                                          /* ATK-MW579进入透传 */
uint8_t atk_mw579_set_linkpass(char *pass);                                                                                                         /* 设置ATK-MW579链路匹配密码 */
uint8_t atk_mw579_set_autosleepen(atk_mw579_autosleepen_t autosleepen, uint8_t autotim);                                                            /* 设置ATK-MW579自动睡眠 */
uint8_t atk_mw579_set_autosleep(atk_mw579_autosleep_t autosleep);                                                                                   /* 设置ATK-MW579自动睡眠模式 */
uint8_t atk_mw579_set_powersleepen(atk_mw579_powersleepen_t powersleepen);                                                                          /* 设置ATK-MW579上电睡眠 */
uint8_t atk_mw579_set_ibeacon(char *uuid, uint16_t major, uint16_t minor, uint8_t rssi);                                                            /* 设置ATK-MW579 iBeacon */
void atk_mw579_wakeup_by_pin(void);                                                                                                                 /* 通过WKUP引脚唤醒ATK-MW579 */
void atk_mw579_wakeup_by_uart(void);                                                                                                                /* 通过UART唤醒ATK-MW579 */

#endif
