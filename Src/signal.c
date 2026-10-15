/*
 * 中文导读：输入协议自动识别与DMA完成处理。舵机PWM按高电平脉宽转换，DShot按边沿时序识别；零油门计数和端点校准也在这里维护。
 */

/*
 * IO.c
 *
 *  Created on: Sep. 26, 2020
 *      Author: Alka
 */

#include "signal.h"
#include "IO.h"
#include "common.h"
#include "dshot.h"
#include "functions.h"
#include "serial_telemetry.h"
#include "sounds.h"
#include "targets.h"
int max_servo_deviation = 250;
int servorawinput;
uint16_t smallestnumber = 20000;
uint8_t enter_calibration_count = 0;
uint8_t calibration_required = 0;
uint8_t high_calibration_counts = 0;
uint8_t high_calibration_set = 0;
uint16_t last_high_threshold = 0;
uint8_t low_calibration_counts = 0;
uint16_t last_input = 0;
char output_timer_prescaler;
uint8_t buffersize = 32;
uint32_t average_signal_pulse;
uint8_t average_count;
uint32_t average_packet_length;
uint16_t dshot_frametime_high = 50000;
uint16_t dshot_frametime_low = 0;

/** 中文说明：从DMA边沿间隔中寻找有效脉冲，并将计数243到1200映射为内部0到2000输入。 */
void computeMSInput()
{

    int lastnumber = dma_buffer[0];
    for (int j = 1; j < 2; j++) {

        if (((dma_buffer[j] - lastnumber) < 1500) && ((dma_buffer[j] - lastnumber) > 0)) { // blank space

            newinput = map((dma_buffer[j] - lastnumber), 243, 1200, 0, 2000);
            break;
        }
        lastnumber = dma_buffer[j];
    }
}

/** 中文说明：解码舵机PWM脉宽：处理高低端点校准、双向中点映射及每次输入变化限幅；有效脉宽须在800到2200之间。 */
void computeServoInput()
{
    if (((dma_buffer[1] - dma_buffer[0]) > 800) && ((dma_buffer[1] - dma_buffer[0]) < 2200)) {
				signaltimeout = 0;
/* 端点校准先稳定采集高油门，再采集低油门，给两端保留25微秒裕量并保存设置。 */
        if (calibration_required) {
            if (!high_calibration_set) {
                if (high_calibration_counts == 0) {
                    last_high_threshold = dma_buffer[1] - dma_buffer[0];
                }
                high_calibration_counts++;
                if (getAbsDif(last_high_threshold, servo_high_threshold) > 50) {
                    calibration_required = 0;
                } else {
                    servo_high_threshold = ((7 * servo_high_threshold + (dma_buffer[1] - dma_buffer[0])) >> 3);
                    if (high_calibration_counts > 50) {
                        servo_high_threshold = servo_high_threshold - 25;
                        eepromBuffer.servo.high_threshold = (servo_high_threshold - 1750) / 2;
                        high_calibration_set = 1;
                        playDefaultTone();
                    }
                }
                last_high_threshold = servo_high_threshold;
            }
            if (high_calibration_set) {
                if (dma_buffer[1] - dma_buffer[0] < 1250) {
                    low_calibration_counts++;
                    servo_low_threshold = ((7 * servo_low_threshold + (dma_buffer[1] - dma_buffer[0])) >> 3);
                }
                if (low_calibration_counts > 75) {
                    servo_low_threshold = servo_low_threshold + 25;
                    eepromBuffer.servo.low_threshold = (servo_low_threshold - 750) / 2;
                    calibration_required = 0;
                    saveEEpromSettings();
                    low_calibration_counts = 0;
                    playChangedTone();
                }
            }
            signaltimeout = 0;
        } else {
            if (eepromBuffer.bi_direction) {
                if (dma_buffer[1] - dma_buffer[0] <= servo_neutral) {
                    servorawinput = map((dma_buffer[1] - dma_buffer[0]),
                        servo_low_threshold, servo_neutral, 0, 1000);
                } else {
                    servorawinput = map((dma_buffer[1] - dma_buffer[0]), servo_neutral + 1,
                        servo_high_threshold, 1001, 2000);
                }
            } else {
                servorawinput = map((dma_buffer[1] - dma_buffer[0]), servo_low_threshold,
                    servo_high_threshold, 47, 2047);
                if (servorawinput <= 48) {
                    servorawinput = 0;
                }
            }
            signaltimeout = 0;
        }
    } else {
        zero_input_count = 0; // reset if out of range
    }

/* 限制每次PWM输入更新的变化幅度；此层限制输入值，主控制环仍可能另外限制输出占空比变化。 */
    if (servorawinput - newinput > max_servo_deviation) {
        newinput += max_servo_deviation;
    } else if (newinput - servorawinput > max_servo_deviation) {
        newinput -= max_servo_deviation;
    } else {
        newinput = servorawinput;
    }
}

