#!/usr/bin/env python3
'''
set application signature in bin and elf files
'''

import struct
import sys

APP_SIGNATURE_MAGIC1 = 0x68f058e6
APP_SIGNATURE_MAGIC2 = 0xafcee5a0

# 按原实现逐位计算CRC32，初值为0且不额外取反，须与引导程序校验算法一致。
def crc32(buf):
    '''crc32 implementation'''
    crc = 0
    size = len(buf)
    for i in range(size):
        byte = buf[i]
        crc ^= byte
        for _ in range(8):
            mask = -(crc & 1)
            crc >>= 1
            crc ^= (0xEDB88320 & mask)
    return crc

# Example usage:
# buf = bytearray([0x31, 0x32, 0x33, 0x34])  # Sample input
# result = crc32(buf, len(buf))
# print(f"CRC32: {hex(result)}")

# 找到双魔数描述符，分别计算描述符前后两段CRC，并同步回填BIN和ELF中的镜像长度/校验字段。
def set_app_descriptor(bin_file, elf_file):
    '''setup app descriptor in bin file and elf file'''
    descriptor = struct.pack("<II", APP_SIGNATURE_MAGIC1, APP_SIGNATURE_MAGIC2);
    img = open(bin_file, 'rb').read()
    len1 = len(img)
    offset = img.find(descriptor)
    if offset == -1:
        print("No APP_DESCRIPTOR found in %s" % bin_file)
        sys.exit(1)

    # full descriptor length
    # 44字节须与固件中的app_signature布局一致，描述符本身不参与两段CRC。
    desc_len = 44

    img1 = bytearray(img[:offset])
    img2 = bytearray(img[offset+desc_len:])
    crc1 = crc32(img1)
    crc2 = crc32(img2)

    desc = struct.pack('<III', len(img), crc1, crc2)
    img = img[:offset+len(descriptor)] + desc + img[offset+len(descriptor)+len(desc):]
    if len(img) != len1:
        print("Bad app descriptor size", len1, len(img))
        sys.exit(1)
    open(bin_file, 'wb').write(img)

    elf_img = open(elf_file,'rb').read()
    elf_ofs = elf_img.find(descriptor)
    if elf_ofs == -1:
        print("No APP_DESCRIPTOR found in elf file")
        sys.exit(1)
    elf_ofs += len(descriptor)
    elf_img = elf_img[:elf_ofs] + desc + elf_img[elf_ofs+len(desc):]
    open(elf_file, 'wb').write(elf_img)
    print("Applied APP_DESCRIPTOR %08x%08x for %s" % (crc1, crc2, bin_file))

# 命令行只处理名称含_CAN_的固件；此工具会原地修改传入的两个产物文件。
from argparse import ArgumentParser
parser = ArgumentParser(description="AM32 set application signature")

parser.add_argument("binfile", type=str, help="application bin file")
parser.add_argument("elffile", type=str, help="application elf file")

args = parser.parse_args()

# only apply to CAN firmwares for now
if args.binfile.find("_CAN_") == -1:
    sys.exit(0)

if not args.binfile.endswith(".bin"):
    print("Invalid bin file %s" % args.binfile)
    sys.exit(1)

if not args.elffile.endswith(".elf"):
    print("Invalid elf file %s" % args.elffile)
    sys.exit(1)
    
set_app_descriptor(args.binfile, args.elffile)
