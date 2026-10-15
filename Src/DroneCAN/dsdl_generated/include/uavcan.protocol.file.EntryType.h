/*
 * 中文导读：DSDL生成协议代码：远程文件系统条目的类型标志。
 * 编解码位宽、字段顺序、类型签名与ID共同决定兼容性。TAO表示尾数组优化；内部decode返回true表示失败。
 * 本文件的中文注释用于阅读，运行regenerate.sh重新生成时可能被覆盖；生成了类型不代表业务层已使用该功能。
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <canard.h>


#define UAVCAN_PROTOCOL_FILE_ENTRYTYPE_MAX_SIZE 1
#define UAVCAN_PROTOCOL_FILE_ENTRYTYPE_SIGNATURE (0x6924572FBB2086E5ULL)

#define UAVCAN_PROTOCOL_FILE_ENTRYTYPE_FLAG_FILE 1
#define UAVCAN_PROTOCOL_FILE_ENTRYTYPE_FLAG_DIRECTORY 2
#define UAVCAN_PROTOCOL_FILE_ENTRYTYPE_FLAG_SYMLINK 4
#define UAVCAN_PROTOCOL_FILE_ENTRYTYPE_FLAG_READABLE 8
#define UAVCAN_PROTOCOL_FILE_ENTRYTYPE_FLAG_WRITEABLE 16


struct uavcan_protocol_file_EntryType {
    uint8_t flags; // 协议定义的标志位集合
};

#ifdef __cplusplus
extern "C"
{
#endif

uint32_t uavcan_protocol_file_EntryType_encode(struct uavcan_protocol_file_EntryType* msg, uint8_t* buffer
#if CANARD_ENABLE_TAO_OPTION
    , bool tao
#endif
);
bool uavcan_protocol_file_EntryType_decode(const CanardRxTransfer* transfer, struct uavcan_protocol_file_EntryType* msg);

#if defined(CANARD_DSDLC_INTERNAL)
static inline void _uavcan_protocol_file_EntryType_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_protocol_file_EntryType* msg, bool tao);
static inline bool _uavcan_protocol_file_EntryType_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_protocol_file_EntryType* msg, bool tao);
/** 中文说明：将本类型结构序列化为协议位流；外层encode返回字节数，带前导下划线的内部入口推进bit_ofs，供嵌套类型复用。 */
void _uavcan_protocol_file_EntryType_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_protocol_file_EntryType* msg, bool tao) {
    (void)buffer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;

    canardEncodeScalar(buffer, *bit_ofs, 8, &msg->flags);
    *bit_ofs += 8;
}

/*
 decode uavcan_protocol_file_EntryType, return true on failure, false on success
*/
/** 中文说明：按DSDL字段位宽反序列化；返回true表示失败、false表示成功；内部入口推进bit_ofs，外层还核对载荷长度。 */
bool _uavcan_protocol_file_EntryType_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_protocol_file_EntryType* msg, bool tao) {
    (void)transfer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;
    canardDecodeScalar(transfer, *bit_ofs, 8, false, &msg->flags);
    *bit_ofs += 8;

    return false; /* success */
}
#endif
#ifdef CANARD_DSDLC_TEST_BUILD
struct uavcan_protocol_file_EntryType sample_uavcan_protocol_file_EntryType_msg(void);
#endif
#ifdef __cplusplus
} // extern "C"

#ifdef DRONECAN_CXX_WRAPPERS
#include <canard/cxx_wrappers.h>
#endif
#endif