/** 中文说明：输入DMA完成后的分发入口：处理协议检测、DShot收发切换、PWM解码及解锁前的零油门计数。 */
void transfercomplete()
{
#ifndef MCU_F031   // f031 does not use software EXTI event to process dshot
    if (armed && dshot_telemetry) {
        if (out_put) {
            receiveDshotDma();
            compute_dshot_flag = 2;
            return;
        } else {
            sendDshotDma();
            compute_dshot_flag = 1;
            return;
        }
    }
#endif
/* 未识别协议时先检测再重新启动DMA接收，不直接把未识别的脉冲用于驱动。 */
    if (inputSet == 0) {
        detectInput();
        receiveDshotDma();
        return;
    }
    if (inputSet == 1) {

        if (dshot_telemetry) {
            if (out_put) {
                make_dshot_package(e_com_time);
                computeDshotDMA();
                receiveDshotDma();
                return;
            } else {
                sendDshotDma();
                return;
            }
        } else {

            if (dshot == 1) {
                computeDshotDMA();
                receiveDshotDma();
            }
            if (servoPwm == 1) {
                if (getInputPinState()) {
                    buffersize = 3;
                } else {
                    buffersize = 2;
                    computeServoInput();
                }
                receiveDshotDma();
            }
        }
        if (!armed) {
            if (dshot && (average_count < 8) && (zero_input_count > 5)) {
                average_count++;
                average_packet_length = average_packet_length + (uint16_t)(dma_buffer[31] - dma_buffer[0]);
                if (average_count == 8) {
                    dshot_frametime_high = (average_packet_length >> 3) + (average_packet_length >> 7);
                    dshot_frametime_low = (average_packet_length >> 3) - (average_packet_length >> 7);
                }
            }
/* 解锁准备要求处理后的输入保持零，校准期间不累计正常零油门确认。 */
            if (adjusted_input == 0 && calibration_required == 0) { // note this in input..not newinput so it
                                                                    // will be adjusted be main loop
                zero_input_count++;
            } else {
              if(!eepromBuffer.disable_stick_calibration){
                zero_input_count = 0;
                if (adjusted_input > 1500) {
                    if (getAbsDif(adjusted_input, last_input) > 50) {
                        enter_calibration_count = 0;
                    } else {
                        enter_calibration_count++;
                    }

                    if (enter_calibration_count > 50 && (!high_calibration_set)) {
                        playBeaconTune3();
                        calibration_required = 1;
                        enter_calibration_count = 0;
                    }
                    last_input = adjusted_input;
                }
              }
            }
        }
    }
}

/** 中文说明：依据最短边沿间隔和平均脉冲长度选择DShot采集/回传定时器分频与缓冲区填充；阈值是计数值。 */
void checkDshot()
{
    if ((smallestnumber >= 1) && (smallestnumber < 4) && (average_signal_pulse < 60)) {
        ic_timer_prescaler = 0;
        if (CPU_FREQUENCY_MHZ > 100) {
            output_timer_prescaler = 1;
        } else {
            output_timer_prescaler = 0;
        }
        //	dshot_runout_timer = 1000;
        dshot = 1;
        buffer_padding = 14;
        buffersize = 32;
        inputSet = 1;
    }
    if ((smallestnumber >= 4) && (smallestnumber <= 8) && (average_signal_pulse < 100)) {
        dshot = 1;
        ic_timer_prescaler = 1;
        if (CPU_FREQUENCY_MHZ > 100) {
            output_timer_prescaler = 3;
        } else {
            output_timer_prescaler = 1;
        }
        buffer_padding = 7;
        buffersize = 32;
        inputSet = 1;
    }
}
/** 中文说明：当最短间隔符合PWM范围时启用舵机输入，并把采集定时器设置为微秒计数。 */
void checkServo()
{
    if (smallestnumber > 200 && smallestnumber < 20000) {
        servoPwm = 1;
        ic_timer_prescaler = CPU_FREQUENCY_MHZ - 1;
        buffersize = 2;
        inputSet = 1;
    }
}

/** 中文说明：统计DMA采样中的正边沿间隔，更新最短/平均间隔，再尝试识别DShot或舵机PWM协议。 */
void detectInput()
{
    smallestnumber = 20000;
    average_signal_pulse = 0;
    int lastnumber = dma_buffer[0];
    for (int j = 1; j < 31; j++) {
        if (dma_buffer[j] - lastnumber > 0) {
            if ((dma_buffer[j] - lastnumber) < smallestnumber) {
                smallestnumber = dma_buffer[j] - lastnumber;
            }
            average_signal_pulse += (dma_buffer[j] - lastnumber);
        }
        lastnumber = dma_buffer[j];
    }
    average_signal_pulse = average_signal_pulse / 32;

    if (dshot == 1) {
        checkDshot();
    }
    if (servoPwm == 1) {
        checkServo();
    }

    if (!dshot && !servoPwm) {
        checkDshot();
        checkServo();
    }
}
