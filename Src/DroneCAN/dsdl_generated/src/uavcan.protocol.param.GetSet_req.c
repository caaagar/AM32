/*
 * 中文导读：DSDL生成协议代码：按名称或索引读取参数，或设置参数并返回当前信息。此文件对应服务请求。
 * 编解码位宽、字段顺序、类型签名与ID共同决定兼容性。TAO表示尾数组优化；内部decode返回true表示失败。
 * 本文件的中文注释用于阅读，运行regenerate.sh重新生成时可能被覆盖；生成了类型不代表业务层已使用该功能。
 */

#define CANARD_DSDLC_INTERNAL
#include <uavcan.protocol.param.GetSet_req.h>
#include <uavcan.protocol.param.GetSet_res.h>
#include <string.h>

#ifdef CANARD_DSDLC_TEST_BUILD
#include <test_helpers.h>
#endif

/** 中文说明：将本类型结构序列化为协议位流；外层encode返回字节数，带前导下划线的内部入口推进bit_ofs，供嵌套类型复用。 */
uint32_t uavcan_protocol_param_GetSetRequest_encode(struct uavcan_protocol_param_GetSetRequest* msg, uint8_t* buffer
#if CANARD_ENABLE_TAO_OPTION
    , bool tao
#endif
) {
    uint32_t bit_ofs = 0;
    memset(buffer, 0, UAVCAN_PROTOCOL_PARAM_GETSET_REQUEST_MAX_SIZE);
    _uavcan_protocol_param_GetSetRequest_encode(buffer, &bit_ofs, msg, 
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
bool uavcan_protocol_param_GetSetRequest_decode(const CanardRxTransfer* transfer, struct uavcan_protocol_param_GetSetRequest* msg) {
#if CANARD_ENABLE_TAO_OPTION
    if (transfer->tao && (transfer->payload_len > UAVCAN_PROTOCOL_PARAM_GETSET_REQUEST_MAX_SIZE)) {
        return true; /* invalid payload length */
    }
#endif
    uint32_t bit_ofs = 0;
    if (_uavcan_protocol_param_GetSetRequest_decode(transfer, &bit_ofs, msg,
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
struct uavcan_protocol_param_GetSetRequest sample_uavcan_protocol_param_GetSetRequest_msg(void) {
    struct uavcan_protocol_param_GetSetRequest msg;

    msg.index = (uint16_t)random_bitlen_unsigned_val(13);
    msg.value = sample_uavcan_protocol_param_Value_msg();
    msg.name.len = (uint8_t)random_range_unsigned_val(0, 92);
    for (size_t i=0; i < msg.name.len; i++) {
        msg.name.data[i] = (uint8_t)random_bitlen_unsigned_val(8);
    }
    return msg;
}
#endif
