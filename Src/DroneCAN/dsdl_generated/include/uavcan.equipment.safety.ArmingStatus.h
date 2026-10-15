/*
 * 中文导读：DSDL生成协议代码：系统解锁状态，用于决定是否允许应用电机指令。
 * 编解码位宽、字段顺序、类型签名与ID共同决定兼容性。TAO表示尾数组优化；内部decode返回true表示失败。
 * 本文件的中文注释用于阅读，运行regenerate.sh重新生成时可能被覆盖；生成了类型不代表业务层已使用该功能。
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <canard.h>


#define UAVCAN_EQUIPMENT_SAFETY_ARMINGSTATUS_MAX_SIZE 1
#define UAVCAN_EQUIPMENT_SAFETY_ARMINGSTATUS_SIGNATURE (0x8700F375556A8003ULL)
#define UAVCAN_EQUIPMENT_SAFETY_ARMINGSTATUS_ID 1100

#define UAVCAN_EQUIPMENT_SAFETY_ARMINGSTATUS_STATUS_DISARMED 0
#define UAVCAN_EQUIPMENT_SAFETY_ARMINGSTATUS_STATUS_FULLY_ARMED 255

#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
class uavcan_equipment_safety_ArmingStatus_cxx_iface;
#endif

struct uavcan_equipment_safety_ArmingStatus {
#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
    using cxx_iface = uavcan_equipment_safety_ArmingStatus_cxx_iface;
#endif
    uint8_t status; // 状态码；按本消息枚举解释
};

#ifdef __cplusplus
extern "C"
{
#endif

uint32_t uavcan_equipment_safety_ArmingStatus_encode(struct uavcan_equipment_safety_ArmingStatus* msg, uint8_t* buffer
#if CANARD_ENABLE_TAO_OPTION
    , bool tao
#endif
);
bool uavcan_equipment_safety_ArmingStatus_decode(const CanardRxTransfer* transfer, struct uavcan_equipment_safety_ArmingStatus* msg);

#if defined(CANARD_DSDLC_INTERNAL)
static inline void _uavcan_equipment_safety_ArmingStatus_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_equipment_safety_ArmingStatus* msg, bool tao);
static inline bool _uavcan_equipment_safety_ArmingStatus_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_equipment_safety_ArmingStatus* msg, bool tao);
/** 中文说明：将本类型结构序列化为协议位流；外层encode返回字节数，带前导下划线的内部入口推进bit_ofs，供嵌套类型复用。 */
void _uavcan_equipment_safety_ArmingStatus_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_equipment_safety_ArmingStatus* msg, bool tao) {
    (void)buffer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;

    canardEncodeScalar(buffer, *bit_ofs, 8, &msg->status);
    *bit_ofs += 8;
}

/*
 decode uavcan_equipment_safety_ArmingStatus, return true on failure, false on success
*/
/** 中文说明：按DSDL字段位宽反序列化；返回true表示失败、false表示成功；内部入口推进bit_ofs，外层还核对载荷长度。 */
bool _uavcan_equipment_safety_ArmingStatus_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_equipment_safety_ArmingStatus* msg, bool tao) {
    (void)transfer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;
    canardDecodeScalar(transfer, *bit_ofs, 8, false, &msg->status);
    *bit_ofs += 8;

    return false; /* success */
}
#endif
#ifdef CANARD_DSDLC_TEST_BUILD
struct uavcan_equipment_safety_ArmingStatus sample_uavcan_equipment_safety_ArmingStatus_msg(void);
#endif
#ifdef __cplusplus
} // extern "C"

#ifdef DRONECAN_CXX_WRAPPERS
#include <canard/cxx_wrappers.h>
BROADCAST_MESSAGE_CXX_IFACE(uavcan_equipment_safety_ArmingStatus, UAVCAN_EQUIPMENT_SAFETY_ARMINGSTATUS_ID, UAVCAN_EQUIPMENT_SAFETY_ARMINGSTATUS_SIGNATURE, UAVCAN_EQUIPMENT_SAFETY_ARMINGSTATUS_MAX_SIZE);
#endif
#endif
