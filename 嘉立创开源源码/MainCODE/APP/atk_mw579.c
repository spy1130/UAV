/**
 ****************************************************************************************************
 * @file        atk_mw579.c
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

#include "atk_mw579.h"
#include "delay.h"
#include <string.h>
#include <stdio.h>

/* ATK-MW579数据结构体 */
static struct
{
    atk_mw579_uart_baudrate_t baudrate;
} g_atk_mw579_sta;

/**
 * @brief       ATK-MW579硬件初始化
 * @param       无
 * @retval      无
 */
static void atk_mw579_hw_init(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    /* 使能时钟 */
    ATK_MW579_STA_GPIO_CLK_ENABLE();
    ATK_MW579_WKUP_GPIO_CLK_ENABLE();
    
    /* 初始化STA引脚 */
    gpio_init_struct.Pin    = ATK_MW579_STA_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_INPUT;
    gpio_init_struct.Pull   = GPIO_PULLDOWN;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ATK_MW579_STA_GPIO_PORT, &gpio_init_struct);
    
    /* 初始化WKUP引脚 */
    gpio_init_struct.Pin    = ATK_MW579_WKUP_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ATK_MW579_WKUP_GPIO_PORT, &gpio_init_struct);
    
    ATK_MW579_WKUP(1);
}

/**
 * @brief       ATK-MW579初始化
 * @param       buadrate: ATK-MW579 UART通讯波特率
 * @retval      ATK_MW579_EOK  : ATK-MW579初始化成功
 *              ATK_MW579_ERROR: ATK-MW579初始化失败
 */
uint8_t atk_mw579_init(atk_mw579_uart_baudrate_t baudrate)
{
    uint8_t ret;
    uint32_t _baudrate;
    
    switch (baudrate)
    {
        case ATK_MW579_UART_BAUDRATE_1200:
        {
            _baudrate = 1200;
            break;
        }
        case ATK_MW579_UART_BAUDRATE_2400:
        {
            _baudrate = 2400;
            break;
        }
        case ATK_MW579_UART_BAUDRATE_4800:
        {
            _baudrate = 4800;
            break;
        }
        case ATK_MW579_UART_BAUDRATE_9600:
        {
            _baudrate = 9600;
            break;
        }
        case ATK_MW579_UART_BAUDRATE_14400:
        {
            _baudrate = 14400;
            break;
        }
        case ATK_MW579_UART_BAUDRATE_19200:
        {
            _baudrate = 19200;
            break;
        }
        case ATK_MW579_UART_BAUDRATE_38400:
        {
            _baudrate = 38400;
            break;
        }
        case ATK_MW579_UART_BAUDRATE_43000:
        {
            _baudrate = 43000;
            break;
        }
        case ATK_MW579_UART_BAUDRATE_57600:
        {
            _baudrate = 57600;
            break;
        }
        case ATK_MW579_UART_BAUDRATE_76800:
        {
            _baudrate = 76800;
            break;
        }
        case ATK_MW579_UART_BAUDRATE_115200:
        {
            _baudrate = 115200;
            break;
        }
        case ATK_MW579_UART_BAUDRATE_128000:
        {
            _baudrate = 1200;
            break;
        }
        case ATK_MW579_UART_BAUDRATE_230400:
        {
            _baudrate = 230400;
            break;
        }
        default:
        {
            return ATK_MW579_EINVAL;
        }
    }
    
    atk_mw579_hw_init();
    atk_mw579_uart_init(_baudrate);
    atk_mw579_enter_config_mode();
    ret = atk_mw579_at_test();
    if (ret != ATK_MW579_EOK)
    {
        return ATK_MW579_ERROR;
    }
    
    g_atk_mw579_sta.baudrate = baudrate;
    
    return ATK_MW579_EOK;
}

/**
 * @brief       获取ATK-MW579连接状态
 * @param       无
 * @retval      ATK_MW579_CONNECTED   : 已连接
 *              ATK_MW579_DISCONNECTED: 未连接
 */
