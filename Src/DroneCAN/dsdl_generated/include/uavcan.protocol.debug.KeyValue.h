/*
 * 中文导读：DSDL生成协议代码：调试键名与数值。
 * 编解码位宽、字段顺序、类型签名与ID共同决定兼容性。TAO表示尾数组优化；内部decode返回true表示失败。
 * 本文件的中文注释用于阅读，运行regenerate.sh重新生成时可能被覆盖；生成了类型不代表业务层已使用该功能。
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <canard.h>


#define UAVCAN_PROTOCOL_DEBUG_KEYVALUE_MAX_SIZE 63
#define UAVCAN_PROTOCOL_DEBUG_KEYVALUE_SIGNATURE (0xE02F25D6E0C98AE0ULL)
#define UAVCAN_PROTOCOL_DEBUG_KEYVALUE_ID 16370

#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
class uavcan_protocol_debug_KeyValue_cxx_iface;
#endif

struct uavcan_protocol_debug_KeyValue {
#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
    using cxx_iface = uavcan_protocol_debug_KeyValue_cxx_iface;
#endif
    float value; // 类型承载的数值/枚举值
    struct { uint8_t len; uint8_t data[58]; }key;
};

#ifdef __cplusplus
extern "C"
{
#endif

uint32_t uavcan_protocol_debug_KeyValue_encode(struct uavcan_protocol_debug_KeyValue* msg, uint8_t* buffer
#if CANARD_ENABLE_TAO_OPTION
    , bool tao
#endif
);
bool uavcan_protocol_debug_KeyValue_decode(const CanardRxTransfer* transfer, struct uavcan_protocol_debug_KeyValue* msg);

#if defined(CANARD_DSDLC_INTERNAL)
static inline void _uavcan_protocol_debug_KeyValue_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_protocol_debug_KeyValue* msg, bool tao);
static inline bool _uavcan_protocol_debug_KeyValue_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_protocol_debug_KeyValue* msg, bool tao);
/** 中文说明：将本类型结构序列化为协议位流；外层encode返回字节数，带前导下划线的内部入口推进bit_ofs，供嵌套类型复用。 */
void _uavcan_protocol_debug_KeyValue_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_protocol_debug_KeyValue* msg, bool tao) {
    (void)buffer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;

    canardEncodeScalar(buffer, *bit_ofs, 32, &msg->value);
    *bit_ofs += 32;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
    const uint8_t key_len = msg->key.len > 58 ? 58 : msg->key.len;
#pragma GCC diagnostic pop
    if (!tao) {
        canardEncodeScalar(buffer, *bit_ofs, 6, &key_len);
        *bit_ofs += 6;
    }
    for (size_t i=0; i < key_len; i++) {
        canardEncodeScalar(buffer, *bit_ofs, 8, &msg->key.data[i]);
        *bit_ofs += 8;
    }
}

/*
 decode uavcan_protocol_debug_KeyValue, return true on failure, false on success
*/
/** 中文说明：按DSDL字段位宽反序列化；返回true表示失败、false表示成功；内部入口推进bit_ofs，外层还核对载荷长度。 */
bool _uavcan_protocol_debug_KeyValue_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_protocol_debug_KeyValue* msg, bool tao) {
    (void)transfer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;
    canardDecodeScalar(transfer, *bit_ofs, 32, true, &msg->value);
    *bit_ofs += 32;

    if (!tao) {
        canardDecodeScalar(transfer, *bit_ofs, 6, false, &msg->key.len);
        *bit_ofs += 6;
    } else {
        msg->key.len = ((transfer->payload_len*8)-*bit_ofs)/8;
    }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
    if (msg->key.len > 58) {
        return true; /* invalid value */
    }
#pragma GCC diagnostic pop
    for (size_t i=0; i < msg->key.len; i++) {
        canardDecodeScalar(transfer, *bit_ofs, 8, false, &msg->key.data[i]);
        *bit_ofs += 8;
    }

    return false; /* success */
}
#endif
#ifdef CANARD_DSDLC_TEST_BUILD
struct uavcan_protocol_debug_KeyValue sample_uavcan_protocol_debug_KeyValue_msg(void);
#endif
#ifdef __cplusplus
} // extern "C"

#ifdef DRONECAN_CXX_WRAPPERS
#include <canard/cxx_wrappers.h>
BROADCAST_MESSAGE_CXX_IFACE(uavcan_protocol_debug_KeyValue, UAVCAN_PROTOCOL_DEBUG_KEYVALUE_ID, UAVCAN_PROTOCOL_DEBUG_KEYVALUE_SIGNATURE, UAVCAN_PROTOCOL_DEBUG_KEYVALUE_MAX_SIZE);
#endif
#endif
