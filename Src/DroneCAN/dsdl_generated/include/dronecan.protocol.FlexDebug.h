/*
 * 中文导读：DSDL生成协议代码：可变长度调试数据，业务含义由id及应用打包格式确定。
 * 编解码位宽、字段顺序、类型签名与ID共同决定兼容性。TAO表示尾数组优化；内部decode返回true表示失败。
 * 本文件的中文注释用于阅读，运行regenerate.sh重新生成时可能被覆盖；生成了类型不代表业务层已使用该功能。
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <canard.h>


#define DRONECAN_PROTOCOL_FLEXDEBUG_MAX_SIZE 258
#define DRONECAN_PROTOCOL_FLEXDEBUG_SIGNATURE (0xECA60382FF038F39ULL)
#define DRONECAN_PROTOCOL_FLEXDEBUG_ID 16371

#define DRONECAN_PROTOCOL_FLEXDEBUG_RESERVATION_SIZE 10
#define DRONECAN_PROTOCOL_FLEXDEBUG_AM32_RESERVE_START 100

#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
class dronecan_protocol_FlexDebug_cxx_iface;
#endif

struct dronecan_protocol_FlexDebug {
#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
    using cxx_iface = dronecan_protocol_FlexDebug_cxx_iface;
#endif
    uint16_t id; // 调试数据标识号
    struct { uint8_t len; uint8_t data[255]; }u8;
};

#ifdef __cplusplus
extern "C"
{
#endif

uint32_t dronecan_protocol_FlexDebug_encode(struct dronecan_protocol_FlexDebug* msg, uint8_t* buffer
#if CANARD_ENABLE_TAO_OPTION
    , bool tao
#endif
);
bool dronecan_protocol_FlexDebug_decode(const CanardRxTransfer* transfer, struct dronecan_protocol_FlexDebug* msg);

#if defined(CANARD_DSDLC_INTERNAL)
static inline void _dronecan_protocol_FlexDebug_encode(uint8_t* buffer, uint32_t* bit_ofs, struct dronecan_protocol_FlexDebug* msg, bool tao);
static inline bool _dronecan_protocol_FlexDebug_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct dronecan_protocol_FlexDebug* msg, bool tao);
/** 中文说明：将本类型结构序列化为协议位流；外层encode返回字节数，带前导下划线的内部入口推进bit_ofs，供嵌套类型复用。 */
void _dronecan_protocol_FlexDebug_encode(uint8_t* buffer, uint32_t* bit_ofs, struct dronecan_protocol_FlexDebug* msg, bool tao) {
    (void)buffer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;

    canardEncodeScalar(buffer, *bit_ofs, 16, &msg->id);
    *bit_ofs += 16;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
    const uint8_t u8_len = msg->u8.len > 255 ? 255 : msg->u8.len;
#pragma GCC diagnostic pop
    if (!tao) {
        canardEncodeScalar(buffer, *bit_ofs, 8, &u8_len);
        *bit_ofs += 8;
    }
    for (size_t i=0; i < u8_len; i++) {
        canardEncodeScalar(buffer, *bit_ofs, 8, &msg->u8.data[i]);
        *bit_ofs += 8;
    }
}

/*
 decode dronecan_protocol_FlexDebug, return true on failure, false on success
*/
/** 中文说明：按DSDL字段位宽反序列化；返回true表示失败、false表示成功；内部入口推进bit_ofs，外层还核对载荷长度。 */
bool _dronecan_protocol_FlexDebug_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct dronecan_protocol_FlexDebug* msg, bool tao) {
    (void)transfer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;
    canardDecodeScalar(transfer, *bit_ofs, 16, false, &msg->id);
    *bit_ofs += 16;

    if (!tao) {
        canardDecodeScalar(transfer, *bit_ofs, 8, false, &msg->u8.len);
        *bit_ofs += 8;
    } else {
        msg->u8.len = ((transfer->payload_len*8)-*bit_ofs)/8;
    }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
    if (msg->u8.len > 255) {
        return true; /* invalid value */
    }
#pragma GCC diagnostic pop
    for (size_t i=0; i < msg->u8.len; i++) {
        canardDecodeScalar(transfer, *bit_ofs, 8, false, &msg->u8.data[i]);
        *bit_ofs += 8;
    }

    return false; /* success */
}
#endif
#ifdef CANARD_DSDLC_TEST_BUILD
struct dronecan_protocol_FlexDebug sample_dronecan_protocol_FlexDebug_msg(void);
#endif
#ifdef __cplusplus
} // extern "C"

#ifdef DRONECAN_CXX_WRAPPERS
#include <canard/cxx_wrappers.h>
BROADCAST_MESSAGE_CXX_IFACE(dronecan_protocol_FlexDebug, DRONECAN_PROTOCOL_FLEXDEBUG_ID, DRONECAN_PROTOCOL_FLEXDEBUG_SIGNATURE, DRONECAN_PROTOCOL_FLEXDEBUG_MAX_SIZE);
#endif
#endif
