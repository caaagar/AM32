/*
 * 中文导读：KISS串口遥测及电调信息包。多字节字段按高字节在前打包，末尾为CRC8；这里只准备数据，串口DMA发送由其他模块触发。
 */

#include "kiss_telemetry.h"
#include "eeprom.h"

extern uint8_t get_crc8(uint8_t* Buf, uint8_t BufLen);

uint8_t aTxBuffer[49] __attribute__((aligned(4)));
uint8_t nbDataToTransmit = sizeof(aTxBuffer);

/** 中文说明：打包KISS遥测：温度为摄氏度，电压/电流单位为0.01V/0.01A，容量为mAh，e_rpm参数以100电气转/分为单位；末尾写CRC8。 */
void makeTelemPackage(int8_t temp, uint16_t voltage, uint16_t current, uint16_t consumption, uint16_t e_rpm)
{
    kiss_telem_pkt_t* telem_pkt = (kiss_telem_pkt_t*)aTxBuffer;

    telem_pkt->temperature = temp; // temperature in Celcius

    // voltage in centivolts
    telem_pkt->voltage_h = (voltage >> 8) & 0xFF;
    telem_pkt->voltage_l = voltage & 0xFF;

    // current in centiamps
    telem_pkt->current_h = (current >> 8) & 0xFF;
    telem_pkt->current_l = current & 0xFF;

    // accumulated current consumption in mAH
    telem_pkt->consumption_h = (consumption >> 8) & 0xFF;
    telem_pkt->consumption_l = consumption & 0xFF;

    // eRPM * 100, so 1 in the packet means 100 eRPM
    telem_pkt->erpm_h = (e_rpm >> 8) & 0xFF;
    telem_pkt->erpm_l = e_rpm & 0xFF;

    telem_pkt->crc = get_crc8((uint8_t*)telem_pkt, sizeof(kiss_telem_pkt_t) - 1);
}

/** 中文说明：将设置缓冲区前48字节复制到信息包，再附加1字节CRC8，供配置端读取电调信息。 */
void makeInfoPacket()
{
    for(int i = 0; i < 48; i++) {
        aTxBuffer[i] = eepromBuffer.buffer[i];
    }
    aTxBuffer[48] = get_crc8(aTxBuffer, 48);
}
