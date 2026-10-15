/*
 * 中文导读：DSDL生成协议代码：节点信息查询服务，包括软件/硬件版本和节点名称。
 * 编解码位宽、字段顺序、类型签名与ID共同决定兼容性。TAO表示尾数组优化；内部decode返回true表示失败。
 * 本文件的中文注释用于阅读，运行regenerate.sh重新生成时可能被覆盖；生成了类型不代表业务层已使用该功能。
 */

#pragma once
#include <uavcan.protocol.GetNodeInfo_req.h>
#include <uavcan.protocol.GetNodeInfo_res.h>

#define UAVCAN_PROTOCOL_GETNODEINFO_ID 1
#define UAVCAN_PROTOCOL_GETNODEINFO_SIGNATURE (0xEE468A8121C46A9EULL)

#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
#include <canard/cxx_wrappers.h>
SERVICE_MESSAGE_CXX_IFACE(uavcan_protocol_GetNodeInfo, UAVCAN_PROTOCOL_GETNODEINFO_ID, UAVCAN_PROTOCOL_GETNODEINFO_SIGNATURE, UAVCAN_PROTOCOL_GETNODEINFO_REQUEST_MAX_SIZE, UAVCAN_PROTOCOL_GETNODEINFO_RESPONSE_MAX_SIZE);
#endif
