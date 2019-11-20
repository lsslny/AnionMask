#include "STM32_ChipID.h"



/*****************************************************
**函数功能：获取STM32芯片ID号
**参	数：ID号为96位12Byte长度，所以必须定义为数组元素为u32类型且长度大于3
**返回	值：0-----------获取成功
**			1-----------获取失败
******************************************************/
uint8_t Get_ChipID(uint32_t* CPU_ID)
{
//	u32 Dev_ID_Addr0,Dev_ID_Addr1,Dev_ID_Addr2;
	
	//获取芯片ID
	CPU_ID[0]=*(__IO uint32_t*)(0x1ffff7e8);
	CPU_ID[1]=*(__IO uint32_t*)(0x1ffff7ec);
	CPU_ID[2]=*(__IO uint32_t*)(0x1ffff7f0);
	
	if((CPU_ID[0] != 0)&&(CPU_ID[1] != 0)&&(CPU_ID[2] != 0))
		return 0;
	
	return 1;
}


/*****************************************************
**函数功能：蓝牙用户名随机算法
**算	法：Val = ((u8)CPU_ID[0]+(u8)CPU_ID[1]+(u8)CPU_ID[2])^0xFF
******************************************************/
uint32_t BLE_UserNum_Val(uint32_t* CPU_ID)
{
	uint32_t ret = 0;
	uint8_t i = 0;
	uint8_t buff[3] = {0};

	if(CPU_ID != (void*)0)
	{
		for(i = 0;i < 3;i++)
			buff[i] = (uint8_t)CPU_ID[i];
		
		for(i = 0;i < 3;i++)
			ret += buff[i];
		
		ret ^= 0xff;
	}
	
	return ret;
}

