/****************************************************************************************
* �ļ�����: system.c
* 
* ����ʱ�䣺2019/11/27
*
* �޸�ʱ�䣺2019/12/09
*
* ��    �ߣ����γ�
*
* ��    ����V1.0
*
* ��ժ������STM32F103 ϵͳ�������жϷ���  ���ʱ�Ӻ���
*
* ˵    ����1��2019/11/27  �����򵥵��жϷ��� �� ���ʱ��
*           2��2019/12/09  �޸�ϵͳʱ�� ��Ϊ36M
****************************************************************************************/ 
#include "system.h"

/**
 * @brief  ���Դ�����
 **/
void Assert_Failed(u8* file, u32 line)
{ 
    //! ��ӡ������ļ���
    int len ; for(; ; ++ len) {if(file[len] =='\0') break ;}
    Assert_Send_N_Byte(file , len) ;
		
		//! ��ӡ�к�
		char chr[12] = "***********" ; 
		NumberToChar(line , chr) ; 
    Assert_Send_N_Byte((u8 *)"  Line:" , 7) ;
		Assert_Send_N_Byte((u8 *)chr , 12) ;
}

/**
 * @brief  ϵͳʱ�ӳ�ʼ��  
 * @note   ʹ���ڲ�HSI/2��ΪPLL����  PLL 9��Ƶ ��Ϊϵͳʱ��
 **/
void System_Init(void)
{
#ifdef SYSCLK_FREQ_36MHz
	
	  RCC -> CFGR &= ~(0xF << 18) ;         //! ��PLLMUL����
	  RCC -> CFGR |= 7 << 18 ;              //! PLL 9��Ƶ
	
    RCC -> CFGR &= ~(1 << 16) ;           //! HSI��ΪPLLʱ������
	  RCC -> CR |= 1 << 24 ;                //! PLLʱ��ʹ��
	  
	  FLASH ->ACR |= 0x31 ;                 //! FLASH 1����ʱ����
	  while((RCC -> CR &(1 << 25)) == 0) ;  //! �ȴ�PLLʱ������
	
	  RCC -> CFGR &= ~(3 << 0) ;            //! ��ϵͳʱ��ѡ��
	  RCC -> CFGR |= 2 << 0 ;               //! PLL��Ϊϵͳʱ��
	
	  while((RCC -> CFGR & (0x08)) == 0) ;  //! �ȴ�ʱ������
	  
#endif
}

/**
 * @brief  ϵͳ�����λ
 **/
void System_Reset(void)
{
    u32 dat = SCB->AIRCR ; 
	  dat &= 0x0000FF00 ; 
	  dat |= 0x05FA0007 ;
    SCB->AIRCR = dat ;
}

/**
 * @brief  ����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
 **/
void NVIC_Configuration(void)
{
	  SCB->AIRCR=0X05FA0500;  /* �����ж����ȼ��ȣ�7:6  5:0 */
}

/**
 * @brief  SysTick��ʱ����ʼ��
 * @note  0x00001F40  -> 8000  : ��ϵͳʱ��Ϊ8M�����Լ���8000Ϊ1ms
 *        0x00008CA0  -> 36000  : ��ϵͳʱ��Ϊ36M�����Լ���36000Ϊ1ms
 **/
void SysTick_Init(void)
{
#ifdef SYSCLK_FREQ_36MHz
	  SysTick->LOAD=36000 ;             /* �趨��ֵ  T = 1ms   */
#else
	  SysTick->LOAD=8000;               /* �趨��ֵ  T = 1ms   */
#endif
	  SysTick->CTRL|=0x00000007;        /* ������ʱ��          */
	
	  SCB->SHP[11]=0X00;                /* �����ж����ȼ�      */
}

