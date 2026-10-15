/*
 * 中文导读：DSDL生成协议代码：动态节点号分配，使用唯一ID分段握手。
 * 编解码位宽、字段顺序、类型签名与ID共同决定兼容性。TAO表示尾数组优化；内部decode返回true表示失败。
 * 本文件的中文注释用于阅读，运行regenerate.sh重新生成时可能被覆盖；生成了类型不代表业务层已使用该功能。
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <canard.h>


#define UAVCAN_PROTOCOL_DYNAMIC_NODE_ID_ALLOCATION_MAX_SIZE 18
#define UAVCAN_PROTOCOL_DYNAMIC_NODE_ID_ALLOCATION_SIGNATURE (0xB2A812620A11D40ULL)
#define UAVCAN_PROTOCOL_DYNAMIC_NODE_ID_ALLOCATION_ID 1

#define UAVCAN_PROTOCOL_DYNAMIC_NODE_ID_ALLOCATION_MAX_REQUEST_PERIOD_MS 1000
#define UAVCAN_PROTOCOL_DYNAMIC_NODE_ID_ALLOCATION_MIN_REQUEST_PERIOD_MS 600
#define UAVCAN_PROTOCOL_DYNAMIC_NODE_ID_ALLOCATION_MAX_FOLLOWUP_DELAY_MS 400
#define UAVCAN_PROTOCOL_DYNAMIC_NODE_ID_ALLOCATION_MIN_FOLLOWUP_DELAY_MS 0
#define UAVCAN_PROTOCOL_DYNAMIC_NODE_ID_ALLOCATION_FOLLOWUP_TIMEOUT_MS 500
#define UAVCAN_PROTOCOL_DYNAMIC_NODE_ID_ALLOCATION_MAX_LENGTH_OF_UNIQUE_ID_IN_REQUEST 6
#define UAVCAN_PROTOCOL_DYNAMIC_NODE_ID_ALLOCATION_ANY_NODE_ID 0

#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
class uavcan_protocol_dynamic_node_id_Allocation_cxx_iface;
#endif

struct uavcan_protocol_dynamic_node_id_Allocation {
#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
    using cxx_iface = uavcan_protocol_dynamic_node_id_Allocation_cxx_iface;
#endif
    uint8_t node_id; // CAN节点号
    bool first_part_of_unique_id; // 是否为唯一ID的首段
    struct { uint8_t len; uint8_t data[16]; }unique_id;
};

#ifdef __cplusplus
extern "C"
{
#endif

uint32_t uavcan_protocol_dynamic_node_id_Allocation_encode(struct uavcan_protocol_dynamic_node_id_Allocation* msg, uint8_t* buffer
#if CANARD_ENABLE_TAO_OPTION
    , bool tao
#endif
);
bool uavcan_protocol_dynamic_node_id_Allocation_decode(const CanardRxTransfer* transfer, struct uavcan_protocol_dynamic_node_id_Allocation* msg);

#if defined(CANARD_DSDLC_INTERNAL)
static inline void _uavcan_protocol_dynamic_node_id_Allocation_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_protocol_dynamic_node_id_Allocation* msg, bool tao);
static inline bool _uavcan_protocol_dynamic_node_id_Allocation_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_protocol_dynamic_node_id_Allocation* msg, bool tao);
/** 中文说明：将本类型结构序列化为协议位流；外层encode返回字节数，带前导下划线的内部入口推进bit_ofs，供嵌套类型复用。 */
void _uavcan_protocol_dynamic_node_id_Allocation_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_protocol_dynamic_node_id_Allocation* msg, bool tao) {
    (void)buffer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;

    canardEncodeScalar(buffer, *bit_ofs, 7, &msg->node_id);
    *bit_ofs += 7;
    canardEncodeScalar(buffer, *bit_ofs, 1, &msg->first_part_of_unique_id);
    *bit_ofs += 1;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
    const uint8_t unique_id_len = msg->unique_id.len > 16 ? 16 : msg->unique_id.len;
#pragma GCC diagnostic pop
    if (!tao) {
        canardEncodeScalar(buffer, *bit_ofs, 5, &unique_id_len);
        *bit_ofs += 5;
    }
    for (size_t i=0; i < unique_id_len; i++) {
        canardEncodeScalar(buffer, *bit_ofs, 8, &msg->unique_id.data[i]);
        *bit_ofs += 8;
    }
}

/*
 decode uavcan_protocol_dynamic_node_id_Allocation, return true on failure, false on success
*/
/** 中文说明：按DSDL字段位宽反序列化；返回true表示失败、false表示成功；内部入口推进bit_ofs，外层还核对载荷长度。 */
bool _uavcan_protocol_dynamic_node_id_Allocation_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_protocol_dynamic_node_id_Allocation* msg, bool tao) {
    (void)transfer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;
    canardDecodeScalar(transfer, *bit_ofs, 7, false, &msg->node_id);
    *bit_ofs += 7;

    canardDecodeScalar(transfer, *bit_ofs, 1, false, &msg->first_part_of_unique_id);
    *bit_ofs += 1;

    if (!tao) {
        canardDecodeScalar(transfer, *bit_ofs, 5, false, &msg->unique_id.len);
        *bit_ofs += 5;
    } else {
        msg->unique_id.len = ((transfer->payload_len*8)-*bit_ofs)/8;
    }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
    if (msg->unique_id.len > 16) {
        return true; /* invalid value */
    }
#pragma GCC diagnostic pop
    for (size_t i=0; i < msg->unique_id.len; i++) {
        canardDecodeScalar(transfer, *bit_ofs, 8, false, &msg->unique_id.data[i]);
        *bit_ofs += 8;
    }

    return false; /* success */
}
#endif
#ifdef CANARD_DSDLC_TEST_BUILD
struct uavcan_protocol_dynamic_node_id_Allocation sample_uavcan_protocol_dynamic_node_id_Allocation_msg(void);
#endif
#ifdef __cplusplus
} // extern "C"

#ifdef DRONECAN_CXX_WRAPPERS
#include <canard/cxx_wrappers.h>
BROADCAST_MESSAGE_CXX_IFACE(uavcan_protocol_dynamic_node_id_Allocation, UAVCAN_PROTOCOL_DYNAMIC_NODE_ID_ALLOCATION_ID, UAVCAN_PROTOCOL_DYNAMIC_NODE_ID_ALLOCATION_SIGNATURE, UAVCAN_PROTOCOL_DYNAMIC_NODE_ID_ALLOCATION_MAX_SIZE);
#endif
#endif
