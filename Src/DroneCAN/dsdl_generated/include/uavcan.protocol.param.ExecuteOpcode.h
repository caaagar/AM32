/*
 * 中文导读：DSDL生成协议代码：参数保存/擦除等操作服务。
 * 编解码位宽、字段顺序、类型签名与ID共同决定兼容性。TAO表示尾数组优化；内部decode返回true表示失败。
 * 本文件的中文注释用于阅读，运行regenerate.sh重新生成时可能被覆盖；生成了类型不代表业务层已使用该功能。
 */

#pragma once
#include <uavcan.protocol.param.ExecuteOpcode_req.h>
#include <uavcan.protocol.param.ExecuteOpcode_res.h>

#define UAVCAN_PROTOCOL_PARAM_EXECUTEOPCODE_ID 10
#define UAVCAN_PROTOCOL_PARAM_EXECUTEOPCODE_SIGNATURE (0x3B131AC5EB69D2CDULL)

#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
#include <canard/cxx_wrappers.h>
SERVICE_MESSAGE_CXX_IFACE(uavcan_protocol_param_ExecuteOpcode, UAVCAN_PROTOCOL_PARAM_EXECUTEOPCODE_ID, UAVCAN_PROTOCOL_PARAM_EXECUTEOPCODE_SIGNATURE, UAVCAN_PROTOCOL_PARAM_EXECUTEOPCODE_REQUEST_MAX_SIZE, UAVCAN_PROTOCOL_PARAM_EXECUTEOPCODE_RESPONSE_MAX_SIZE);
#endif
