/*
 * 中文导读：DSDL生成协议代码：电调扩展状态，包括输入/输出百分比、电机角度和状态标志。
 * 编解码位宽、字段顺序、类型签名与ID共同决定兼容性。TAO表示尾数组优化；内部decode返回true表示失败。
 * 本文件的中文注释用于阅读，运行regenerate.sh重新生成时可能被覆盖；生成了类型不代表业务层已使用该功能。
 */

#define CANARD_DSDLC_INTERNAL
#include <uavcan.equipment.esc.StatusExtended.h>
#include <string.h>

#ifdef CANARD_DSDLC_TEST_BUILD
#include <test_helpers.h>
#endif

/** 中文说明：将本类型结构序列化为协议位流；外层encode返回字节数，带前导下划线的内部入口推进bit_ofs，供嵌套类型复用。 */
uint32_t uavcan_equipment_esc_StatusExtended_encode(struct uavcan_equipment_esc_StatusExtended* msg, uint8_t* buffer
#if CANARD_ENABLE_TAO_OPTION
    , bool tao
#endif
) {
    uint32_t bit_ofs = 0;
    memset(buffer, 0, UAVCAN_EQUIPMENT_ESC_STATUSEXTENDED_MAX_SIZE);
    _uavcan_equipment_esc_StatusExtended_encode(buffer, &bit_ofs, msg, 
#if CANARD_ENABLE_TAO_OPTION
    tao
#else
    true
#endif
    );
    return ((bit_ofs+7)/8);
}

/*
  return true if the decode is invalid
 */
/** 中文说明：按DSDL字段位宽反序列化；返回true表示失败、false表示成功；内部入口推进bit_ofs，外层还核对载荷长度。 */
bool uavcan_equipment_esc_StatusExtended_decode(const CanardRxTransfer* transfer, struct uavcan_equipment_esc_StatusExtended* msg) {
#if CANARD_ENABLE_TAO_OPTION
    if (transfer->tao && (transfer->payload_len > UAVCAN_EQUIPMENT_ESC_STATUSEXTENDED_MAX_SIZE)) {
        return true; /* invalid payload length */
    }
#endif
    uint32_t bit_ofs = 0;
    if (_uavcan_equipment_esc_StatusExtended_decode(transfer, &bit_ofs, msg,
#if CANARD_ENABLE_TAO_OPTION
    transfer->tao
#else
    true
#endif
    )) {
        return true; /* invalid payload */
    }

    const uint32_t byte_len = (bit_ofs+7U)/8U;
#if CANARD_ENABLE_TAO_OPTION
    // if this could be CANFD then the dlc could indicating more bytes than
    // we actually have
    if (!transfer->tao) {
        return byte_len > transfer->payload_len;
    }
#endif
    return byte_len != transfer->payload_len;
}

#ifdef CANARD_DSDLC_TEST_BUILD
/** 中文说明：仅在CANARD_DSDLC_TEST_BUILD启用时生成随机样本，供编解码测试使用，不是电调实际控制指令。 */
struct uavcan_equipment_esc_StatusExtended sample_uavcan_equipment_esc_StatusExtended_msg(void) {
    struct uavcan_equipment_esc_StatusExtended msg;

    msg.input_pct = (uint8_t)random_bitlen_unsigned_val(7);
    msg.output_pct = (uint8_t)random_bitlen_unsigned_val(7);
    msg.motor_temperature_degC = (int16_t)random_bitlen_signed_val(9);
    msg.motor_angle = (uint16_t)random_bitlen_unsigned_val(9);
    msg.status_flags = (uint32_t)random_bitlen_unsigned_val(19);
    msg.esc_index = (uint8_t)random_bitlen_unsigned_val(5);
    return msg;
}
#endif