atk_mw579_conn_sta_t atk_mw579_get_conn_sta(void)
{
    if (ATK_MW579_READ_STA() != 0)
    {
        return ATK_MW579_DISCONNECTED;
    }
    
    return ATK_MW579_CONNECTED;
}

/**
 * @brief       ATK-MW579发送AT指令
 * @param       cmd    : 待发送的AT指令
 *              ack    : 等待的响应
 *              timeout: 等待超时时间
 * @retval      ATK_MW579_EOK     : 函数执行成功
 *              ATK_MW579_ETIMEOUT: 等待期望应答超时，函数执行失败
 */
uint8_t atk_mw579_send_at_cmd(char *cmd, char *ack, uint32_t timeout)
{
    uint8_t *ret = NULL;
    
    atk_mw579_uart_rx_restart();
    atk_mw579_uart_printf("%s\r\n", cmd);
    
    if ((ack == NULL) || (timeout == 0))
    {
        return ATK_MW579_EOK;
    }
    else
    {
        while (timeout > 0)
        {
            ret = atk_mw579_uart_rx_get_frame();
            if (ret != NULL)
            {
                if (strstr((const char *)ret, ack) != NULL)
                {
                    return ATK_MW579_EOK;
                }
                else
                {
                    atk_mw579_uart_rx_restart();
                }
            }
            timeout--;
            delay_ms(1);
        }
        
        return ATK_MW579_ETIMEOUT;
    }
}

/**
 * @brief       ATK-MW579进入配置模式
 * @param       无
 * @retval      ATK_MW579_EOK  : ATK-MW579进入配置模式成功
 *              ATK_MW579_ERROR: ATK-MW579进入配置模式失败
 */
uint8_t atk_mw579_enter_config_mode(void)
{
    uint8_t ret;
    
    ret = atk_mw579_send_at_cmd("+++a", "a+ok", 1000);
    if (ret != ATK_MW579_EOK)
    {
        return ATK_MW579_ERROR;
    }
    
    return ATK_MW579_EOK;
}

/**
 * @brief       ATK-MW579 AT指令测试
 * @param       无
 * @retval      ATK_MW579_EOK  : AT指令测试成功
 *              ATK_MW579_ERROR: AT指令测试失败
 */
uint8_t atk_mw579_at_test(void)
{
    uint8_t ret;
    uint8_t loop;
    
    for (loop=0; loop<10; loop++)
    {
        ret = atk_mw579_send_at_cmd("AT", "OK", 100);
        if (ret == ATK_MW579_EOK)
        {
            return ATK_MW579_EOK;
        }
    }
    
    return ATK_MW579_ERROR;
}

/**
 * @brief       设置ATK-MW579蓝牙名称
 * @param       name: 蓝牙名称
 * @retval      ATK_MW579_EOK  : 设置ATK-MW579蓝牙名称成功
 *              ATK_MW579_ERROR: 设置ATK-MW579蓝牙名称失败
 */
uint8_t atk_mw579_set_name(char *name)
{
    uint8_t ret;
    char cmd[64];
    
    sprintf(cmd, "AT+NAME=%s", name);
    ret = atk_mw579_send_at_cmd(cmd, "OK", 100);
    if (ret != ATK_MW579_EOK)
    {
        return ATK_MW579_ERROR;
    }
    
    return ATK_MW579_EOK;
}

/**
 * @brief       设置ATK-MW579开机欢迎语
 * @param       hello: 开机欢迎语
 * @retval      ATK_MW579_EOK  : 设置ATK-MW579开机欢迎语成功
 *              ATK_MW579_ERROR: 设置ATK-MW579开机欢迎语失败
 */
uint8_t atk_mw579_set_hello(char *hello)
{
    uint8_t ret;
    char cmd[64];
    
    sprintf(cmd, "AT+HELLO=%s", hello);
    ret = atk_mw579_send_at_cmd(cmd, "OK", 100);
    if (ret != ATK_MW579_EOK)
    {
        return ATK_MW579_ERROR;
    }
    
    return ATK_MW579_EOK;
}

