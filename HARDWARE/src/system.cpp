/****************************************************************************************
* 文件名称: system.c
* 
* 创建时间：2019/11/27
*
* 修改时间：2019/12/09
*
* 作    者：何鑫成
*
* 版    本：V1.0
*
* 文摘描述：STM32F103 系统函数，中断分组  嘀嗒时钟函数
*
* 说    明：1，2019/11/27  建立简单的中断分组 ， 嘀嗒时钟
*           2，2019/12/09  修改系统时钟 改为36M
****************************************************************************************/ 
#include "system.h"

/**
 * @brief  断言错误处理
 **/
void Assert_Failed(u8* file, u32 line)
{ 
    //! 打印出错的文件名
    int len ; for(; ; ++ len) {if(file[len] =='\0') break ;}
    Assert_Send_N_Byte(file , len) ;
		
		//! 打印行号
		char chr[12] = "***********" ; 
		NumberToChar(line , chr) ; 
    Assert_Send_N_Byte((u8 *)"  Line:" , 7) ;
		Assert_Send_N_Byte((u8 *)chr , 12) ;
}

/**
 * @brief  系统时钟初始化  
 * @note   使用内部HSI/2作为PLL输入  PLL 9倍频 作为系统时钟
 **/
void System_Init(void)
{
#ifdef SYSCLK_FREQ_36MHz
	
	  RCC -> CFGR &= ~(0xF << 18) ;         //! 清PLLMUL数据
	  RCC -> CFGR |= 7 << 18 ;              //! PLL 9倍频
	
    RCC -> CFGR &= ~(1 << 16) ;           //! HSI作为PLL时钟输入
	  RCC -> CR |= 1 << 24 ;                //! PLL时钟使能
	  
	  FLASH ->ACR |= 0x31 ;                 //! FLASH 1个延时周期
	  while((RCC -> CR &(1 << 25)) == 0) ;  //! 等待PLL时钟锁定
	
	  RCC -> CFGR &= ~(3 << 0) ;            //! 清系统时钟选择
	  RCC -> CFGR |= 2 << 0 ;               //! PLL作为系统时钟
	
	  while((RCC -> CFGR & (0x08)) == 0) ;  //! 等待时钟锁定
	  
#endif
}

/**
 * @brief  系统软件复位
 **/
void System_Reset(void)
{
    u32 dat = SCB->AIRCR ; 
	  dat &= 0x0000FF00 ; 
	  dat |= 0x05FA0007 ;
    SCB->AIRCR = dat ;
}

/**
 * @brief  设置NVIC中断分组2:2位抢占优先级，2位响应优先级
 **/
void NVIC_Configuration(void)
{
	  SCB->AIRCR=0X05FA0500;  /* 设置中断优先级比，7:6  5:0 */
}

/**
 * @brief  SysTick定时器初始化
 * @note  0x00001F40  -> 8000  : 此系统时钟为8M，所以计数8000为1ms
 *        0x00008CA0  -> 36000  : 此系统时钟为36M，所以计数36000为1ms
 **/
void SysTick_Init(void)
{
#ifdef SYSCLK_FREQ_36MHz
	  SysTick->LOAD=36000 ;             /* 设定初值  T = 1ms   */
#else
	  SysTick->LOAD=8000;               /* 设定初值  T = 1ms   */
#endif
	  SysTick->CTRL|=0x00000007;        /* 开启定时器          */
	
	  SCB->SHP[11]=0X00;                /* 设置中断优先级      */
}

