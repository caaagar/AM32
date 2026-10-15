/*
 * 中文导读：共享整数映射、差值、延时、CRC8和GPIO辅助函数。涉及定时器计数的量必须结合平台分频理解，避免把原始计数直接当作机械转速。
 */

/*
 * functions.c
 *
 *  Created on: Sep. 26, 2020
 *      Author: Alka
 */

#include "functions.h"
#include "targets.h"

// long map(long x, long in_min, long in_max, long out_min, long out_max)
//{
//     if (x < in_min) {
//         x = in_min;
//     }
//     if (x > in_max) {
//         x = in_max;
//     }
//     return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
// }

/** 中文说明：将整数输入分段递归映射到输出区间，端点外直接返回端点值；不是浮点线性插值，保留原有整数取整行为。 */
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
    if (x >= in_max)
        return out_max;
		if (x <= in_min)
        return out_min;
    if (in_min > in_max)
        return map(x, in_max, in_min, out_max, out_min);
    if (out_min == out_max)
        return out_min;
    const long in_mid = (in_min + in_max) >> 1;
    const long out_mid = (out_min + out_max) >> 1;
    if (in_min == in_mid)
        return out_mid;
    if (x <= in_mid)
        return map(x, in_min, in_mid, out_min, out_mid);
    else
        return map(x, in_mid + 1, in_max, out_mid, out_max);
}

/** 中文说明：计算两个整数之差的绝对值，供输入稳定性、校准及失步检测比较使用。 */
uint32_t getAbsDif(int number1, int number2)
{
    int result = number1 - number2;
    if (result < 0) {
        result = -result;
    }
    return (uint32_t)result;
}

/*
  get current value of UTILITY_TIMER timer as 16bit microseconds
 */
/** 中文说明：读取平台适配后的16位微秒计数；计数会回绕，调用者用无符号差计算经过时间。NXP分支不使用此实现。 */
static inline uint16_t get_timer_us16(void) {
#if defined(STMICRO)
    return UTILITY_TIMER->CNT;
#elif defined(GIGADEVICES)
    return TIMER_CNT(UTILITY_TIMER);
#elif defined(ARTERY)
    return UTILITY_TIMER->cval;
#elif defined(NXP)
    //Return nothing since NXP micro-tick works differently
    return 0;
#elif defined(WCH)
    return UTILITY_TIMER->CNT>>1;
#else
#error unsupported MCU
#endif
}

/*
  delay by microseconds, max 65535
 */
/** 中文说明：阻塞等待指定微秒数；非NXP路径将参数截成16位，因此单次应不超过65535微秒。 */
void delayMicros(uint32_t micros)
{
#ifdef NXP
    //Set delay value
	modifyReg32(&UTICK0->CTRL, UTICK_CTRL_DELAYVAL_MASK, UTICK_CTRL_DELAYVAL(micros));

	//Wait until micro-tick timer is finished
	while (!(UTICK0->STAT & UTICK_STAT_INTR_MASK)) {}

	//Clear UTICK interrupt flag
	UTICK0->STAT = UTICK_STAT_INTR(1);
#else
    const uint16_t cval_start = get_timer_us16();
    while ((uint16_t)(get_timer_us16() - cval_start) < (uint16_t)micros) {
    }
#endif
}


/*
  delay in millis, convenience wrapper around delayMicros
  Note: For a long delay, say 100ms, there is a possibility that it goes into a nested delay
  	  	  due to the tenKhzRoutine also calling the delay function.
 */
/** 中文说明：毫秒级阻塞延时；多数平台拆成多次1000微秒等待，中断仍可能影响实际耗时。 */
void delayMillis(uint32_t millis)
{
#ifdef NXP
	delayMicros(1000UL * millis);
#else
    while (millis-- > 0) {
        delayMicros(1000UL);
    }
#endif
}

/** 中文说明：用多项式0x07处理一个字节，逐位更新8位校验值；用于串口遥测的数据完整性检查。 */
uint8_t update_crc8(uint8_t crc, uint8_t crc_seed)
{
    uint8_t crc_u, i;
    crc_u = crc;
    crc_u ^= crc_seed;
    for (i = 0; i < 8; i++) {
        crc_u = (crc_u & 0x80) ? 0x7 ^ (crc_u << 1) : (crc_u << 1);
    }
    return (crc_u);
}

/** 中文说明：从零开始遍历BufLen个字节，返回CRC8校验值，不包含校验字段本身。 */
uint8_t get_crc8(uint8_t* Buf, uint8_t BufLen)
{
    uint8_t crc = 0, i;
    for (i = 0; i < BufLen; i++) {
        crc = update_crc8(Buf[i], crc);
    }
    return (crc);
}

#ifdef MCU_AT421
/** 中文说明：快速切换GPIO模式；具体寄存器操作依MCU条件编译分支而定，常用于信号线收发方向切换。 */
void gpio_mode_QUICK(gpio_type* gpio_periph, uint32_t mode,
    uint32_t pull_up_down, uint32_t pin)
{
    gpio_periph->cfgr = (((((gpio_periph->cfgr))) & (~(((pin * pin) * (0x3UL << (0U)))))) | (((pin * pin) * mode)));
}
/** 中文说明：同时更新引脚模式与上下拉配置；pin是引脚掩码，按平台寄存器布局写入。 */
void gpio_mode_set(gpio_type* gpio_periph, uint32_t mode, uint32_t pull_up_down,
    uint32_t pin)
{
    gpio_periph->cfgr = (((((gpio_periph->cfgr))) & (~(((pin * pin) * (0x3UL << (0U)))))) | (((pin * pin) * mode)));
    gpio_periph->pull = ((((((gpio_periph->pull))) & (~(((pin * pin) * (0x3UL << (0U)))))) | (((pin * pin) * pull_up_down))));
}
#endif

#ifdef MCU_AT415
/** 中文说明：快速切换GPIO模式；具体寄存器操作依MCU条件编译分支而定，常用于信号线收发方向切换。 */
void gpio_mode_QUICK(gpio_type* gpio_periph, uint32_t mode,
    uint32_t pull_up_down, uint32_t pin)
{
    __disable_irq();
    gpio_init_type gpio_init_struct;
    gpio_default_para_init(&gpio_init_struct);

    if (GPIO_MODE_MUX) {
    }

    gpio_init_struct.gpio_mode = mode;
    gpio_init_struct.gpio_pins = pin;
    gpio_init_struct.gpio_pull = pull_up_down;

    gpio_init(gpio_periph, &gpio_init_struct);

    __enable_irq();
}
#endif