/**
 * @brief       设置ATK-MW579发射功率
 * @param       tpl: ATK_MW579_TPL_N20DBM: -20dBm
 *                   ATK_MW579_TPL_N14DBM: -14dBm
 *                   ATK_MW579_TPL_N8DBM : -8dBm
 *                   ATK_MW579_TPL_N3DBM : -3dBm
 *                   ATK_MW579_TPL_P0DBM : +0dBm
 *                   ATK_MW579_TPL_P1DBM : +1dBm
 *                   ATK_MW579_TPL_P2DBM : +2dBm
 *                   ATK_MW579_TPL_P3DBM : +3dBm
 * @retval      ATK_MW579_EOK   : 设置ATK-MW579发射功率成功
 *              ATK_MW579_ERROR : 设置ATK-MW579发射功率失败
 *              ATK_MW579_EINVAL: 函数参数错误
 */
uint8_t atk_mw579_set_tpl(atk_mw579_tpl_t tpl)
{
    uint8_t ret;
    uint8_t _tpl;
    char cmd[9];
    
    switch (tpl)
    {
        case ATK_MW579_TPL_N20DBM:
        {
            _tpl = 1;
            break;
        }
        case ATK_MW579_TPL_N14DBM:
        {
            _tpl = 2;
            break;
        }
        case ATK_MW579_TPL_N8DBM:
        {
            _tpl = 3;
            break;
        }
        case ATK_MW579_TPL_N3DBM:
        {
            _tpl = 4;
            break;
        }
        case ATK_MW579_TPL_P0DBM:
        {
            _tpl = 5;
            break;
        }
        case ATK_MW579_TPL_P1DBM:
        {
            _tpl = 6;
            break;
        }
        case ATK_MW579_TPL_P2DBM:
        {
            _tpl = 7;
            break;
        }
        case ATK_MW579_TPL_P3DBM:
        {
            _tpl = 8;
            break;
        }
        default:
        {
            return ATK_MW579_EINVAL;
        }
    }
    
    sprintf(cmd, "AT+TPL=%d", _tpl);
    ret = atk_mw579_send_at_cmd(cmd, "OK", 100);
    if (ret != ATK_MW579_EOK)
    {
        return ATK_MW579_ERROR;
    }
    
    return ATK_MW579_EOK;
}

/**
 * @brief       设置ATK-MW579串口参数
 * @param       baudrate: 波特率
 *              data    : 数据位
 *              pari    : 校验位
 *              stop    : 停止位
 * @retval      ATK_MW579_EOK   : 设置ATK-MW579串口参数成功
 *              ATK_MW579_ERROR : 设置ATK-MW579串口参数失败
 *              ATK_MW579_EINVAL: 函数参数错误
 */
