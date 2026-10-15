/*
 * 中文导读：固件目标名称标识。used属性要求编译器保留此对象；名称来自targets.h的FILE_NAME，不是运行时计算的版本号。
 */

#include "firmwareversion.h"
#include "targets.h"

const char test[30] __attribute__((used)) = FILE_NAME;