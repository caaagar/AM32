/*
 * 中文导读：DSDL生成协议代码：按名称或索引读取参数，或设置参数并返回当前信息。
 * 编解码位宽、字段顺序、类型签名与ID共同决定兼容性。TAO表示尾数组优化；内部decode返回true表示失败。
 * 本文件的中文注释用于阅读，运行regenerate.sh重新生成时可能被覆盖；生成了类型不代表业务层已使用该功能。
 */

#pragma once
#include <uavcan.protocol.param.GetSet_req.h>
#include <uavcan.protocol.param.GetSet_res.h>

#define UAVCAN_PROTOCOL_PARAM_GETSET_ID 11
#define UAVCAN_PROTOCOL_PARAM_GETSET_SIGNATURE (0xA7B622F939D1A4D5ULL)

#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
#include <canard/cxx_wrappers.h>
SERVICE_MESSAGE_CXX_IFACE(uavcan_protocol_param_GetSet, UAVCAN_PROTOCOL_PARAM_GETSET_ID, UAVCAN_PROTOCOL_PARAM_GETSET_SIGNATURE, UAVCAN_PROTOCOL_PARAM_GETSET_REQUEST_MAX_SIZE, UAVCAN_PROTOCOL_PARAM_GETSET_RESPONSE_MAX_SIZE);
#endif
