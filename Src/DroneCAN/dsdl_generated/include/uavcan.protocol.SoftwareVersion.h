/*
 * 中文导读：DSDL生成协议代码：软件版本、提交号和镜像校验信息。
 * 编解码位宽、字段顺序、类型签名与ID共同决定兼容性。TAO表示尾数组优化；内部decode返回true表示失败。
 * 本文件的中文注释用于阅读，运行regenerate.sh重新生成时可能被覆盖；生成了类型不代表业务层已使用该功能。
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <canard.h>


#define UAVCAN_PROTOCOL_SOFTWAREVERSION_MAX_SIZE 15
#define UAVCAN_PROTOCOL_SOFTWAREVERSION_SIGNATURE (0xDD46FD376527FEA1ULL)

#define UAVCAN_PROTOCOL_SOFTWAREVERSION_OPTIONAL_FIELD_FLAG_VCS_COMMIT 1
#define UAVCAN_PROTOCOL_SOFTWAREVERSION_OPTIONAL_FIELD_FLAG_IMAGE_CRC 2


struct uavcan_protocol_SoftwareVersion {
    uint8_t major; // 主版本号
    uint8_t minor; // 次版本号
    uint8_t optional_field_flags; // 可选版本字段有效标志
    uint32_t vcs_commit; // 版本控制提交标识字段
    uint64_t image_crc; // 固件镜像CRC
};

#ifdef __cplusplus
extern "C"
{
#endif

uint32_t uavcan_protocol_SoftwareVersion_encode(struct uavcan_protocol_SoftwareVersion* msg, uint8_t* buffer
#if CANARD_ENABLE_TAO_OPTION
    , bool tao
#endif
);
bool uavcan_protocol_SoftwareVersion_decode(const CanardRxTransfer* transfer, struct uavcan_protocol_SoftwareVersion* msg);

#if defined(CANARD_DSDLC_INTERNAL)
static inline void _uavcan_protocol_SoftwareVersion_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_protocol_SoftwareVersion* msg, bool tao);
static inline bool _uavcan_protocol_SoftwareVersion_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_protocol_SoftwareVersion* msg, bool tao);
/** 中文说明：将本类型结构序列化为协议位流；外层encode返回字节数，带前导下划线的内部入口推进bit_ofs，供嵌套类型复用。 */
void _uavcan_protocol_SoftwareVersion_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_protocol_SoftwareVersion* msg, bool tao) {
    (void)buffer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;

    canardEncodeScalar(buffer, *bit_ofs, 8, &msg->major);
    *bit_ofs += 8;
    canardEncodeScalar(buffer, *bit_ofs, 8, &msg->minor);
    *bit_ofs += 8;
    canardEncodeScalar(buffer, *bit_ofs, 8, &msg->optional_field_flags);
    *bit_ofs += 8;
    canardEncodeScalar(buffer, *bit_ofs, 32, &msg->vcs_commit);
    *bit_ofs += 32;
    canardEncodeScalar(buffer, *bit_ofs, 64, &msg->image_crc);
    *bit_ofs += 64;
}

/*
 decode uavcan_protocol_SoftwareVersion, return true on failure, false on success
*/
/** 中文说明：按DSDL字段位宽反序列化；返回true表示失败、false表示成功；内部入口推进bit_ofs，外层还核对载荷长度。 */
bool _uavcan_protocol_SoftwareVersion_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_protocol_SoftwareVersion* msg, bool tao) {
    (void)transfer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;
    canardDecodeScalar(transfer, *bit_ofs, 8, false, &msg->major);
    *bit_ofs += 8;

    canardDecodeScalar(transfer, *bit_ofs, 8, false, &msg->minor);
    *bit_ofs += 8;

    canardDecodeScalar(transfer, *bit_ofs, 8, false, &msg->optional_field_flags);
    *bit_ofs += 8;

    canardDecodeScalar(transfer, *bit_ofs, 32, false, &msg->vcs_commit);
    *bit_ofs += 32;

    canardDecodeScalar(transfer, *bit_ofs, 64, false, &msg->image_crc);
    *bit_ofs += 64;

    return false; /* success */
}
#endif
#ifdef CANARD_DSDLC_TEST_BUILD
struct uavcan_protocol_SoftwareVersion sample_uavcan_protocol_SoftwareVersion_msg(void);
#endif
#ifdef __cplusplus
} // extern "C"

#ifdef DRONECAN_CXX_WRAPPERS
#include <canard/cxx_wrappers.h>
#endif
#endif