uint8_t atk_mw579_set_uart(atk_mw579_uart_baudrate_t baudrate, atk_mw579_uart_data_t data, atk_mw579_uart_pari_t pari, atk_mw579_uart_stop_t stop)
{
    uint8_t ret;
    uint32_t _baudrate;
    uint8_t _data;
    uint8_t _pari;
    uint8_t _stop;
    char cmd[22];
    
    switch (baudrate)
    {
        case ATK_MW579_UART_BAUDRATE_1200:
        {
            _baudrate = 1200;
            break;
        }
        case ATK_MW579_UART_BAUDRATE_2400:
        {
            _baudrate = 2400;
            break;
        }
        case ATK_MW579_UART_BAUDRATE_4800:
        {
            _baudrate = 4800;
            break;
        }
        case ATK_MW579_UART_BAUDRATE_9600:
        {
            _baudrate = 9600;
            break;
        }
        case ATK_MW579_UART_BAUDRATE_14400:
        {
            _baudrate = 14400;
            break;
        }
        case ATK_MW579_UART_BAUDRATE_19200:
        {
            _baudrate = 19200;
            break;
        }
        case ATK_MW579_UART_BAUDRATE_38400:
        {
            _baudrate = 38400;
            break;
        }
        case ATK_MW579_UART_BAUDRATE_43000:
        {
            _baudrate = 43000;
            break;
        }
        case ATK_MW579_UART_BAUDRATE_57600:
        {
            _baudrate = 57600;
            break;
        }
        case ATK_MW579_UART_BAUDRATE_76800:
        {
            _baudrate = 76800;
            break;
        }
        case ATK_MW579_UART_BAUDRATE_115200:
        {
            _baudrate = 115200;
            break;
        }
        case ATK_MW579_UART_BAUDRATE_128000:
        {
            _baudrate = 1200;
            break;
        }
        case ATK_MW579_UART_BAUDRATE_230400:
        {
            _baudrate = 230400;
            break;
        }
        default:
        {
            return ATK_MW579_EINVAL;
        }
    }
    
    switch (data)
    {
        case ATK_MW579_UART_DATA_5:
        {
            _data = 5;
            break;
        }
        case ATK_MW579_UART_DATA_6:
        {
            _data = 6;
            break;
        }
        case ATK_MW579_UART_DATA_7:
        {
            _data = 7;
            break;
        }
        case ATK_MW579_UART_DATA_8:
        {
            _data = 8;
            break;
        }
        default:
        {
            return ATK_MW579_EINVAL;
        }
    }
    
    switch (pari)
    {
        case ATK_MW579_UART_PARI_NONE:
        {
            _pari = 0;
            break;
        }
        case ATK_MW579_UART_PARI_ODD:
        {
            _pari = 1;
            break;
        }
        case ATK_MW579_UART_PARI_EVEN:
        {
            _pari = 2;
            break;
        }
        default:
        {
            return ATK_MW579_EINVAL;
        }
    }
    
    switch (stop)
    {
        case ATK_MW579_UART_STOP_1:
        {
            _stop = 1;
            break;
        }
        case ATK_MW579_UART_STOP_2:
        {
            _stop = 2;
            break;
        }
        default:
        {
            return ATK_MW579_EINVAL;
        }
    }
    
    sprintf(cmd, "AT+UART=%d,%d,%d,%d", _baudrate, _data, _pari, _stop);
    ret = atk_mw579_send_at_cmd(cmd, "OK", 100);
    if (ret != ATK_MW579_EOK)
    {
        return ATK_MW579_ERROR;
    }
    
    return ATK_MW579_EOK;
}

/**
 * @brief       设置ATK-MW579广播速度
 * @param       adptim: 广播时间，单位：10ms，范围：2~1024
 * @retval      ATK_MW579_EOK   : 设置ATK-MW579广播速度成功
 *              ATK_MW579_ERROR : 设置ATK-MW579广播速度失败
 *              ATK_MW579_EINVAL: 函数参数错误
 */
uint8_t atk_mw579_set_adptim(uint16_t adptim)
{
    uint8_t ret;
    char cmd[15];
    
    if ((adptim < 2) || (adptim > 1024))
    {
        return ATK_MW579_EINVAL;
    }
    
    sprintf(cmd, "AT+ADPTIM=%d", adptim);
    ret = atk_mw579_send_at_cmd(cmd, "OK", 100);
    if (ret != ATK_MW579_EOK)
    {
        return ATK_MW579_ERROR;
    }
    
    return ATK_MW579_EOK;
}

/**
 * @brief       设置ATK-MW579链路匹配
 * @param       linkpassen: ATK_MW579_LINKPASSEN_ON : 使能链路匹配
 *                          ATK_MW579_LINKPASSEN_OFF: 关闭链路匹配
 * @retval      ATK_MW579_EOK   : 设置ATK-MW579链路匹配成功
 *              ATK_MW579_ERROR : 设置ATK-MW579链路匹配失败
 *              ATK_MW579_EINVAL: 函数参数错误
 */
uint8_t atk_mw579_set_linkpassen(atk_mw579_linkpassen_t linkpassen)
{
    uint8_t ret;
    char _linkpassen[4];
    char cmd[18];
    
    switch (linkpassen)
    {
        case ATK_MW579_LINKPASSEN_ON:
        {
            sprintf(_linkpassen, "ON");
            break;
        }
        case ATK_MW579_LINKPASSEN_OFF:
        {
            sprintf(_linkpassen, "OFF");
            break;
        }
        default:
        {
            return ATK_MW579_EINVAL;
        }
    }
    
    sprintf(cmd, "AT+LINKPASSEN=%s", _linkpassen);
    ret = atk_mw579_send_at_cmd(cmd, "OK", 100);
    if (ret != ATK_MW579_EOK)
    {
        return ATK_MW579_ERROR;
    }
    
    return ATK_MW579_EOK;
}

