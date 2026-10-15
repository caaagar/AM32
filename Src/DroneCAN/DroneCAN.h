/*
 * 中文导读：DroneCAN应用层对外接口；实现受DRONECAN_SUPPORT编译选项控制。声明存在不代表每个构建都会链接相应功能。
 */

#pragma once

#include <stdbool.h>

#if DRONECAN_SUPPORT
void DroneCAN_Init(void);
/** 中文接口：主循环CAN服务：节点分配、发送调度、延后保存和250ms RawCommand失联置零；失联同时清除滤波历史。 */
void DroneCAN_update();
/** 中文接口：只判断启动以来是否曾收到RawCommand；计数非零即为真，并不等价于当前控制链路仍在线。 */
bool DroneCAN_active();

#endif // DRONECAN_SUPPORT
