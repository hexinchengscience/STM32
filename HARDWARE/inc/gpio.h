#ifndef _GPIO_H_
#define _GPIO_H_

#include "Cortex-M3.h"
#include "STM32F103.h"

/** 
  * @brief  Configuration Mode enumeration  
  */
typedef enum
{ 
	  GPIO_Mode_AIN         = 0x00,     //! ģ������ģʽ
    GPIO_Mode_IN_FLOATING = 0x04,     //! ��������
    GPIO_Mode_IPD         = 0x08,     //! ��������
    GPIO_Mode_IPU         = 0x08,     //! ��������
    GPIO_Mode_Out_OD      = 0x03,     //! ͨ���������
    GPIO_Mode_Out_PP      = 0x07,     //! ͨ�ÿ�©���
    GPIO_Mode_AF_OD       = 0x0B,     //! �����������
    GPIO_Mode_AF_PP       = 0x0F      //! ���ÿ�©���
}GPIOMode_TypeDef;

//! һЩ�������ų�ʼ��**********************************************************************************************************
#define defPBout3Init()       {RCC->APB2ENR |= 1 << 0 ; AFIO -> MAPR |= (1 << 8) ; GPIO_Init(GPIOB , 3 , GPIO_Mode_Out_OD) ; }  //! PB3�������

#define defPAout15Init()      {RCC->APB2ENR |= 1 << 0 ; AFIO -> MAPR |= (2 << 24) ; GPIO_Init(GPIOA , 15 , GPIO_Mode_Out_OD) ;} //! PA15�������

void GPIO_Init(GPIO_TypeDef * gpio , u8 pin , GPIOMode_TypeDef mode) ;  //! IO�ڳ�ʼ��

#endif //! _GPIO_H_