/**
 * @brief       设置ATK-MW579板载LED
 * @param       leden: ATK_MW579_LEDEN_ON : 使能板载LED
 *                     ATK_MW579_LEDEN_OFF: 关闭板载LED
 * @retval      ATK_MW579_EOK   : 设置ATK-MW579板载LED成功
 *              ATK_MW579_ERROR : 设置ATK-MW579板载LED失败
 *              ATK_MW579_EINVAL: 函数参数错误
 */
uint8_t atk_mw579_set_leden(atk_mw579_leden_t leden)
{
    uint8_t ret;
    char _leden[4];
    char cmd[13];
    
    switch (leden)
    {
        case ATK_MW579_LEDEN_ON:
        {
            sprintf(_leden, "ON");
            break;
        }
        case ATK_MW579_LEDEN_OFF:
        {
            sprintf(_leden, "OFF");
            break;
        }
        default:
        {
            return ATK_MW579_EINVAL;
        }
    }
    
    sprintf(cmd, "AT+LEDEN=%s", _leden);
    ret = atk_mw579_send_at_cmd(cmd, "OK", 100);
    if (ret != ATK_MW579_EOK)
    {
        return ATK_MW579_ERROR;
    }
    
    return ATK_MW579_EOK;
}

/**
 * @brief       设置ATK-MW579从设备断连睡眠
 * @param       leden: ATK_MW579_SLAVESLEEPEN_ON : 使能从设备断连睡眠
 *                     ATK_MW579_SLAVESLEEPEN_OFF: 关闭从设备断连睡眠
 * @retval      ATK_MW579_EOK   : 设置ATK-MW579从设备断连睡眠成功
 *              ATK_MW579_ERROR : 设置ATK-MW579从设备断连睡眠失败
 *              ATK_MW579_EINVAL: 函数参数错误
 */
uint8_t atk_mw579_set_slavesleepen(atk_mw579_slavesleepen_t slavesleepen)
{
    uint8_t ret;
    char _slavesleepen[4];
    char cmd[20];
    
    switch (slavesleepen)
    {
        case ATK_MW579_SLAVESLEEPEN_ON:
        {
            sprintf(_slavesleepen, "ON");
            break;
        }
        case ATK_MW579_SLAVESLEEPEN_OFF:
        {
            sprintf(_slavesleepen, "OFF");
            break;
        }
        default:
        {
            return ATK_MW579_EINVAL;
        }
    }
    
    sprintf(cmd, "AT+SLAVESLEEPEN=%s", _slavesleepen);
    ret = atk_mw579_send_at_cmd(cmd, "OK", 100);
    if (ret != ATK_MW579_EOK)
    {
        return ATK_MW579_ERROR;
    }
    
    return ATK_MW579_EOK;
}

/**
 * @brief       设置ATK-MW579通信最大输出
 * @param       leden: ATK_MW579_MAXPUT_ON : 使能通信最大输出
 *                     ATK_MW579_MAXPUT_OFF: 关闭通信最大输出
 * @retval      ATK_MW579_EOK   : 设置ATK-MW579通信最大输出成功
 *              ATK_MW579_ERROR : 设置ATK-MW579通信最大输出失败
 *              ATK_MW579_EINVAL: 函数参数错误
 */
uint8_t atk_mw579_set_maxput(atk_mw579_maxput_t maxput)
{
    uint8_t ret;
    char _maxput[4];
    char cmd[14];
    
    switch (maxput)
    {
        case ATK_MW579_MAXPUT_ON:
        {
            sprintf(_maxput, "ON");
            break;
        }
        case ATK_MW579_MAXPUT_OFF:
        {
            sprintf(_maxput, "OFF");
            break;
        }
        default:
        {
            return ATK_MW579_EINVAL;
        }
    }
    
    sprintf(cmd, "AT+MAXPUT=%s", _maxput);
    ret = atk_mw579_send_at_cmd(cmd, "OK", 100);
    if (ret != ATK_MW579_EOK)
    {
        return ATK_MW579_ERROR;
    }
    
    return ATK_MW579_EOK;
}

