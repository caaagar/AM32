/*
 * 中文导读：DSDL生成协议代码：动态节点分配服务器的日志记录。
 * 编解码位宽、字段顺序、类型签名与ID共同决定兼容性。TAO表示尾数组优化；内部decode返回true表示失败。
 * 本文件的中文注释用于阅读，运行regenerate.sh重新生成时可能被覆盖；生成了类型不代表业务层已使用该功能。
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <canard.h>


#define UAVCAN_PROTOCOL_DYNAMIC_NODE_ID_SERVER_ENTRY_MAX_SIZE 21
#define UAVCAN_PROTOCOL_DYNAMIC_NODE_ID_SERVER_ENTRY_SIGNATURE (0x7FAA779D64FA75C2ULL)


struct uavcan_protocol_dynamic_node_id_server_Entry {
    uint32_t term; // 集群选举任期
    uint8_t unique_id[16]; // 硬件唯一ID字节序列
    uint8_t node_id; // CAN节点号
};

#ifdef __cplusplus
extern "C"
{
#endif

uint32_t uavcan_protocol_dynamic_node_id_server_Entry_encode(struct uavcan_protocol_dynamic_node_id_server_Entry* msg, uint8_t* buffer
#if CANARD_ENABLE_TAO_OPTION
    , bool tao
#endif
);
bool uavcan_protocol_dynamic_node_id_server_Entry_decode(const CanardRxTransfer* transfer, struct uavcan_protocol_dynamic_node_id_server_Entry* msg);

#if defined(CANARD_DSDLC_INTERNAL)
static inline void _uavcan_protocol_dynamic_node_id_server_Entry_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_protocol_dynamic_node_id_server_Entry* msg, bool tao);
static inline bool _uavcan_protocol_dynamic_node_id_server_Entry_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_protocol_dynamic_node_id_server_Entry* msg, bool tao);
/** 中文说明：将本类型结构序列化为协议位流；外层encode返回字节数，带前导下划线的内部入口推进bit_ofs，供嵌套类型复用。 */
void _uavcan_protocol_dynamic_node_id_server_Entry_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_protocol_dynamic_node_id_server_Entry* msg, bool tao) {
    (void)buffer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;

    canardEncodeScalar(buffer, *bit_ofs, 32, &msg->term);
    *bit_ofs += 32;
    for (size_t i=0; i < 16; i++) {
        canardEncodeScalar(buffer, *bit_ofs, 8, &msg->unique_id[i]);
        *bit_ofs += 8;
    }
    *bit_ofs += 1;
    canardEncodeScalar(buffer, *bit_ofs, 7, &msg->node_id);
    *bit_ofs += 7;
}

/*
 decode uavcan_protocol_dynamic_node_id_server_Entry, return true on failure, false on success
*/
/** 中文说明：按DSDL字段位宽反序列化；返回true表示失败、false表示成功；内部入口推进bit_ofs，外层还核对载荷长度。 */
bool _uavcan_protocol_dynamic_node_id_server_Entry_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_protocol_dynamic_node_id_server_Entry* msg, bool tao) {
    (void)transfer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;
    canardDecodeScalar(transfer, *bit_ofs, 32, false, &msg->term);
    *bit_ofs += 32;

    for (size_t i=0; i < 16; i++) {
        canardDecodeScalar(transfer, *bit_ofs, 8, false, &msg->unique_id[i]);
        *bit_ofs += 8;
    }

    *bit_ofs += 1;

    canardDecodeScalar(transfer, *bit_ofs, 7, false, &msg->node_id);
    *bit_ofs += 7;

    return false; /* success */
}
#endif
#ifdef CANARD_DSDLC_TEST_BUILD
struct uavcan_protocol_dynamic_node_id_server_Entry sample_uavcan_protocol_dynamic_node_id_server_Entry_msg(void);
#endif
#ifdef __cplusplus
} // extern "C"

#ifdef DRONECAN_CXX_WRAPPERS
#include <canard/cxx_wrappers.h>
#endif
#endif
