/*
 * 中文导读：libcanard内部辅助接口：池内索引、会话、队列、位拷贝与CRC。属于协议栈实现细节，应用层应优先使用canard.h。
 */

/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016-2017 UAVCAN Team
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Contributors: https://github.com/UAVCAN/libcanard/contributors
 */

/*
 * This file holds function declarations that expose the library's internal definitions for unit testing.
 * It is NOT part of the library's API and should not even be looked at by the user.
 */

#ifndef CANARD_INTERNALS_H
#define CANARD_INTERNALS_H

#include "canard.h"

#ifdef __cplusplus
extern "C" {
#endif

/// This macro is needed only for testing and development. Do not redefine this in production.
#ifndef CANARD_INTERNAL
# define CANARD_INTERNAL static
#endif

/*
 * Some MCUs like TMS320 have 16-bits addressing, so
 * 1.   (uint8_t) same (uint16_t)
 * 2.   sizeof(float) is 2
 * 3.   union not same like STM32, because type uint8_t does not exist in hardware
 *
 *      union
 *      {
 *          uint64_t u8;
 *          uint64_t u16;
 *          uint64_t u32;
 *          uint64_t u64;
 *          uint8_t bytes[8];
 *      } storage;
 *
 *      address:|   bytes:      |   u64:            |   u32:            |   u16:    |   u8:
 *      0x00    |   bytes[0]    |   (u64    )&0xFF  |   (u32    )&0xFF  |   u16     |   u8
 *      0x01    |   bytes[1]    |   (u64>>16)&0xFF  |   (u32>>16)&0xFF  |
 *      0x02    |   bytes[2]    |   (u64>>32)&0xFF  |
 *      0x03    |   bytes[3]    |   (u64>>48)&0xFF  |
 *      0x04    |   bytes[4]    |
 *      0x05    |   bytes[5]    |
 *      0x06    |   bytes[6]    |
 *      0x07    |   bytes[7]    |
 *
 */
#ifndef WORD_ADDRESSING_IS_16BITS
#if defined(__TI_COMPILER_VERSION__) || defined(__TMS320C2000__)
#define WORD_ADDRESSING_IS_16BITS 1
#else
#define WORD_ADDRESSING_IS_16BITS 0
#endif
#endif

#if WORD_ADDRESSING_IS_16BITS
# define uint8_t               uint16_t
# define int8_t                int16_t
# define CANARD_SIZEOF_FLOAT   2
#else
# define CANARD_SIZEOF_FLOAT   4
#endif

/** 中文接口：遍历接收状态链表查找指定传输描述，按实现调整命中状态位置。 */
CANARD_INTERNAL CanardRxState* traverseRxStates(CanardInstance* ins,
                                                uint32_t transfer_descriptor);

/** 中文接口：从池中分配接收会话状态并初始化其传输描述。 */
CANARD_INTERNAL CanardRxState* createRxState(CanardPoolAllocator* allocator,
                                             uint32_t transfer_descriptor);

/** 中文接口：创建接收状态并将其插入实例的接收状态链表头部。 */
CANARD_INTERNAL CanardRxState* prependRxState(CanardInstance* ins,
                                              uint32_t transfer_descriptor);

/** 中文接口：按传输描述查找已有接收会话，不创建新状态。 */
CANARD_INTERNAL CanardRxState* findRxState(CanardInstance *ins,
                                           uint32_t transfer_descriptor);

/** 中文接口：把新载荷追加到接收状态的缓冲链，空间不足时从池中申请新块。 */
CANARD_INTERNAL int16_t bufferBlockPushBytes(CanardPoolAllocator* allocator,
                                             CanardRxState* state,
                                             const uint8_t* data,
                                             uint8_t data_len);

/** 中文接口：从池中创建并初始化一个载荷缓冲块。 */
CANARD_INTERNAL CanardBufferBlock* createBufferBlock(CanardPoolAllocator* allocator);

/** 中文接口：按CAN仲裁优先级将新帧插入发送链表，维持队首优先发送。 */
CANARD_INTERNAL void pushTxQueue(CanardInstance* ins,
                                 CanardTxQueueItem* item);

/** 中文接口：比较CAN标识符对应的仲裁优先级，考虑标准/扩展帧等标志。 */
CANARD_INTERNAL bool isPriorityHigher(uint32_t id,
                                      uint32_t rhs);

/** 中文接口：从固定块内存池分配并初始化一个发送队列项；失败返回空指针。 */
CANARD_INTERNAL CanardTxQueueItem* createTxItem(CanardPoolAllocator* allocator);

/** 中文接口：清理当前接收状态的载荷进度，为同一会话下一次传输做好准备。 */
CANARD_INTERNAL void prepareForNextTransfer(CanardRxState* state);

/** 中文接口：计算循环transfer_id空间中的前向距离，用于判断重复、丢失及新传输。 */
CANARD_INTERNAL int16_t computeTransferIDForwardDistance(uint8_t a,
                                                         uint8_t b);

/** 中文接口：递增传输序号并按协议最大序号回绕。 */
CANARD_INTERNAL void incrementTransferID(uint8_t* transfer_id);

/** 中文接口：归还接收状态持有的载荷缓冲块，并清理载荷引用。 */
CANARD_INTERNAL uint64_t releaseStatePayload(CanardInstance* ins,
                                             CanardRxState* rxstate);

/** 中文接口：把CAN DLC编码转换成实际载荷字节数；CAN FD较大载荷不再与DLC数值相等。 */
CANARD_INTERNAL uint16_t dlcToDataLength(uint16_t dlc);
/** 中文接口：把载荷字节数转换为可容纳它的CAN DLC编码。 */
CANARD_INTERNAL uint16_t dataLengthToDlc(uint16_t data_length);

/// Returns the number of frames enqueued
/** 中文接口：把一次传输拆成CAN帧，附加CRC/尾字节并分配发送项；返回入队结果或内存错误。 */
CANARD_INTERNAL int16_t enqueueTxFrames(CanardInstance* ins,
                                        uint32_t can_id,
                                        uint16_t crc,
                                        CanardTxTransfer* transfer);

/** 中文接口：按源/目标比特偏移复制位串，处理非字节对齐的头尾。 */
CANARD_INTERNAL void copyBitArray(const uint8_t* src,
                                  uint32_t src_offset,
                                  uint32_t src_len,
                                  uint8_t* dst,
                                  uint32_t dst_offset);

/**
 * Moves specified bits from the scattered transfer storage to a specified contiguous buffer.
 * Returns the number of bits copied, or negated error code.
 */
/** 中文接口：从分散存储的接收载荷中读取连续比特到目标缓冲区。 */
CANARD_INTERNAL int16_t descatterTransferPayload(const CanardRxTransfer* transfer,
                                                 uint32_t bit_offset,
                                                 uint8_t bit_length,
                                                 void* output);

/** 中文接口：检测本机字节序，供协议标量转换时选择字节交换。 */
CANARD_INTERNAL bool isBigEndian(void);

/** 中文接口：原地反转指定长度数据的字节顺序。 */
CANARD_INTERNAL void swapByteOrder(void* data, unsigned size);

/*
 * Transfer CRC
 */
/** 中文接口：将一个字节加入传输CRC16累积值。 */
CANARD_INTERNAL uint16_t crcAddByte(uint16_t crc_val,
                                    uint8_t byte);

/** 中文接口：按协议顺序将64位数据类型签名纳入CRC16。 */
CANARD_INTERNAL uint16_t crcAddSignature(uint16_t crc_val,
                                         uint64_t data_type_signature);

/** 中文接口：把一段字节数据逐个加入CRC16。 */
CANARD_INTERNAL uint16_t crcAdd(uint16_t crc_val,
                                const uint8_t* bytes,
                                size_t len);

/**
 * Inits a memory allocator.
 *
 * @param [in] allocator The memory allocator to initialize.
 * @param [in] buf The buffer used by the memory allocator.
 * @param [in] buf_len The number of blocks in buf.
 */
/** 中文接口：将调用者提供的内存组织成固定大小空闲块链表，并初始化容量统计。 */
CANARD_INTERNAL void initPoolAllocator(CanardPoolAllocator* allocator,
                                       void *buf,
                                       uint16_t buf_len);

/**
 * Allocates a block from the given pool allocator.
 */
/** 中文接口：从空闲链表取出一个固定块并更新使用统计；池耗尽时返回空指针。 */
CANARD_INTERNAL void* allocateBlock(CanardPoolAllocator* allocator);

/**
 * Frees a memory block previously returned by canardAllocateBlock.
 */
/** 中文接口：将指定块归还空闲链表并更新统计，不是向操作系统释放堆内存。 */
CANARD_INTERNAL void freeBlock(CanardPoolAllocator* allocator,
                               void* p);

/** 中文接口：计算发送传输校验：将数据类型签名与载荷纳入CRC，供多帧传输完整性核对。 */
CANARD_INTERNAL uint16_t calculateCRC(const CanardTxTransfer* transfer_object);

/** 中文接口：将内存池块索引还原成缓冲块指针；用于节约内部链表指针存储。 */
CANARD_INTERNAL CanardBufferBlock *canardBufferFromIdx(CanardPoolAllocator* allocator, canard_buffer_idx_t idx);

/** 中文接口：将缓冲块地址换算成内存池索引，供内部紧凑链表引用。 */
CANARD_INTERNAL canard_buffer_idx_t canardBufferToIdx(CanardPoolAllocator* allocator, const CanardBufferBlock *buf);

/** 中文接口：将池内索引转换为接收会话状态指针。 */
CANARD_INTERNAL CanardRxState *canardRxFromIdx(CanardPoolAllocator* allocator, canard_buffer_idx_t idx);

/** 中文接口：将接收会话状态地址转换为池内索引。 */
CANARD_INTERNAL canard_buffer_idx_t canardRxToIdx(CanardPoolAllocator* allocator, const CanardRxState *rx);

#ifdef __cplusplus
}
#endif
#endif
