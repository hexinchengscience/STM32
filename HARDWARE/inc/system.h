#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "DataType.h"

#include "Cortex-M3.h"
#include "STM32F103.h"
#include "usart.h"
#include "arithmetic.h" 

//! 断言处理---------------------------------------------------------------------------------------
#define USE_FULL_ASSERT    1   //! 是否使用断言，如果不使用，注释掉这行代码
#define Assert_Send_N_Byte   USART1_Send_N_Byte
#ifdef  USE_FULL_ASSERT
  #define Assert_Param(expr) ((expr) ? (void)0 : assert_failed((u8 *)__FILE__, __LINE__))
  void Assert_Failed(u8* file, u32 line) ;   //! 断言错误处理，一般打印文件名和行号
#else
  #define Assert_Param(expr) ((void)0)       //! 这里使用大写为了和一些库的断言进行区分
#endif  //! USE_FULL_ASSERT 
//!------------------------------------------------------------------------------------------------

#define SYSCLK_FREQ_36MHz 36000000           //! 是否使用系统时钟36M，屏蔽时系统时钟为8M

#define SysclkFrequency  SYSCLK_FREQ_36MHz   //! 定义系统时钟

//! 定义串口波特率
#define BaudRate9600    SysclkFrequency / 9600
#define BaudRate115200  SysclkFrequency / 115200

#define NVIC_Set_IRQn(IRQn,Priority) NVIC->IP[IRQn]=Priority;NVIC->ISER[IRQn>>0x05]=(u32)0x01<<(IRQn&(u8)0x1F);

extern u32 SystemHeartbeatCount ;   //! 系统心跳时钟
extern u16 MicroElectricCount ;

void System_Init(void) ;            //! 系统时钟初始化
void System_Reset(void) ;           //! 系统软件复位
void NVIC_Configuration(void) ;     //! 设置NVIC中断分组
void SysTick_Init(void) ;           //! SysTick定时器初始化


#endif //! _SYSTEM_H_

