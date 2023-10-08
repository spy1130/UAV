/**
 ****************************************************************************************************
 * @file        atk_mw579.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2022-06-21
 * @brief       ATK-MW579ģ����������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32F103������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "atk_mw579.h"
#include "delay.h"
#include <string.h>
#include <stdio.h>

/* ATK-MW579���ݽṹ�� */
static struct
{
    atk_mw579_uart_baudrate_t baudrate;
} g_atk_mw579_sta;

/**
 * @brief       ATK-MW579Ӳ����ʼ��
 * @param       ��
 * @retval      ��
 */
static void atk_mw579_hw_init(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    /* ʹ��ʱ�� */
    ATK_MW579_STA_GPIO_CLK_ENABLE();
    ATK_MW579_WKUP_GPIO_CLK_ENABLE();
    
    /* ��ʼ��STA���� */
    gpio_init_struct.Pin    = ATK_MW579_STA_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_INPUT;
    gpio_init_struct.Pull   = GPIO_PULLDOWN;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ATK_MW579_STA_GPIO_PORT, &gpio_init_struct);
    
    /* ��ʼ��WKUP���� */
    gpio_init_struct.Pin    = ATK_MW579_WKUP_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ATK_MW579_WKUP_GPIO_PORT, &gpio_init_struct);
    
    ATK_MW579_WKUP(1);
}

