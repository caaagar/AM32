/*
 * 中文导读：DSDL生成协议代码：远程文件路径字节数组。
 * 编解码位宽、字段顺序、类型签名与ID共同决定兼容性。TAO表示尾数组优化；内部decode返回true表示失败。
 * 本文件的中文注释用于阅读，运行regenerate.sh重新生成时可能被覆盖；生成了类型不代表业务层已使用该功能。
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <canard.h>


#define UAVCAN_PROTOCOL_FILE_PATH_MAX_SIZE 201
#define UAVCAN_PROTOCOL_FILE_PATH_SIGNATURE (0x12AEFC50878A43E2ULL)

#define UAVCAN_PROTOCOL_FILE_PATH_SEPARATOR 47


struct uavcan_protocol_file_Path {
    struct { uint8_t len; uint8_t data[200]; }path;
};

#ifdef __cplusplus
extern "C"
{
#endif

uint32_t uavcan_protocol_file_Path_encode(struct uavcan_protocol_file_Path* msg, uint8_t* buffer
#if CANARD_ENABLE_TAO_OPTION
    , bool tao
#endif
);
bool uavcan_protocol_file_Path_decode(const CanardRxTransfer* transfer, struct uavcan_protocol_file_Path* msg);

#if defined(CANARD_DSDLC_INTERNAL)
static inline void _uavcan_protocol_file_Path_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_protocol_file_Path* msg, bool tao);
static inline bool _uavcan_protocol_file_Path_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_protocol_file_Path* msg, bool tao);
/** 中文说明：将本类型结构序列化为协议位流；外层encode返回字节数，带前导下划线的内部入口推进bit_ofs，供嵌套类型复用。 */
void _uavcan_protocol_file_Path_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_protocol_file_Path* msg, bool tao) {
    (void)buffer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
    const uint8_t path_len = msg->path.len > 200 ? 200 : msg->path.len;
#pragma GCC diagnostic pop
    if (!tao) {
        canardEncodeScalar(buffer, *bit_ofs, 8, &path_len);
        *bit_ofs += 8;
    }
    for (size_t i=0; i < path_len; i++) {
        canardEncodeScalar(buffer, *bit_ofs, 8, &msg->path.data[i]);
        *bit_ofs += 8;
    }
}

/*
 decode uavcan_protocol_file_Path, return true on failure, false on success
*/
/** 中文说明：按DSDL字段位宽反序列化；返回true表示失败、false表示成功；内部入口推进bit_ofs，外层还核对载荷长度。 */
bool _uavcan_protocol_file_Path_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_protocol_file_Path* msg, bool tao) {
    (void)transfer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;
    if (!tao) {
        canardDecodeScalar(transfer, *bit_ofs, 8, false, &msg->path.len);
        *bit_ofs += 8;
    } else {
        msg->path.len = ((transfer->payload_len*8)-*bit_ofs)/8;
    }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
    if (msg->path.len > 200) {
        return true; /* invalid value */
    }
#pragma GCC diagnostic pop
    for (size_t i=0; i < msg->path.len; i++) {
        canardDecodeScalar(transfer, *bit_ofs, 8, false, &msg->path.data[i]);
        *bit_ofs += 8;
    }

    return false; /* success */
}
#endif
#ifdef CANARD_DSDLC_TEST_BUILD
struct uavcan_protocol_file_Path sample_uavcan_protocol_file_Path_msg(void);
#endif
#ifdef __cplusplus
} // extern "C"

#ifdef DRONECAN_CXX_WRAPPERS
#include <canard/cxx_wrappers.h>
#endif
#endif
