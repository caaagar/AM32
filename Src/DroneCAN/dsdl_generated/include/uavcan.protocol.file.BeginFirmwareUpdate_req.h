/*
 * 中文导读：DSDL生成协议代码：请求节点进入固件升级流程。此文件对应服务请求。
 * 编解码位宽、字段顺序、类型签名与ID共同决定兼容性。TAO表示尾数组优化；内部decode返回true表示失败。
 * 本文件的中文注释用于阅读，运行regenerate.sh重新生成时可能被覆盖；生成了类型不代表业务层已使用该功能。
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <canard.h>
#include <uavcan.protocol.file.Path.h>


#define UAVCAN_PROTOCOL_FILE_BEGINFIRMWAREUPDATE_REQUEST_MAX_SIZE 202
#define UAVCAN_PROTOCOL_FILE_BEGINFIRMWAREUPDATE_REQUEST_SIGNATURE (0xB7D725DF72724126ULL)
#define UAVCAN_PROTOCOL_FILE_BEGINFIRMWAREUPDATE_REQUEST_ID 40

#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
class uavcan_protocol_file_BeginFirmwareUpdate_cxx_iface;
#endif

struct uavcan_protocol_file_BeginFirmwareUpdateRequest {
#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
    using cxx_iface = uavcan_protocol_file_BeginFirmwareUpdate_cxx_iface;
#endif
    uint8_t source_node_id; // 文件来源节点号
    struct uavcan_protocol_file_Path image_file_remote_path;
};

#ifdef __cplusplus
extern "C"
{
#endif

uint32_t uavcan_protocol_file_BeginFirmwareUpdateRequest_encode(struct uavcan_protocol_file_BeginFirmwareUpdateRequest* msg, uint8_t* buffer
#if CANARD_ENABLE_TAO_OPTION
    , bool tao
#endif
);
bool uavcan_protocol_file_BeginFirmwareUpdateRequest_decode(const CanardRxTransfer* transfer, struct uavcan_protocol_file_BeginFirmwareUpdateRequest* msg);

#if defined(CANARD_DSDLC_INTERNAL)
static inline void _uavcan_protocol_file_BeginFirmwareUpdateRequest_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_protocol_file_BeginFirmwareUpdateRequest* msg, bool tao);
static inline bool _uavcan_protocol_file_BeginFirmwareUpdateRequest_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_protocol_file_BeginFirmwareUpdateRequest* msg, bool tao);
/** 中文说明：将本类型结构序列化为协议位流；外层encode返回字节数，带前导下划线的内部入口推进bit_ofs，供嵌套类型复用。 */
void _uavcan_protocol_file_BeginFirmwareUpdateRequest_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_protocol_file_BeginFirmwareUpdateRequest* msg, bool tao) {
    (void)buffer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;

    canardEncodeScalar(buffer, *bit_ofs, 8, &msg->source_node_id);
    *bit_ofs += 8;
    _uavcan_protocol_file_Path_encode(buffer, bit_ofs, &msg->image_file_remote_path, tao);
}

/*
 decode uavcan_protocol_file_BeginFirmwareUpdateRequest, return true on failure, false on success
*/
/** 中文说明：按DSDL字段位宽反序列化；返回true表示失败、false表示成功；内部入口推进bit_ofs，外层还核对载荷长度。 */
bool _uavcan_protocol_file_BeginFirmwareUpdateRequest_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_protocol_file_BeginFirmwareUpdateRequest* msg, bool tao) {
    (void)transfer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;
    canardDecodeScalar(transfer, *bit_ofs, 8, false, &msg->source_node_id);
    *bit_ofs += 8;

    if (_uavcan_protocol_file_Path_decode(transfer, bit_ofs, &msg->image_file_remote_path, tao)) {return true;}

    return false; /* success */
}
#endif
#ifdef CANARD_DSDLC_TEST_BUILD
struct uavcan_protocol_file_BeginFirmwareUpdateRequest sample_uavcan_protocol_file_BeginFirmwareUpdateRequest_msg(void);
#endif
#ifdef __cplusplus
} // extern "C"

#ifdef DRONECAN_CXX_WRAPPERS
#include <canard/cxx_wrappers.h>
#endif
#endif