/**
 * @brief       设置ATK-MW579工作模式
 * @param       leden: ATK_MW579_MODE_M: 主设备模式
 *                     ATK_MW579_MODE_S: 从设备模式
 *                     ATK_MW579_MODE_O: 观察者模式
 *                     ATK_MW579_MODE_B: 广播者模式
 *                     ATK_MW579_MODE_I: iBeacon模式
 * @retval      ATK_MW579_EOK   : 设置ATK-MW579工作模式成功
 *              ATK_MW579_ERROR : 设置ATK-MW579工作模式失败
 *              ATK_MW579_EINVAL: 函数参数错误
 */
uint8_t atk_mw579_set_mode(atk_mw579_mode_t mode)
{
    uint8_t ret;
    char _mode[2];
    char cmd[10];
    
    switch (mode)
    {
        case ATK_MW579_MODE_M:
        {
            sprintf(_mode, "M");
            break;
        }
        case ATK_MW579_MODE_S:
        {
            sprintf(_mode, "S");
            break;
        }
        case ATK_MW579_MODE_O:
        {
            sprintf(_mode, "O");
            break;
        }
        case ATK_MW579_MODE_B:
        {
            sprintf(_mode, "B");
            break;
        }
        case ATK_MW579_MODE_I:
        {
            sprintf(_mode, "I");
            break;
        }
        default:
        {
            return ATK_MW579_EINVAL;
        }
    }
    
    sprintf(cmd, "AT+MODE=%s", _mode);
    ret = atk_mw579_send_at_cmd(cmd, "OK", 100);
    if (ret != ATK_MW579_EOK)
    {
        return ATK_MW579_ERROR;
    }
    
    delay_ms(100);
    
    return ATK_MW579_EOK;
}

/**
 * @brief       ATK-MW579扫描周围从设备
 * @param       无
 * @retval      ATK_MW579_EOK   : ATK-MW579扫描周围从设备成功
 *              ATK_MW579_ERROR : ATK-MW579扫描周围从设备失败
 */
uint8_t atk_mw579_scan_slave(void)
{
    uint8_t ret;
    
    ret = atk_mw579_send_at_cmd("AT+SCAN", "OK", 5000);
    if (ret != ATK_MW579_EOK)
    {
        return ATK_MW579_ERROR;
    }
    
    return ATK_MW579_EOK;
}

/**
 * @brief       ATK-MW579连接周围从设备
 * @param       id: 扫描出从设备的序号
 * @retval      ATK_MW579_EOK   : ATK-MW579连接周围从设备成功
 *              ATK_MW579_ERROR : ATK-MW579连接周围从设备失败
 */
uint8_t atk_mw579_conn_slave(uint8_t id)
{
    uint8_t ret;
    char cmd[12];
    
    sprintf(cmd, "AT+CONN=%d", id);
    ret = atk_mw579_send_at_cmd(cmd, "OK", 1000);
    if (ret != ATK_MW579_EOK)
    {
        return ATK_MW579_ERROR;
    }
    
    return ATK_MW579_EOK;
}

/**
 * @brief       ATK-MW579进入透传
 * @param       无
 * @retval      ATK_MW579_EOK   : ATK-MW579进入透传成功
 *              ATK_MW579_ERROR : ATK-MW579进入透传失败
 */
uint8_t atk_mw579_enter_unvarnished(void)
{
    uint8_t ret;
    char cmd[8];
    
    sprintf(cmd, "AT+ENTM");
    ret = atk_mw579_send_at_cmd(cmd, "OK", 1000);
    if (ret != ATK_MW579_EOK)
    {
        return ATK_MW579_ERROR;
    }
    
    return ATK_MW579_EOK;
}

