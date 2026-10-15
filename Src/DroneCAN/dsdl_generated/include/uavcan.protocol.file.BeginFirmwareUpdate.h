/*
 * 中文导读：DSDL生成协议代码：请求节点进入固件升级流程。
 * 编解码位宽、字段顺序、类型签名与ID共同决定兼容性。TAO表示尾数组优化；内部decode返回true表示失败。
 * 本文件的中文注释用于阅读，运行regenerate.sh重新生成时可能被覆盖；生成了类型不代表业务层已使用该功能。
 */

#pragma once
#include <uavcan.protocol.file.BeginFirmwareUpdate_req.h>
#include <uavcan.protocol.file.BeginFirmwareUpdate_res.h>

#define UAVCAN_PROTOCOL_FILE_BEGINFIRMWAREUPDATE_ID 40
#define UAVCAN_PROTOCOL_FILE_BEGINFIRMWAREUPDATE_SIGNATURE (0xB7D725DF72724126ULL)

#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
#include <canard/cxx_wrappers.h>
SERVICE_MESSAGE_CXX_IFACE(uavcan_protocol_file_BeginFirmwareUpdate, UAVCAN_PROTOCOL_FILE_BEGINFIRMWAREUPDATE_ID, UAVCAN_PROTOCOL_FILE_BEGINFIRMWAREUPDATE_SIGNATURE, UAVCAN_PROTOCOL_FILE_BEGINFIRMWAREUPDATE_REQUEST_MAX_SIZE, UAVCAN_PROTOCOL_FILE_BEGINFIRMWAREUPDATE_RESPONSE_MAX_SIZE);
#endif
