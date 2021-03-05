#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "DataType.h"

#include "Cortex-M3.h"
#include "STM32F103.h"
#include "usart.h"
#include "arithmetic.h" 

//! ���Դ���---------------------------------------------------------------------------------------
#define USE_FULL_ASSERT    1   //! �Ƿ�ʹ�ö��ԣ������ʹ�ã�ע�͵����д���
#define Assert_Send_N_Byte   USART1_Send_N_Byte
#ifdef  USE_FULL_ASSERT
  #define Assert_Param(expr) ((expr) ? (void)0 : assert_failed((u8 *)__FILE__, __LINE__))
  void Assert_Failed(u8* file, u32 line) ;   //! ���Դ�����һ���ӡ�ļ������к�
#else
  #define Assert_Param(expr) ((void)0)       //! ����ʹ�ô�дΪ�˺�һЩ��Ķ��Խ�������
#endif  //! USE_FULL_ASSERT 
//!------------------------------------------------------------------------------------------------

#define SYSCLK_FREQ_36MHz 36000000           //! �Ƿ�ʹ��ϵͳʱ��36M������ʱϵͳʱ��Ϊ8M

#define SysclkFrequency  SYSCLK_FREQ_36MHz   //! ����ϵͳʱ��

//! ���崮�ڲ�����
#define BaudRate9600    SysclkFrequency / 9600
#define BaudRate115200  SysclkFrequency / 115200

#define NVIC_Set_IRQn(IRQn,Priority) NVIC->IP[IRQn]=Priority;NVIC->ISER[IRQn>>0x05]=(u32)0x01<<(IRQn&(u8)0x1F);

extern u32 SystemHeartbeatCount ;   //! ϵͳ����ʱ��
extern u16 MicroElectricCount ;

void System_Init(void) ;            //! ϵͳʱ�ӳ�ʼ��
void System_Reset(void) ;           //! ϵͳ�����λ
void NVIC_Configuration(void) ;     //! ����NVIC�жϷ���
void SysTick_Init(void) ;           //! SysTick��ʱ����ʼ��


#endif //! _SYSTEM_H_

