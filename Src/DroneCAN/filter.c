/*
 * 中文导读：CAN油门二阶低通滤波。截止频率越低，输入变化越平滑但延迟越大；失联处理需直接重置历史状态。
 */

/*
  a 2 pole filter applied to RawCommand to provide a configurable
  acceleration filter

  Based on ArduPilot LowPassFilter2p.cpp
 */

#include <math.h>

struct Filter2P {
    float cutoff_freq;
    float sample_freq;
    float a1;
    float a2;
    float b0;
    float b1;
    float b2;

    float _delay_element_1;
    float _delay_element_2;
};

static struct Filter2P filter;

#define MIN(a,b) ((a)<(b)?(a):(b))

/** 中文说明：按采样率和截止频率计算二阶低通系数，并将截止频率限制到采样率的40%以下。 */
static void Filter2P_setup(float sample_freq, float cutoff_freq)
{
    // Keep well under Nyquist limit
    filter.cutoff_freq = MIN(cutoff_freq, sample_freq * 0.4);
    filter.sample_freq = sample_freq;

    const float fr = filter.sample_freq / filter.cutoff_freq;
    const float fr_scaled = M_PI/fr;
    const float ohm = tanf(fr_scaled);
    const float c = 1.0f+2.0f*cosf(M_PI/4.0f)*ohm + ohm*ohm;

    filter.b0 = ohm*ohm/c;
    filter.b1 = 2.0f*filter.b0;
    filter.b2 = filter.b0;
    filter.a1 = 2.0f*(ohm*ohm-1.0f)/c;
    filter.a2 = (1.0f-2.0f*cosf(M_PI/4.0f)*ohm+ohm*ohm)/c;
}

/*
  force the filter state to a value, so that the next
  apply(value, ...) returns it rather than easing towards it. Used by the RawCommand failsafe: a
  single zero sample pushed through a slow filter leaves almost all of
  the previous throttle applied
 */
/** 中文说明：直接重置滤波器历史状态到指定稳态值；失联时用于立即清除历史油门，避免缓慢衰减。 */
void Filter2P_reset(const float value)
{
    filter._delay_element_1 = filter._delay_element_2 =
        value * (1.0f / (1 + filter.a1 + filter.a2));
}

/** 中文说明：对CAN输入执行二阶低通；频率非正时直通，参数变化时重算系数并按当前样本初始化状态。 */
float Filter2P_apply(const float sample, float cutoff_freq, float sample_freq)
{
    if (cutoff_freq <= 0 || sample_freq <= 0) {
        // passthru
        return sample;
    }

    if (filter.cutoff_freq != cutoff_freq || filter.sample_freq != sample_freq) {
        Filter2P_setup(sample_freq, cutoff_freq);
        filter._delay_element_1 = filter._delay_element_2 = sample * (1.0 / (1 + filter.a1 + filter.a2));
    }

    const float delay_element_0 = sample - filter._delay_element_1 * filter.a1 - filter._delay_element_2 * filter.a2;
    const float output = delay_element_0 * filter.b0 + filter._delay_element_1 * filter.b1 + filter._delay_element_2 * filter.b2;

    filter._delay_element_2 = filter._delay_element_1;
    filter._delay_element_1 = delay_element_0;

    return output;
}

#ifndef MCU_SITL
/*
  unfortunately the maths libraries have an abort() linkage
 */
/** 中文说明：为数学库提供链接符号；当前实现声明不可到达，不是可用于普通错误处理的停机函数。 */
void abort(void)
{
    __builtin_unreachable();
}
#endif
