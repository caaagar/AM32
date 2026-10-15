/*
 * 中文导读：DSDL生成协议代码：按通道提供目标机械转速的命令类型；这里只定义编解码，不保证AM32业务层订阅此消息。
 * 编解码位宽、字段顺序、类型签名与ID共同决定兼容性。TAO表示尾数组优化；内部decode返回true表示失败。
 * 本文件的中文注释用于阅读，运行regenerate.sh重新生成时可能被覆盖；生成了类型不代表业务层已使用该功能。
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <canard.h>


#define UAVCAN_EQUIPMENT_ESC_RPMCOMMAND_MAX_SIZE 46
#define UAVCAN_EQUIPMENT_ESC_RPMCOMMAND_SIGNATURE (0xCE0F9F621CF7E70BULL)
#define UAVCAN_EQUIPMENT_ESC_RPMCOMMAND_ID 1031

#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
class uavcan_equipment_esc_RPMCommand_cxx_iface;
#endif

struct uavcan_equipment_esc_RPMCommand {
#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
    using cxx_iface = uavcan_equipment_esc_RPMCommand_cxx_iface;
#endif
    struct { uint8_t len; int32_t data[20]; }rpm;
};

#ifdef __cplusplus
extern "C"
{
#endif

uint32_t uavcan_equipment_esc_RPMCommand_encode(struct uavcan_equipment_esc_RPMCommand* msg, uint8_t* buffer
#if CANARD_ENABLE_TAO_OPTION
    , bool tao
#endif
);
bool uavcan_equipment_esc_RPMCommand_decode(const CanardRxTransfer* transfer, struct uavcan_equipment_esc_RPMCommand* msg);

#if defined(CANARD_DSDLC_INTERNAL)
static inline void _uavcan_equipment_esc_RPMCommand_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_equipment_esc_RPMCommand* msg, bool tao);
static inline bool _uavcan_equipment_esc_RPMCommand_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_equipment_esc_RPMCommand* msg, bool tao);
/** 中文说明：将本类型结构序列化为协议位流；外层encode返回字节数，带前导下划线的内部入口推进bit_ofs，供嵌套类型复用。 */
void _uavcan_equipment_esc_RPMCommand_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_equipment_esc_RPMCommand* msg, bool tao) {
    (void)buffer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
    const uint8_t rpm_len = msg->rpm.len > 20 ? 20 : msg->rpm.len;
#pragma GCC diagnostic pop
    if (!tao) {
        canardEncodeScalar(buffer, *bit_ofs, 5, &rpm_len);
        *bit_ofs += 5;
    }
    for (size_t i=0; i < rpm_len; i++) {
        canardEncodeScalar(buffer, *bit_ofs, 18, &msg->rpm.data[i]);
        *bit_ofs += 18;
    }
}

/*
 decode uavcan_equipment_esc_RPMCommand, return true on failure, false on success
*/
/** 中文说明：按DSDL字段位宽反序列化；返回true表示失败、false表示成功；内部入口推进bit_ofs，外层还核对载荷长度。 */
bool _uavcan_equipment_esc_RPMCommand_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_equipment_esc_RPMCommand* msg, bool tao) {
    (void)transfer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;
    if (!tao) {
        canardDecodeScalar(transfer, *bit_ofs, 5, false, &msg->rpm.len);
        *bit_ofs += 5;
    } else {
        msg->rpm.len = ((transfer->payload_len*8)-*bit_ofs)/18;
    }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
    if (msg->rpm.len > 20) {
        return true; /* invalid value */
    }
#pragma GCC diagnostic pop
    for (size_t i=0; i < msg->rpm.len; i++) {
        canardDecodeScalar(transfer, *bit_ofs, 18, true, &msg->rpm.data[i]);
        *bit_ofs += 18;
    }

    return false; /* success */
}
#endif
#ifdef CANARD_DSDLC_TEST_BUILD
struct uavcan_equipment_esc_RPMCommand sample_uavcan_equipment_esc_RPMCommand_msg(void);
#endif
#ifdef __cplusplus
} // extern "C"

#ifdef DRONECAN_CXX_WRAPPERS
#include <canard/cxx_wrappers.h>
BROADCAST_MESSAGE_CXX_IFACE(uavcan_equipment_esc_RPMCommand, UAVCAN_EQUIPMENT_ESC_RPMCOMMAND_ID, UAVCAN_EQUIPMENT_ESC_RPMCOMMAND_SIGNATURE, UAVCAN_EQUIPMENT_ESC_RPMCOMMAND_MAX_SIZE);
#endif
#endif
