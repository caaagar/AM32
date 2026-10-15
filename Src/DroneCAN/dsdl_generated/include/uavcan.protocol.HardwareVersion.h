/*
 * 中文导读：DSDL生成协议代码：硬件版本、唯一ID和可选证书数据。
 * 编解码位宽、字段顺序、类型签名与ID共同决定兼容性。TAO表示尾数组优化；内部decode返回true表示失败。
 * 本文件的中文注释用于阅读，运行regenerate.sh重新生成时可能被覆盖；生成了类型不代表业务层已使用该功能。
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <canard.h>


#define UAVCAN_PROTOCOL_HARDWAREVERSION_MAX_SIZE 274
#define UAVCAN_PROTOCOL_HARDWAREVERSION_SIGNATURE (0xAD5C4C933F4A0C4ULL)


struct uavcan_protocol_HardwareVersion {
    uint8_t major; // 主版本号
    uint8_t minor; // 次版本号
    uint8_t unique_id[16]; // 硬件唯一ID字节序列
    struct { uint8_t len; uint8_t data[255]; }certificate_of_authenticity;
};

#ifdef __cplusplus
extern "C"
{
#endif

uint32_t uavcan_protocol_HardwareVersion_encode(struct uavcan_protocol_HardwareVersion* msg, uint8_t* buffer
#if CANARD_ENABLE_TAO_OPTION
    , bool tao
#endif
);
bool uavcan_protocol_HardwareVersion_decode(const CanardRxTransfer* transfer, struct uavcan_protocol_HardwareVersion* msg);

#if defined(CANARD_DSDLC_INTERNAL)
static inline void _uavcan_protocol_HardwareVersion_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_protocol_HardwareVersion* msg, bool tao);
static inline bool _uavcan_protocol_HardwareVersion_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_protocol_HardwareVersion* msg, bool tao);
/** 中文说明：将本类型结构序列化为协议位流；外层encode返回字节数，带前导下划线的内部入口推进bit_ofs，供嵌套类型复用。 */
void _uavcan_protocol_HardwareVersion_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_protocol_HardwareVersion* msg, bool tao) {
    (void)buffer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;

    canardEncodeScalar(buffer, *bit_ofs, 8, &msg->major);
    *bit_ofs += 8;
    canardEncodeScalar(buffer, *bit_ofs, 8, &msg->minor);
    *bit_ofs += 8;
    for (size_t i=0; i < 16; i++) {
        canardEncodeScalar(buffer, *bit_ofs, 8, &msg->unique_id[i]);
        *bit_ofs += 8;
    }
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
    const uint8_t certificate_of_authenticity_len = msg->certificate_of_authenticity.len > 255 ? 255 : msg->certificate_of_authenticity.len;
#pragma GCC diagnostic pop
    if (!tao) {
        canardEncodeScalar(buffer, *bit_ofs, 8, &certificate_of_authenticity_len);
        *bit_ofs += 8;
    }
    for (size_t i=0; i < certificate_of_authenticity_len; i++) {
        canardEncodeScalar(buffer, *bit_ofs, 8, &msg->certificate_of_authenticity.data[i]);
        *bit_ofs += 8;
    }
}

/*
 decode uavcan_protocol_HardwareVersion, return true on failure, false on success
*/
/** 中文说明：按DSDL字段位宽反序列化；返回true表示失败、false表示成功；内部入口推进bit_ofs，外层还核对载荷长度。 */
bool _uavcan_protocol_HardwareVersion_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_protocol_HardwareVersion* msg, bool tao) {
    (void)transfer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;
    canardDecodeScalar(transfer, *bit_ofs, 8, false, &msg->major);
    *bit_ofs += 8;

    canardDecodeScalar(transfer, *bit_ofs, 8, false, &msg->minor);
    *bit_ofs += 8;

    for (size_t i=0; i < 16; i++) {
        canardDecodeScalar(transfer, *bit_ofs, 8, false, &msg->unique_id[i]);
        *bit_ofs += 8;
    }

    if (!tao) {
        canardDecodeScalar(transfer, *bit_ofs, 8, false, &msg->certificate_of_authenticity.len);
        *bit_ofs += 8;
    } else {
        msg->certificate_of_authenticity.len = ((transfer->payload_len*8)-*bit_ofs)/8;
    }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
    if (msg->certificate_of_authenticity.len > 255) {
        return true; /* invalid value */
    }
#pragma GCC diagnostic pop
    for (size_t i=0; i < msg->certificate_of_authenticity.len; i++) {
        canardDecodeScalar(transfer, *bit_ofs, 8, false, &msg->certificate_of_authenticity.data[i]);
        *bit_ofs += 8;
    }

    return false; /* success */
}
#endif
#ifdef CANARD_DSDLC_TEST_BUILD
struct uavcan_protocol_HardwareVersion sample_uavcan_protocol_HardwareVersion_msg(void);
#endif
#ifdef __cplusplus
} // extern "C"

#ifdef DRONECAN_CXX_WRAPPERS
#include <canard/cxx_wrappers.h>
#endif
#endif
