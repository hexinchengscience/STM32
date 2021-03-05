#ifndef _FLASH_H_
#define _FLASH_H_

#include "DataType.h"
#include "Cortex-M3.h"
#include "STM32F103.h"

//! FLASH������ֵ
#define FLASH_KEY1               0X45670123
#define FLASH_KEY2               0XCDEF89AB

void FLASH_Read_N_Byte(u32 addr , u8 * byte , u16 len) ;   //! FLASH ��
void FLASH_Write_N_Byte(u32 addr , u8 * byte , u16 len) ;  //! FLASH д

#endif //! _FLASH_H_

