/****************************************************************************************
* 文件名称: uart.c
* 
* 创建时间：2019/11/27
*
* 修改时间：2019/12/19
*
* 作    者：science
*
* 版    本：V1.2
*
* 文摘描述：STM32F103 串口函数
*
* 说    明：20191128 : 串口发送中断配置好后会自动进入一次中断，原因未知，影响不大，待解决
*           20191219 : 重新整理串口初始化，发送函数
*           20210105 : 整理串口函数
*           20210225 : 串口发送函数，当数据发送数组满之后，会出现串口死机情况，增加等待判断解决问题，会增加等待时间
****************************************************************************************/ 
#include "usart.h"

UsartDataTypeDef Usart1 ;             //! 定义串口1数据结构体
UsartDataTypeDef Usart2 ;             //! 定义串口2数据结构体
UsartDataTypeDef Usart3 ;             //! 定义串口3数据结构体

/**
 * @brief  串口1初始化
 **/
#define USART_Init(USART , Usart)                                \
    USART -> BRR = USART##_BaudRate ;    /*! 设置波特率        */\
	  USART -> CR1 &= ~(1 << 6) ;          /*! 清发送中断使能    */\
	  USART -> CR1 |= 1 << 2 ;             /*! 接收使能          */\
	  USART -> CR1 |= 1 << 3 ;             /*! 发送使能          */\
	  USART -> CR1 |= 1 << 5 ;             /*! 接收中断          */\
	  USART -> CR1 |= 1 << 6 ;             /*! 发送中断          */\
	  USART -> CR1 |= 1 << 13 ;            /*! 串口使能          */\
	  USART -> SR &= ~(1 << 6) ;           /*! 清发送中断        */\
		Usart.RxHead = 0 ; Usart.RxTail = 0 ;/*! 设置初始值        */\
	  Usart.TxHead = 0 ; Usart.TxTail = 1 ;/*! 设置初始值        */\
	  Usart.TxFlag = 0 ; Usart.TxEnd  = 1 ;/*! 设置初始值        */\
		Usart.RxFlag = 0 ; Usart.RxTime = 6 ;/*! 设置初始值        */\
	  NVIC -> IP[USART##_IRQn] = 0x1F ;    /*! 设置中断优先级    */\
	  NVIC->ISER[USART##_IRQn >> 0x05] =(u32)0x01 << (USART##_IRQn & (u8)0x1F);

/**
 * @brief  串口1初始化
 **/
void USART1_Init(void)
{
    RCC -> APB2ENR |= 1<< 14 ;                //! 使能串口1时钟    
	  RCC -> APB2ENR |= 1 << 2 ;                //! 打开A口时钟
	
	  GPIO_Init(GPIOA , 9 , GPIO_Mode_AF_OD) ;  //! PA9  TX 推挽输出
	  GPIO_Init(GPIOA , 10 , GPIO_Mode_IPD) ;   //! PA10 RX 上拉输入
	  
	  RCC -> APB2RSTR |= 1 << 14 ;              //! 复位串口1   
	  RCC -> APB2RSTR &= ~( 1 << 14);           //! 停止复位	  
	
	  USART_Init(USART1 , Usart1) ;             //! 串口初始化
}

/**
 * @brief  串口2初始化
 **/
void USART2_Init(void)
{
    RCC -> APB1ENR |= 1<< 17 ;                //! 使能串口1时钟    
	  RCC -> APB2ENR |= 1 << 2 ;                //! 打开A口时钟
	
	  GPIO_Init(GPIOA , 2 , GPIO_Mode_AF_OD) ;  //! PA2  TX 推挽输出
	  GPIO_Init(GPIOA , 3 , GPIO_Mode_IPD) ;    //! PA3  RX 上拉输入
	  
	  RCC -> APB1RSTR |= 1 << 17 ;              //! 复位串口2
	  RCC -> APB1RSTR &= ~( 1 << 17);           //! 停止复位	  
	
	  USART_Init(USART2 , Usart2) ;             //! 串口初始化 
}

/**
 * @brief  串口3初始化
 **/
void USART3_Init(void)
{
    RCC -> APB1ENR |= 1 << 18;                //! 使能串口3时钟   
	  RCC -> APB2ENR |= 1 << 3 ;                //! 打开B口时钟
	
	  GPIO_Init(GPIOB , 10 , GPIO_Mode_AF_OD) ; //! PB10 TX 推挽输出
	  GPIO_Init(GPIOB , 11 , GPIO_Mode_IPD) ;   //! PB11 RX 上拉输入
	
	  RCC -> APB1RSTR |= 1 << 18 ;              //! 复位串口3       
	  RCC -> APB1RSTR &= ~(1 << 18) ;           //! 停止复位	      
	
	  USART_Init(USART3 , Usart3) ;             //! 串口初始化
}

/**
 * @brief  串口1发送N个字节数据
 * @param  Usart: 串口结构体
 *         byte : 需要发送的数据
 *         len  : 数据长度 
 *
 * @note   串口发送函数，当数据发送数组满之后，会出现串口死机情况
 *         增加等待判断 while(Usart.TxTail == Usart.TxHead) 解决问题，会增加等待时间
 *         在while循环中还可以加上 Usart.TxFlag = 1 ; 语句，预防第一次调用函数就超数组
 *         一般情况不允许这种情况，这个地方没有加。
 **/
#define USART_Send_N_Byte(Usart , byte , len)      \
{                                                  \
	  for(int i = 0 ; i < len ; ++ i)                \
	  {                                              \
		    Usart.TxBuffer[Usart.TxTail] = byte[i] ;   \
			  USART_RenewalPointer(Usart.TxTail) ;       \
			  while(Usart.TxTail == Usart.TxHead) ;      \
		}                                              \
		Usart.TxFlag = 1 ;                             \
}

/**
 * @brief  串口1发送N个字节数据
 * @param  byte : 需要发送的数据
 *         len  : 数据长度 
 **/
void USART1_Send_N_Byte(u8 *byte , int len)
{
	  USART_Send_N_Byte(Usart1 , byte , len);
}

/**
 * @brief  串口2发送N个字节数据
 * @param  byte : 需要发送的数据
 *         len  : 数据长度 
 **/
void USART2_Send_N_Byte(u8 *byte , int len)
{
	  USART_Send_N_Byte(Usart2 , byte , len);
}

/**
 * @brief  串口3发送N个字节数据
 * @param  byte : 需要发送的数据
 *         len  : 数据长度 
 **/
void USART3_Send_N_Byte(u8 *byte , int len)
{ 
	  USART_Send_N_Byte(Usart3 , byte , len);
}

/**
 * @brief  串口1中断处理函数 ，测试使用
 **/
#define USART_RxBufferDeal(USART , Usart)                \
{                                                        \
	  u8 RxBuffer[128] ;                                   \
    if(Usart.RxFlag && Usart.RxTime > defRxOverTime)     \
		{                                                    \
		    int i = 0 ;                                      \
			  Usart.RxFlag = 0 ;                               \
			  for( ; Usart.RxHead != Usart.RxTail ; ++ i)      \
			  {                                                \
				    RxBuffer[i] = Usart.RxBuffer[Usart.RxHead] ; \
					  USART_RenewalPointer(Usart.RxHead) ;         \
				}                                                \
				USART##_Send_N_Byte(RxBuffer , i) ;              \
		}                                                    \
}

/**
 * @brief  串口1中断处理函数 ，测试使用
 **/
void USART1_RxBufferDeal(void)
{
	  USART_RxBufferDeal(USART1 , Usart1) ;
}

/**
 * @brief  串口2中断处理函数 ，测试使用
 **/
void USART2_RxBufferDeal(void)
{
	  USART_RxBufferDeal(USART2 , Usart2) ;
}

/**
 * @brief  串口3中断处理函数 ，测试使用
 **/
void USART3_RxBufferDeal(void)
{
	  USART_RxBufferDeal(USART3 , Usart3) ;
}
