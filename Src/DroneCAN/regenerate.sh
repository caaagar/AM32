#!/bin/bash
# 中文导读：从上游DSDL重新生成本项目使用的协议C接口。必须在仓库根目录执行。
# 此脚本会删除tmp临时目录及现有dsdl_generated目录并重新复制；手工中文注释也会被覆盖。
# regenerate the C API from DSDL

[ -d Src/DroneCAN ] || {
    echo "Must be run from top level of AM32 source tree"
    exit 1
}

# 下载协议定义与生成器到临时工作目录。
download() {
    /bin/rm -rf tmp
    mkdir -p tmp

    echo "Cloning DSDL"
    git clone --depth 1 https://github.com/DroneCAN/DSDL tmp/DSDL

    echo "Cloning dronecan_dsdlc"
    git clone --depth 1 https://github.com/DroneCAN/dronecan_dsdlc tmp/dronecan_dsdlc
}

# 调用生成器，再由下方MSGS列表筛选本项目保留的消息族。
generate() {
    echo "Running generator"
    python3 tmp/dronecan_dsdlc/dronecan_dsdlc.py -O tmp/dsdl_generated tmp/DSDL/dronecan tmp/DSDL/uavcan tmp/DSDL/com tmp/DSDL/ardupilot
}

download
generate

# list of messages which we need to support, wildcards are added to get the sub-messages
MSGS="uavcan.protocol.NodeStatus uavcan.protocol.HardwareVersion uavcan.protocol.SoftwareVersion uavcan.protocol.GetNodeInfo uavcan.equipment.esc uavcan.protocol.dynamic_node_id uavcan.protocol.param uavcan.protocol.file uavcan.protocol.RestartNode uavcan.protocol.RestartNode uavcan.protocol.debug uavcan.equipment.safety.ArmingStatus dronecan.protocol.FlexDebug"

rm -rf Src/DroneCAN/dsdl_generated
mkdir -p Src/DroneCAN/dsdl_generated/src
mkdir -p Src/DroneCAN/dsdl_generated/include

for m in $MSGS; do
    echo "Copying $m"
    cp tmp/dsdl_generated/src/$m* Src/DroneCAN/dsdl_generated/src/
    cp tmp/dsdl_generated/include/$m* Src/DroneCAN/dsdl_generated/include/
done

echo "#pragma once" > Src/DroneCAN/dsdl_generated/dronecan_msgs.h
for f in $(/bin/ls Src/DroneCAN/dsdl_generated/include); do
    echo "#include \"$f\"" >> Src/DroneCAN/dsdl_generated/dronecan_msgs.h
done

rm -rf tmp
