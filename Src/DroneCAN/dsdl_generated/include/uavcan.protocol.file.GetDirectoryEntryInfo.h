/*
 * 中文导读：DSDL生成协议代码：按索引查询远程目录项。
 * 编解码位宽、字段顺序、类型签名与ID共同决定兼容性。TAO表示尾数组优化；内部decode返回true表示失败。
 * 本文件的中文注释用于阅读，运行regenerate.sh重新生成时可能被覆盖；生成了类型不代表业务层已使用该功能。
 */

#pragma once
#include <uavcan.protocol.file.GetDirectoryEntryInfo_req.h>
#include <uavcan.protocol.file.GetDirectoryEntryInfo_res.h>

#define UAVCAN_PROTOCOL_FILE_GETDIRECTORYENTRYINFO_ID 46
#define UAVCAN_PROTOCOL_FILE_GETDIRECTORYENTRYINFO_SIGNATURE (0x8C46E8AB568BDA79ULL)

#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
#include <canard/cxx_wrappers.h>
SERVICE_MESSAGE_CXX_IFACE(uavcan_protocol_file_GetDirectoryEntryInfo, UAVCAN_PROTOCOL_FILE_GETDIRECTORYENTRYINFO_ID, UAVCAN_PROTOCOL_FILE_GETDIRECTORYENTRYINFO_SIGNATURE, UAVCAN_PROTOCOL_FILE_GETDIRECTORYENTRYINFO_REQUEST_MAX_SIZE, UAVCAN_PROTOCOL_FILE_GETDIRECTORYENTRYINFO_RESPONSE_MAX_SIZE);
#endif