/**
 * @brief       ATK-MW579��ʼ��
 * @param       buadrate: ATK-MW579 UARTͨѶ������
 * @retval      ATK_MW579_EOK  : ATK-MW579��ʼ���ɹ�
 *              ATK_MW579_ERROR: ATK-MW579��ʼ��ʧ��
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
 * @brief       ��ȡATK-MW579����״̬
 * @param       ��
 * @retval      ATK_MW579_CONNECTED   : ������
 *              ATK_MW579_DISCONNECTED: δ����
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
 * @brief       ATK-MW579����ATָ��
 * @param       cmd    : �����͵�ATָ��
 *              ack    : �ȴ�����Ӧ
 *              timeout: �ȴ���ʱʱ��
 * @retval      ATK_MW579_EOK     : ����ִ�гɹ�
 *              ATK_MW579_ETIMEOUT: �ȴ�����Ӧ��ʱ������ִ��ʧ��
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
 * @brief       ATK-MW579��������ģʽ
 * @param       ��
 * @retval      ATK_MW579_EOK  : ATK-MW579��������ģʽ�ɹ�
 *              ATK_MW579_ERROR: ATK-MW579��������ģʽʧ��
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
 * @brief       ATK-MW579 ATָ�����
 * @param       ��
 * @retval      ATK_MW579_EOK  : ATָ����Գɹ�
 *              ATK_MW579_ERROR: ATָ�����ʧ��
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
 * @brief       ����ATK-MW579��������
 * @param       name: ��������
 * @retval      ATK_MW579_EOK  : ����ATK-MW579�������Ƴɹ�
 *              ATK_MW579_ERROR: ����ATK-MW579��������ʧ��
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
 * @brief       ����ATK-MW579������ӭ��
 * @param       hello: ������ӭ��
 * @retval      ATK_MW579_EOK  : ����ATK-MW579������ӭ��ɹ�
 *              ATK_MW579_ERROR: ����ATK-MW579������ӭ��ʧ��
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
 * @brief       ����ATK-MW579���书��
 * @param       tpl: ATK_MW579_TPL_N20DBM: -20dBm
 *                   ATK_MW579_TPL_N14DBM: -14dBm
 *                   ATK_MW579_TPL_N8DBM : -8dBm
 *                   ATK_MW579_TPL_N3DBM : -3dBm
 *                   ATK_MW579_TPL_P0DBM : +0dBm
 *                   ATK_MW579_TPL_P1DBM : +1dBm
 *                   ATK_MW579_TPL_P2DBM : +2dBm
 *                   ATK_MW579_TPL_P3DBM : +3dBm
 * @retval      ATK_MW579_EOK   : ����ATK-MW579���书�ʳɹ�
 *              ATK_MW579_ERROR : ����ATK-MW579���书��ʧ��
 *              ATK_MW579_EINVAL: ������������
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
 * @brief       ����ATK-MW579���ڲ���
 * @param       baudrate: ������
 *              data    : ����λ
 *              pari    : У��λ
 *              stop    : ֹͣλ
 * @retval      ATK_MW579_EOK   : ����ATK-MW579���ڲ����ɹ�
 *              ATK_MW579_ERROR : ����ATK-MW579���ڲ���ʧ��
 *              ATK_MW579_EINVAL: ������������
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
 * @brief       ����ATK-MW579�㲥�ٶ�
 * @param       adptim: �㲥ʱ�䣬��λ��10ms����Χ��2~1024
 * @retval      ATK_MW579_EOK   : ����ATK-MW579�㲥�ٶȳɹ�
 *              ATK_MW579_ERROR : ����ATK-MW579�㲥�ٶ�ʧ��
 *              ATK_MW579_EINVAL: ������������
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
 * @brief       ����ATK-MW579��·ƥ��
 * @param       linkpassen: ATK_MW579_LINKPASSEN_ON : ʹ����·ƥ��
 *                          ATK_MW579_LINKPASSEN_OFF: �ر���·ƥ��
 * @retval      ATK_MW579_EOK   : ����ATK-MW579��·ƥ��ɹ�
 *              ATK_MW579_ERROR : ����ATK-MW579��·ƥ��ʧ��
 *              ATK_MW579_EINVAL: ������������
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
 * @brief       ����ATK-MW579����LED
 * @param       leden: ATK_MW579_LEDEN_ON : ʹ�ܰ���LED
 *                     ATK_MW579_LEDEN_OFF: �رհ���LED
 * @retval      ATK_MW579_EOK   : ����ATK-MW579����LED�ɹ�
 *              ATK_MW579_ERROR : ����ATK-MW579����LEDʧ��
 *              ATK_MW579_EINVAL: ������������
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
 * @brief       ����ATK-MW579���豸����˯��
 * @param       leden: ATK_MW579_SLAVESLEEPEN_ON : ʹ�ܴ��豸����˯��
 *                     ATK_MW579_SLAVESLEEPEN_OFF: �رմ��豸����˯��
 * @retval      ATK_MW579_EOK   : ����ATK-MW579���豸����˯�߳ɹ�
 *              ATK_MW579_ERROR : ����ATK-MW579���豸����˯��ʧ��
 *              ATK_MW579_EINVAL: ������������
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
 * @brief       ����ATK-MW579ͨ��������
 * @param       leden: ATK_MW579_MAXPUT_ON : ʹ��ͨ��������
 *                     ATK_MW579_MAXPUT_OFF: �ر�ͨ��������
 * @retval      ATK_MW579_EOK   : ����ATK-MW579ͨ���������ɹ�
 *              ATK_MW579_ERROR : ����ATK-MW579ͨ��������ʧ��
 *              ATK_MW579_EINVAL: ������������
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
 * @brief       ����ATK-MW579����ģʽ
 * @param       leden: ATK_MW579_MODE_M: ���豸ģʽ
 *                     ATK_MW579_MODE_S: ���豸ģʽ
 *                     ATK_MW579_MODE_O: �۲���ģʽ
 *                     ATK_MW579_MODE_B: �㲥��ģʽ
 *                     ATK_MW579_MODE_I: iBeaconģʽ
 * @retval      ATK_MW579_EOK   : ����ATK-MW579����ģʽ�ɹ�
 *              ATK_MW579_ERROR : ����ATK-MW579����ģʽʧ��
 *              ATK_MW579_EINVAL: ������������
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
 * @brief       ATK-MW579ɨ����Χ���豸
 * @param       ��
 * @retval      ATK_MW579_EOK   : ATK-MW579ɨ����Χ���豸�ɹ�
 *              ATK_MW579_ERROR : ATK-MW579ɨ����Χ���豸ʧ��
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
 * @brief       ATK-MW579������Χ���豸
 * @param       id: ɨ������豸�����
 * @retval      ATK_MW579_EOK   : ATK-MW579������Χ���豸�ɹ�
 *              ATK_MW579_ERROR : ATK-MW579������Χ���豸ʧ��
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
 * @brief       ATK-MW579����͸��
 * @param       ��
 * @retval      ATK_MW579_EOK   : ATK-MW579����͸���ɹ�
 *              ATK_MW579_ERROR : ATK-MW579����͸��ʧ��
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
 * @brief       ����ATK-MW579��·ƥ������
 * @param       pass: ��·ƥ�����룬֧�����֡�Ӣ�ġ����ţ����ȱ���Ϊ6λ
 * @retval      ATK_MW579_EOK   : ����ATK-MW579��·ƥ������ɹ�
 *              ATK_MW579_ERROR : ����ATK-MW579��·ƥ������ʧ��
 *              ATK_MW579_EINVAL: ������������
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
 * @brief       ����ATK-MW579�Զ�˯��
 * @param       autosleepen: ATK_MW579_AUTOSLEEPEN_ON : ʹ���Զ�˯��
 *                           ATK_MW579_AUTOSLEEPEN_OFF: �ر��Զ�˯��
 *              autotim    : �Զ�˯��ʱ�䣬��λ��5s����Χ��1~100
 * @retval      ATK_MW579_EOK   : ����ATK-MW579�Զ�˯�߳ɹ�
 *              ATK_MW579_ERROR : ����ATK-MW579�Զ�˯��ʧ��
 *              ATK_MW579_EINVAL: ������������
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
 * @brief       ����ATK-MW579�Զ�˯��ģʽ
 * @param       autosleep: ATK_MW579_AUTOSLEEP_LOW : ǳ˯��
 *                         ATK_MW579_AUTOSLEEP_DEEP: ���˯��
 * @retval      ATK_MW579_EOK   : ����ATK-MW579�Զ�˯��ģʽ�ɹ�
 *              ATK_MW579_ERROR : ����ATK-MW579�Զ�˯��ģʽʧ��
 *              ATK_MW579_EINVAL: ������������
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
 * @brief       ����ATK-MW579�ϵ�˯��
 * @param       powersleepen: ATK_MW579_POWERSLEEPEN_ON : ʹ���ϵ�˯��
 *                            ATK_MW579_POWERSLEEPEN_OFF: �ر��ϵ�˯��
 * @retval      ATK_MW579_EOK   : ����ATK-MW579�ϵ�˯�߳ɹ�
 *              ATK_MW579_ERROR : ����ATK-MW579�ϵ�˯��ʧ��
 *              ATK_MW579_EINVAL: ������������
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
 * @brief       ����ATK-MW579 iBeacon
 * @param       uuid : ��ʶ��
 *              major: ����ʶ
 *              minor: �α�ʶ
 *              rssi : ����1��ʱ���ź�ǿ��
 * @retval      ATK_MW579_EOK   : ����ATK-MW579 iBeacon�ɹ�
 *              ATK_MW579_ERROR : ����ATK-MW579 iBeaconʧ��
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
 * @brief       ͨ��WKUP���Ż���ATK-MW579
 * @param       ��
 * @retval      ��
 */
void atk_mw579_wakeup_by_pin(void)
{
    ATK_MW579_WKUP(0);
    delay_ms(30);
    ATK_MW579_WKUP(1);
    delay_ms(30);
}

/**
 * @brief       ͨ��UART����ATK-MW579
 * @param       ��
 * @retval      ��
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