/**
 * @brief       设置ATK-MW579链路匹配密码
 * @param       pass: 链路匹配密码，支持数字、英文、符号，长度必须为6位
 * @retval      ATK_MW579_EOK   : 设置ATK-MW579链路匹配密码成功
 *              ATK_MW579_ERROR : 设置ATK-MW579链路匹配密码失败
 *              ATK_MW579_EINVAL: 函数参数错误
 */
uint8_t atk_mw579_set_linkpass(char *pass)
{
    uint8_t ret;
    char cmd[19];
    
    if (strlen(pass) != 6)
    {
        return ATK_MW579_EINVAL;
    }
    
    sprintf(cmd, "AT+LINKPASS=%s", pass);
    ret = atk_mw579_send_at_cmd(cmd, "OK", 1000);
    if (ret != ATK_MW579_EOK)
    {
        return ATK_MW579_ERROR;
    }
    
    return ATK_MW579_EOK;
}

/**
 * @brief       设置ATK-MW579自动睡眠
 * @param       autosleepen: ATK_MW579_AUTOSLEEPEN_ON : 使能自动睡眠
 *                           ATK_MW579_AUTOSLEEPEN_OFF: 关闭自动睡眠
 *              autotim    : 自动睡眠时间，单位：5s，范围：1~100
 * @retval      ATK_MW579_EOK   : 设置ATK-MW579自动睡眠成功
 *              ATK_MW579_ERROR : 设置ATK-MW579自动睡眠失败
 *              ATK_MW579_EINVAL: 函数参数错误
 */
uint8_t atk_mw579_set_autosleepen(atk_mw579_autosleepen_t autosleepen, uint8_t autotim)
{
    uint8_t ret;
    char _autosleepen[4];
    char cmd[23];
    
    if ((autotim < 1) || (autotim > 100))
    {
        return ATK_MW579_EINVAL;
    }
    
    switch (autosleepen)
    {
        case ATK_MW579_AUTOSLEEPEN_ON:
        {
            sprintf(_autosleepen, "ON");
            break;
        }
        case ATK_MW579_AUTOSLEEPEN_OFF:
        {
            sprintf(_autosleepen, "OFF");
            break;
        }
        default:
        {
            return ATK_MW579_EINVAL;
        }
    }
    
    sprintf(cmd, "AT+AUTOSLEEPEN=%s,%d", _autosleepen, autotim);
    ret = atk_mw579_send_at_cmd(cmd, "OK", 1000);
    if (ret != ATK_MW579_EOK)
    {
        return ATK_MW579_ERROR;
    }
    
    return ATK_MW579_EOK;
}

/**
 * @brief       设置ATK-MW579自动睡眠模式
 * @param       autosleep: ATK_MW579_AUTOSLEEP_LOW : 浅睡眠
 *                         ATK_MW579_AUTOSLEEP_DEEP: 深度睡眠
 * @retval      ATK_MW579_EOK   : 设置ATK-MW579自动睡眠模式成功
 *              ATK_MW579_ERROR : 设置ATK-MW579自动睡眠模式失败
 *              ATK_MW579_EINVAL: 函数参数错误
 */
uint8_t atk_mw579_set_autosleep(atk_mw579_autosleep_t autosleep)
{
    uint8_t ret;
    char _autosleep[5];
    char cmd[18];
    
    switch (autosleep)
    {
        case ATK_MW579_AUTOSLEEP_LOW:
        {
            sprintf(_autosleep, "LOW");
            break;
        }
        case ATK_MW579_AUTOSLEEP_DEEP:
        {
            sprintf(_autosleep, "DEEP");
            break;
        }
        default:
        {
            return ATK_MW579_EINVAL;
        }
    }
    
    sprintf(cmd, "AT+AUTOSLEEP=%s", _autosleep);
    ret = atk_mw579_send_at_cmd(cmd, "OK", 1000);
    if (ret != ATK_MW579_EOK)
    {
        return ATK_MW579_ERROR;
    }
    
    return ATK_MW579_EOK;
}

