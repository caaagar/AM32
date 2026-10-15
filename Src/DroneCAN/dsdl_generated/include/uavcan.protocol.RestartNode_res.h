/*
 * 中文导读：DSDL生成协议代码：节点重启请求/响应服务。此文件对应服务响应。
 * 编解码位宽、字段顺序、类型签名与ID共同决定兼容性。TAO表示尾数组优化；内部decode返回true表示失败。
 * 本文件的中文注释用于阅读，运行regenerate.sh重新生成时可能被覆盖；生成了类型不代表业务层已使用该功能。
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <canard.h>


#define UAVCAN_PROTOCOL_RESTARTNODE_RESPONSE_MAX_SIZE 1
#define UAVCAN_PROTOCOL_RESTARTNODE_RESPONSE_SIGNATURE (0x569E05394A3017F0ULL)
#define UAVCAN_PROTOCOL_RESTARTNODE_RESPONSE_ID 5

#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
class uavcan_protocol_RestartNode_cxx_iface;
#endif

struct uavcan_protocol_RestartNodeResponse {
#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
    using cxx_iface = uavcan_protocol_RestartNode_cxx_iface;
#endif
    bool ok; // 操作是否成功
};

#ifdef __cplusplus
extern "C"
{
#endif

uint32_t uavcan_protocol_RestartNodeResponse_encode(struct uavcan_protocol_RestartNodeResponse* msg, uint8_t* buffer
#if CANARD_ENABLE_TAO_OPTION
    , bool tao
#endif
);
bool uavcan_protocol_RestartNodeResponse_decode(const CanardRxTransfer* transfer, struct uavcan_protocol_RestartNodeResponse* msg);

#if defined(CANARD_DSDLC_INTERNAL)
static inline void _uavcan_protocol_RestartNodeResponse_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_protocol_RestartNodeResponse* msg, bool tao);
static inline bool _uavcan_protocol_RestartNodeResponse_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_protocol_RestartNodeResponse* msg, bool tao);
/** 中文说明：将本类型结构序列化为协议位流；外层encode返回字节数，带前导下划线的内部入口推进bit_ofs，供嵌套类型复用。 */
void _uavcan_protocol_RestartNodeResponse_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_protocol_RestartNodeResponse* msg, bool tao) {
    (void)buffer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;

    canardEncodeScalar(buffer, *bit_ofs, 1, &msg->ok);
    *bit_ofs += 1;
}

/*
 decode uavcan_protocol_RestartNodeResponse, return true on failure, false on success
*/
/** 中文说明：按DSDL字段位宽反序列化；返回true表示失败、false表示成功；内部入口推进bit_ofs，外层还核对载荷长度。 */
bool _uavcan_protocol_RestartNodeResponse_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_protocol_RestartNodeResponse* msg, bool tao) {
    (void)transfer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;
    canardDecodeScalar(transfer, *bit_ofs, 1, false, &msg->ok);
    *bit_ofs += 1;

    return false; /* success */
}
#endif
#ifdef CANARD_DSDLC_TEST_BUILD
struct uavcan_protocol_RestartNodeResponse sample_uavcan_protocol_RestartNodeResponse_msg(void);
#endif
#ifdef __cplusplus
} // extern "C"

#ifdef DRONECAN_CXX_WRAPPERS
#include <canard/cxx_wrappers.h>
#endif
#endif
