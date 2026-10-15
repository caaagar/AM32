/*
 * 中文导读：DSDL生成协议代码：电调扩展状态，包括输入/输出百分比、电机角度和状态标志。
 * 编解码位宽、字段顺序、类型签名与ID共同决定兼容性。TAO表示尾数组优化；内部decode返回true表示失败。
 * 本文件的中文注释用于阅读，运行regenerate.sh重新生成时可能被覆盖；生成了类型不代表业务层已使用该功能。
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <canard.h>


#define UAVCAN_EQUIPMENT_ESC_STATUSEXTENDED_MAX_SIZE 7
#define UAVCAN_EQUIPMENT_ESC_STATUSEXTENDED_SIGNATURE (0x2DC203C50960EDCULL)
#define UAVCAN_EQUIPMENT_ESC_STATUSEXTENDED_ID 1036

#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
class uavcan_equipment_esc_StatusExtended_cxx_iface;
#endif

struct uavcan_equipment_esc_StatusExtended {
#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
    using cxx_iface = uavcan_equipment_esc_StatusExtended_cxx_iface;
#endif
    uint8_t input_pct; // 输入百分比
    uint8_t output_pct; // 输出百分比
    int16_t motor_temperature_degC; // 电机温度，单位摄氏度
    uint16_t motor_angle; // 电机角度编码，按本协议类型解释
    uint32_t status_flags; // 状态位集合
    uint8_t esc_index; // 电调在指令数组/系统中的索引
};

#ifdef __cplusplus
extern "C"
{
#endif

uint32_t uavcan_equipment_esc_StatusExtended_encode(struct uavcan_equipment_esc_StatusExtended* msg, uint8_t* buffer
#if CANARD_ENABLE_TAO_OPTION
    , bool tao
#endif
);
bool uavcan_equipment_esc_StatusExtended_decode(const CanardRxTransfer* transfer, struct uavcan_equipment_esc_StatusExtended* msg);

#if defined(CANARD_DSDLC_INTERNAL)
static inline void _uavcan_equipment_esc_StatusExtended_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_equipment_esc_StatusExtended* msg, bool tao);
static inline bool _uavcan_equipment_esc_StatusExtended_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_equipment_esc_StatusExtended* msg, bool tao);
/** 中文说明：将本类型结构序列化为协议位流；外层encode返回字节数，带前导下划线的内部入口推进bit_ofs，供嵌套类型复用。 */
void _uavcan_equipment_esc_StatusExtended_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_equipment_esc_StatusExtended* msg, bool tao) {
    (void)buffer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;

    canardEncodeScalar(buffer, *bit_ofs, 7, &msg->input_pct);
    *bit_ofs += 7;
    canardEncodeScalar(buffer, *bit_ofs, 7, &msg->output_pct);
    *bit_ofs += 7;
    canardEncodeScalar(buffer, *bit_ofs, 9, &msg->motor_temperature_degC);
    *bit_ofs += 9;
    canardEncodeScalar(buffer, *bit_ofs, 9, &msg->motor_angle);
    *bit_ofs += 9;
    canardEncodeScalar(buffer, *bit_ofs, 19, &msg->status_flags);
    *bit_ofs += 19;
    canardEncodeScalar(buffer, *bit_ofs, 5, &msg->esc_index);
    *bit_ofs += 5;
}

/*
 decode uavcan_equipment_esc_StatusExtended, return true on failure, false on success
*/
/** 中文说明：按DSDL字段位宽反序列化；返回true表示失败、false表示成功；内部入口推进bit_ofs，外层还核对载荷长度。 */
bool _uavcan_equipment_esc_StatusExtended_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_equipment_esc_StatusExtended* msg, bool tao) {
    (void)transfer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;
    canardDecodeScalar(transfer, *bit_ofs, 7, false, &msg->input_pct);
    *bit_ofs += 7;

    canardDecodeScalar(transfer, *bit_ofs, 7, false, &msg->output_pct);
    *bit_ofs += 7;

    canardDecodeScalar(transfer, *bit_ofs, 9, true, &msg->motor_temperature_degC);
    *bit_ofs += 9;

    canardDecodeScalar(transfer, *bit_ofs, 9, false, &msg->motor_angle);
    *bit_ofs += 9;

    canardDecodeScalar(transfer, *bit_ofs, 19, false, &msg->status_flags);
    *bit_ofs += 19;

    canardDecodeScalar(transfer, *bit_ofs, 5, false, &msg->esc_index);
    *bit_ofs += 5;

    return false; /* success */
}
#endif
#ifdef CANARD_DSDLC_TEST_BUILD
struct uavcan_equipment_esc_StatusExtended sample_uavcan_equipment_esc_StatusExtended_msg(void);
#endif
#ifdef __cplusplus
} // extern "C"

#ifdef DRONECAN_CXX_WRAPPERS
#include <canard/cxx_wrappers.h>
BROADCAST_MESSAGE_CXX_IFACE(uavcan_equipment_esc_StatusExtended, UAVCAN_EQUIPMENT_ESC_STATUSEXTENDED_ID, UAVCAN_EQUIPMENT_ESC_STATUSEXTENDED_SIGNATURE, UAVCAN_EQUIPMENT_ESC_STATUSEXTENDED_MAX_SIZE);
#endif
#endif
