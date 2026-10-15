/*
 * 中文导读：DSDL生成协议代码：节点心跳，包括运行时间、健康度和运行模式。
 * 编解码位宽、字段顺序、类型签名与ID共同决定兼容性。TAO表示尾数组优化；内部decode返回true表示失败。
 * 本文件的中文注释用于阅读，运行regenerate.sh重新生成时可能被覆盖；生成了类型不代表业务层已使用该功能。
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <canard.h>


#define UAVCAN_PROTOCOL_NODESTATUS_MAX_SIZE 7
#define UAVCAN_PROTOCOL_NODESTATUS_SIGNATURE (0xF0868D0C1A7C6F1ULL)
#define UAVCAN_PROTOCOL_NODESTATUS_ID 341

#define UAVCAN_PROTOCOL_NODESTATUS_MAX_BROADCASTING_PERIOD_MS 1000
#define UAVCAN_PROTOCOL_NODESTATUS_MIN_BROADCASTING_PERIOD_MS 2
#define UAVCAN_PROTOCOL_NODESTATUS_OFFLINE_TIMEOUT_MS 3000
#define UAVCAN_PROTOCOL_NODESTATUS_HEALTH_OK 0
#define UAVCAN_PROTOCOL_NODESTATUS_HEALTH_WARNING 1
#define UAVCAN_PROTOCOL_NODESTATUS_HEALTH_ERROR 2
#define UAVCAN_PROTOCOL_NODESTATUS_HEALTH_CRITICAL 3
#define UAVCAN_PROTOCOL_NODESTATUS_MODE_OPERATIONAL 0
#define UAVCAN_PROTOCOL_NODESTATUS_MODE_INITIALIZATION 1
#define UAVCAN_PROTOCOL_NODESTATUS_MODE_MAINTENANCE 2
#define UAVCAN_PROTOCOL_NODESTATUS_MODE_SOFTWARE_UPDATE 3
#define UAVCAN_PROTOCOL_NODESTATUS_MODE_OFFLINE 7

#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
class uavcan_protocol_NodeStatus_cxx_iface;
#endif

struct uavcan_protocol_NodeStatus {
#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
    using cxx_iface = uavcan_protocol_NodeStatus_cxx_iface;
#endif
    uint32_t uptime_sec; // 节点启动后经过的秒数
    uint8_t health; // 节点健康状态枚举
    uint8_t mode; // 节点运行模式
    uint8_t sub_mode; // 节点子模式
    uint16_t vendor_specific_status_code; // 厂商自定义状态码
};

#ifdef __cplusplus
extern "C"
{
#endif

uint32_t uavcan_protocol_NodeStatus_encode(struct uavcan_protocol_NodeStatus* msg, uint8_t* buffer
#if CANARD_ENABLE_TAO_OPTION
    , bool tao
#endif
);
bool uavcan_protocol_NodeStatus_decode(const CanardRxTransfer* transfer, struct uavcan_protocol_NodeStatus* msg);

#if defined(CANARD_DSDLC_INTERNAL)
static inline void _uavcan_protocol_NodeStatus_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_protocol_NodeStatus* msg, bool tao);
static inline bool _uavcan_protocol_NodeStatus_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_protocol_NodeStatus* msg, bool tao);
/** 中文说明：将本类型结构序列化为协议位流；外层encode返回字节数，带前导下划线的内部入口推进bit_ofs，供嵌套类型复用。 */
void _uavcan_protocol_NodeStatus_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_protocol_NodeStatus* msg, bool tao) {
    (void)buffer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;

    canardEncodeScalar(buffer, *bit_ofs, 32, &msg->uptime_sec);
    *bit_ofs += 32;
    canardEncodeScalar(buffer, *bit_ofs, 2, &msg->health);
    *bit_ofs += 2;
    canardEncodeScalar(buffer, *bit_ofs, 3, &msg->mode);
    *bit_ofs += 3;
    canardEncodeScalar(buffer, *bit_ofs, 3, &msg->sub_mode);
    *bit_ofs += 3;
    canardEncodeScalar(buffer, *bit_ofs, 16, &msg->vendor_specific_status_code);
    *bit_ofs += 16;
}

/*
 decode uavcan_protocol_NodeStatus, return true on failure, false on success
*/
/** 中文说明：按DSDL字段位宽反序列化；返回true表示失败、false表示成功；内部入口推进bit_ofs，外层还核对载荷长度。 */
bool _uavcan_protocol_NodeStatus_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_protocol_NodeStatus* msg, bool tao) {
    (void)transfer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;
    canardDecodeScalar(transfer, *bit_ofs, 32, false, &msg->uptime_sec);
    *bit_ofs += 32;

    canardDecodeScalar(transfer, *bit_ofs, 2, false, &msg->health);
    *bit_ofs += 2;

    canardDecodeScalar(transfer, *bit_ofs, 3, false, &msg->mode);
    *bit_ofs += 3;

    canardDecodeScalar(transfer, *bit_ofs, 3, false, &msg->sub_mode);
    *bit_ofs += 3;

    canardDecodeScalar(transfer, *bit_ofs, 16, false, &msg->vendor_specific_status_code);
    *bit_ofs += 16;

    return false; /* success */
}
#endif
#ifdef CANARD_DSDLC_TEST_BUILD
struct uavcan_protocol_NodeStatus sample_uavcan_protocol_NodeStatus_msg(void);
#endif
#ifdef __cplusplus
} // extern "C"

#ifdef DRONECAN_CXX_WRAPPERS
#include <canard/cxx_wrappers.h>
BROADCAST_MESSAGE_CXX_IFACE(uavcan_protocol_NodeStatus, UAVCAN_PROTOCOL_NODESTATUS_ID, UAVCAN_PROTOCOL_NODESTATUS_SIGNATURE, UAVCAN_PROTOCOL_NODESTATUS_MAX_SIZE);
#endif
#endif
