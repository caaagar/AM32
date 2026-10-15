/*
 * 中文导读：DSDL生成协议代码：按字节偏移写入远程文件数据。
 * 编解码位宽、字段顺序、类型签名与ID共同决定兼容性。TAO表示尾数组优化；内部decode返回true表示失败。
 * 本文件的中文注释用于阅读，运行regenerate.sh重新生成时可能被覆盖；生成了类型不代表业务层已使用该功能。
 */

#pragma once
#include <uavcan.protocol.file.Write_req.h>
#include <uavcan.protocol.file.Write_res.h>

#define UAVCAN_PROTOCOL_FILE_WRITE_ID 49
#define UAVCAN_PROTOCOL_FILE_WRITE_SIGNATURE (0x515AA1DC77E58429ULL)

#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
#include <canard/cxx_wrappers.h>
SERVICE_MESSAGE_CXX_IFACE(uavcan_protocol_file_Write, UAVCAN_PROTOCOL_FILE_WRITE_ID, UAVCAN_PROTOCOL_FILE_WRITE_SIGNATURE, UAVCAN_PROTOCOL_FILE_WRITE_REQUEST_MAX_SIZE, UAVCAN_PROTOCOL_FILE_WRITE_RESPONSE_MAX_SIZE);
#endif
