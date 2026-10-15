/*
 * 中文导读：DSDL生成协议代码：远程文件服务错误码。
 * 编解码位宽、字段顺序、类型签名与ID共同决定兼容性。TAO表示尾数组优化；内部decode返回true表示失败。
 * 本文件的中文注释用于阅读，运行regenerate.sh重新生成时可能被覆盖；生成了类型不代表业务层已使用该功能。
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <canard.h>


#define UAVCAN_PROTOCOL_FILE_ERROR_MAX_SIZE 2
#define UAVCAN_PROTOCOL_FILE_ERROR_SIGNATURE (0xA83071FFEA4FAE15ULL)

#define UAVCAN_PROTOCOL_FILE_ERROR_OK 0
#define UAVCAN_PROTOCOL_FILE_ERROR_UNKNOWN_ERROR 32767
#define UAVCAN_PROTOCOL_FILE_ERROR_NOT_FOUND 2
#define UAVCAN_PROTOCOL_FILE_ERROR_IO_ERROR 5
#define UAVCAN_PROTOCOL_FILE_ERROR_ACCESS_DENIED 13
#define UAVCAN_PROTOCOL_FILE_ERROR_IS_DIRECTORY 21
#define UAVCAN_PROTOCOL_FILE_ERROR_INVALID_VALUE 22
#define UAVCAN_PROTOCOL_FILE_ERROR_FILE_TOO_LARGE 27
#define UAVCAN_PROTOCOL_FILE_ERROR_OUT_OF_SPACE 28
#define UAVCAN_PROTOCOL_FILE_ERROR_NOT_IMPLEMENTED 38


struct uavcan_protocol_file_Error {
    int16_t value; // 类型承载的数值/枚举值
};

#ifdef __cplusplus
extern "C"
{
#endif

uint32_t uavcan_protocol_file_Error_encode(struct uavcan_protocol_file_Error* msg, uint8_t* buffer
#if CANARD_ENABLE_TAO_OPTION
    , bool tao
#endif
);
bool uavcan_protocol_file_Error_decode(const CanardRxTransfer* transfer, struct uavcan_protocol_file_Error* msg);

#if defined(CANARD_DSDLC_INTERNAL)
static inline void _uavcan_protocol_file_Error_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_protocol_file_Error* msg, bool tao);
static inline bool _uavcan_protocol_file_Error_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_protocol_file_Error* msg, bool tao);
/** 中文说明：将本类型结构序列化为协议位流；外层encode返回字节数，带前导下划线的内部入口推进bit_ofs，供嵌套类型复用。 */
void _uavcan_protocol_file_Error_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_protocol_file_Error* msg, bool tao) {
    (void)buffer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;

    canardEncodeScalar(buffer, *bit_ofs, 16, &msg->value);
    *bit_ofs += 16;
}

/*
 decode uavcan_protocol_file_Error, return true on failure, false on success
*/
/** 中文说明：按DSDL字段位宽反序列化；返回true表示失败、false表示成功；内部入口推进bit_ofs，外层还核对载荷长度。 */
bool _uavcan_protocol_file_Error_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_protocol_file_Error* msg, bool tao) {
    (void)transfer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;
    canardDecodeScalar(transfer, *bit_ofs, 16, true, &msg->value);
    *bit_ofs += 16;

    return false; /* success */
}
#endif
#ifdef CANARD_DSDLC_TEST_BUILD
struct uavcan_protocol_file_Error sample_uavcan_protocol_file_Error_msg(void);
#endif
#ifdef __cplusplus
} // extern "C"

#ifdef DRONECAN_CXX_WRAPPERS
#include <canard/cxx_wrappers.h>
#endif
#endif