/**
 * @brief       设置ATK-MW579上电睡眠
 * @param       powersleepen: ATK_MW579_POWERSLEEPEN_ON : 使能上电睡眠
 *                            ATK_MW579_POWERSLEEPEN_OFF: 关闭上电睡眠
 * @retval      ATK_MW579_EOK   : 设置ATK-MW579上电睡眠成功
 *              ATK_MW579_ERROR : 设置ATK-MW579上电睡眠失败
 *              ATK_MW579_EINVAL: 函数参数错误
 */
uint8_t atk_mw579_set_powersleepen(atk_mw579_powersleepen_t powersleepen)
{
    uint8_t ret;
    char _powersleepen[4];
    char cmd[20];
    
    switch (powersleepen)
    {
        case ATK_MW579_POWERSLEEPEN_ON:
        {
            sprintf(_powersleepen, "ON");
            break;
        }
        case ATK_MW579_POWERSLEEPEN_OFF:
        {
            sprintf(_powersleepen, "OFF");
            break;
        }
        default:
        {
            return ATK_MW579_EINVAL;
        }
    }
    
    sprintf(cmd, "AT+POWERSLEEPEN=%s", _powersleepen);
    ret = atk_mw579_send_at_cmd(cmd, "OK", 1000);
    if (ret != ATK_MW579_EOK)
    {
        return ATK_MW579_ERROR;
    }
    
    return ATK_MW579_EOK;
}

/**
 * @brief       设置ATK-MW579 iBeacon
 * @param       uuid : 标识符
 *              major: 主标识
 *              minor: 次标识
 *              rssi : 距离1米时的信号强度
 * @retval      ATK_MW579_EOK   : 设置ATK-MW579 iBeacon成功
 *              ATK_MW579_ERROR : 设置ATK-MW579 iBeacon失败
 */
uint8_t atk_mw579_set_ibeacon(char *uuid, uint16_t major, uint16_t minor, uint8_t rssi)
{
    uint8_t ret;
    char cmd[60];
    
    sprintf(cmd, "AT+IBEACON=%s,%d,%d,%d", uuid, major, minor, rssi);
    ret = atk_mw579_send_at_cmd(cmd, "OK", 1000);
    if (ret != ATK_MW579_EOK)
    {
        return ATK_MW579_ERROR;
    }
    
    return ATK_MW579_EOK;
}

/**
 * @brief       通过WKUP引脚唤醒ATK-MW579
 * @param       无
 * @retval      无
 */
void atk_mw579_wakeup_by_pin(void)
{
    ATK_MW579_WKUP(0);
    delay_ms(30);
    ATK_MW579_WKUP(1);
    delay_ms(30);
}

/**
 * @brief       通过UART唤醒ATK-MW579
 * @param       无
 * @retval      无
 */
void atk_mw579_wakeup_by_uart(void)
{
    uint8_t byte_cnt;
    uint8_t byte_index;
    
    switch (g_atk_mw579_sta.baudrate)
    {
        case ATK_MW579_UART_BAUDRATE_1200:
        case ATK_MW579_UART_BAUDRATE_2400:
        case ATK_MW579_UART_BAUDRATE_4800:
        case ATK_MW579_UART_BAUDRATE_9600:
        case ATK_MW579_UART_BAUDRATE_14400:
        case ATK_MW579_UART_BAUDRATE_19200:
        {
            byte_cnt = 1;
            break;
        }
        case ATK_MW579_UART_BAUDRATE_38400:
        case ATK_MW579_UART_BAUDRATE_43000:
        {
            byte_cnt = 2;
            break;
        }
        case ATK_MW579_UART_BAUDRATE_57600:
        case ATK_MW579_UART_BAUDRATE_76800:
        {
            byte_cnt = 3;
            break;
        }
        case ATK_MW579_UART_BAUDRATE_115200:
        case ATK_MW579_UART_BAUDRATE_128000:
        {
            byte_cnt = 5;
            break;
        }
        case ATK_MW579_UART_BAUDRATE_230400:
        {
            byte_cnt = 8;
            break;
        }
        default:
        {
            break;
        }
    }
    
    for (byte_index=0; byte_index<byte_cnt; byte_index++)
    {
        atk_mw579_uart_printf("0");
    }
}
