/*
 * 中文导读：二阶输入滤波的应用接口：apply处理一次采样，reset直接设置历史稳态，供CAN失联归零使用。
 */

/*
  a 2 pole filter applied to RawCommand to provide a configurable
  acceleration filter
 */
#pragma once

/** 中文接口：对CAN输入执行二阶低通；频率非正时直通，参数变化时重算系数并按当前样本初始化状态。 */
float Filter2P_apply(const float sample, float cutoff_freq, float sample_rate);
/** 中文接口：直接重置滤波器历史状态到指定稳态值；失联时用于立即清除历史油门，避免缓慢衰减。 */
void Filter2P_reset(const float value);
