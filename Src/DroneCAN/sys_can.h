/*
 * 中文导读：平台无关CAN接口及统计结构。上层通过统一收发接口使用不同MCU驱动；RTC备份槽用于与引导程序交换复位/升级状态。
 */

/*
  sys_can.h - MCU specific CAN API
 */

#pragma once

#include <canard.h>

/*
  CAN statistics shared by low level and high level code
 */
struct CANStats {
    uint32_t num_commands;
    uint32_t num_input;
    uint32_t total_commands;
    uint32_t num_receive;
    uint32_t num_tx_interrupts;
    uint32_t num_rx_interrupts;
    uint32_t rx_errors;
    uint32_t esr;
    uint32_t rxframe_error;
    int32_t rx_ecode;
    uint32_t should_accept;
    uint32_t on_receive;
    uint64_t last_raw_command_us;
};

extern struct CANStats canstats;


/*
  disable/enable CAN interripts
 */
/** 中文接口：禁用本平台CAN相关中断；不等同于关闭电机输出。 */
void sys_can_disable_IRQ(void);
/** 中文接口：使能本平台CAN相关中断；与禁用入口配合保护协议栈共享状态。 */
void sys_can_enable_IRQ(void);

/*
  get a 16 byte unique ID for this node
*/
/** 中文接口：从平台设备标识构造16字节节点唯一ID，供节点信息与动态地址分配使用。 */
void sys_can_getUniqueID(uint8_t id[16]);

/*
  initialise CAN hardware
 */
/** 中文接口：初始化本平台CAN时钟、引脚、收发资源和中断；SITL实现以主机网络模拟CAN。 */
void sys_can_init(void);

/*
  called from CAN IRQ indicating we may have a free TX slot
 */
/** 中文接口：尝试发送协议栈队首帧；硬件无空位时保留队列等待，成功或错误时弹出本帧。 */
extern void DroneCAN_processTxQueue();

/*
  called from CAN IRQ indicating we have a new frame waiting
 */
/** 中文接口：在中断上下文取尽底层接收帧，交给libcanard组包并记录接收错误。 */
extern void DroneCAN_receiveFrame();

/*
  alternative for interrupt driven receive, called from CAN interrupt
  handler
 */
/** 中文接口：将一帧CAN数据交给libcanard并记录错误；适合底层驱动在中断里直接传入已取出的帧。 */
extern void DroneCAN_handleFrame(const CanardCANFrame *rx_frame);

/*
  try to transmit a frame.
  return 1 for success, 0 for no space, -ve for error
 */
/** 中文接口：尝试提交一帧到底层发送资源；返回正值表示接受，0表示暂时无空间，负值表示错误。 */
int16_t sys_can_transmit(const CanardCANFrame* txf);

/*
  check for an incoming frame
  return 1 for success, 0 for no frame, -ve for error
 */
/** 中文接口：读取一帧到底层提供的输出结构；返回正值表示有效帧，0表示当前无帧，负值表示错误。 */
int16_t sys_can_receive(CanardCANFrame *rx_frame);

/*
  get/set RTC backup registers. Used to detect firmware update state
 */
/** 中文接口：读取指定RTC备份槽；硬件用于保留复位前状态，SITL用文件模拟。 */
uint32_t get_rtc_backup_register(uint8_t idx);
/** 中文接口：写指定RTC备份槽，用于应用程序与引导程序交换启动/升级状态；SITL写模拟文件。 */
void set_rtc_backup_register(uint8_t idx, uint32_t value);

/*
  magic values for RTC backup registers
 */
#define RTC_BKUP0_FWUPDATE 0x42c7 // top byte is CAN node number, 2nd byte is file server node
#define RTC_BKUP0_BOOTED 0x8c42c8 // set when main started
#define RTC_BKUP0_SIGNAL 0x8c42c9 // set on 5 DroneCAN messages processed

// setup a static port/pin
/** 中文接口：将编码后的端口/引脚设为指定逻辑状态，常用于控制CAN终端电阻；平台实现可能为空。 */
void setup_portpin(uint16_t portpin, bool enable);
