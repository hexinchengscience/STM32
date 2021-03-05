/****************************************************************************************
* �ļ�����: uart.c
* 
* ����ʱ�䣺2019/11/27
*
* �޸�ʱ�䣺2019/12/19
*
* ��    �ߣ�science
*
* ��    ����V1.2
*
* ��ժ������STM32F103 ���ں���
*
* ˵    ����20191128 : ���ڷ����ж����úú���Զ�����һ���жϣ�ԭ��δ֪��Ӱ�첻�󣬴����
*           20191219 : ���������ڳ�ʼ�������ͺ���
*           20210105 : �����ں���
*           20210225 : ���ڷ��ͺ����������ݷ���������֮�󣬻���ִ���������������ӵȴ��жϽ�����⣬�����ӵȴ�ʱ��
****************************************************************************************/ 
#include "usart.h"

UsartDataTypeDef Usart1 ;             //! ���崮��1���ݽṹ��
UsartDataTypeDef Usart2 ;             //! ���崮��2���ݽṹ��
UsartDataTypeDef Usart3 ;             //! ���崮��3���ݽṹ��

/**
 * @brief  ����1��ʼ��
 **/
#define USART_Init(USART , Usart)                                \
    USART -> BRR = USART##_BaudRate ;    /*! ���ò�����        */\
	  USART -> CR1 &= ~(1 << 6) ;          /*! �巢���ж�ʹ��    */\
	  USART -> CR1 |= 1 << 2 ;             /*! ����ʹ��          */\
	  USART -> CR1 |= 1 << 3 ;             /*! ����ʹ��          */\
	  USART -> CR1 |= 1 << 5 ;             /*! �����ж�          */\
	  USART -> CR1 |= 1 << 6 ;             /*! �����ж�          */\
	  USART -> CR1 |= 1 << 13 ;            /*! ����ʹ��          */\
	  USART -> SR &= ~(1 << 6) ;           /*! �巢���ж�        */\
		Usart.RxHead = 0 ; Usart.RxTail = 0 ;/*! ���ó�ʼֵ        */\
	  Usart.TxHead = 0 ; Usart.TxTail = 1 ;/*! ���ó�ʼֵ        */\
	  Usart.TxFlag = 0 ; Usart.TxEnd  = 1 ;/*! ���ó�ʼֵ        */\
		Usart.RxFlag = 0 ; Usart.RxTime = 6 ;/*! ���ó�ʼֵ        */\
	  NVIC -> IP[USART##_IRQn] = 0x1F ;    /*! �����ж����ȼ�    */\
	  NVIC->ISER[USART##_IRQn >> 0x05] =(u32)0x01 << (USART##_IRQn & (u8)0x1F);

/**
 * @brief  ����1��ʼ��
 **/
void USART1_Init(void)
{
    RCC -> APB2ENR |= 1<< 14 ;                //! ʹ�ܴ���1ʱ��    
	  RCC -> APB2ENR |= 1 << 2 ;                //! ��A��ʱ��
	
	  GPIO_Init(GPIOA , 9 , GPIO_Mode_AF_OD) ;  //! PA9  TX �������
	  GPIO_Init(GPIOA , 10 , GPIO_Mode_IPD) ;   //! PA10 RX ��������
	  
	  RCC -> APB2RSTR |= 1 << 14 ;              //! ��λ����1   
	  RCC -> APB2RSTR &= ~( 1 << 14);           //! ֹͣ��λ	  
	
	  USART_Init(USART1 , Usart1) ;             //! ���ڳ�ʼ��
}

/**
 * @brief  ����2��ʼ��
 **/
void USART2_Init(void)
{
    RCC -> APB1ENR |= 1<< 17 ;                //! ʹ�ܴ���1ʱ��    
	  RCC -> APB2ENR |= 1 << 2 ;                //! ��A��ʱ��
	
	  GPIO_Init(GPIOA , 2 , GPIO_Mode_AF_OD) ;  //! PA2  TX �������
	  GPIO_Init(GPIOA , 3 , GPIO_Mode_IPD) ;    //! PA3  RX ��������
	  
	  RCC -> APB1RSTR |= 1 << 17 ;              //! ��λ����2
	  RCC -> APB1RSTR &= ~( 1 << 17);           //! ֹͣ��λ	  
	
	  USART_Init(USART2 , Usart2) ;             //! ���ڳ�ʼ�� 
}

/**
 * @brief  ����3��ʼ��
 **/
void USART3_Init(void)
{
    RCC -> APB1ENR |= 1 << 18;                //! ʹ�ܴ���3ʱ��   
	  RCC -> APB2ENR |= 1 << 3 ;                //! ��B��ʱ��
	
	  GPIO_Init(GPIOB , 10 , GPIO_Mode_AF_OD) ; //! PB10 TX �������
	  GPIO_Init(GPIOB , 11 , GPIO_Mode_IPD) ;   //! PB11 RX ��������
	
	  RCC -> APB1RSTR |= 1 << 18 ;              //! ��λ����3       
	  RCC -> APB1RSTR &= ~(1 << 18) ;           //! ֹͣ��λ	      
	
	  USART_Init(USART3 , Usart3) ;             //! ���ڳ�ʼ��
}

/**
 * @brief  ����1����N���ֽ�����
 * @param  Usart: ���ڽṹ��
 *         byte : ��Ҫ���͵�����
 *         len  : ���ݳ��� 
 *
 * @note   ���ڷ��ͺ����������ݷ���������֮�󣬻���ִ����������
 *         ���ӵȴ��ж� while(Usart.TxTail == Usart.TxHead) ������⣬�����ӵȴ�ʱ��
 *         ��whileѭ���л����Լ��� Usart.TxFlag = 1 ; ��䣬Ԥ����һ�ε��ú����ͳ�����
 *         һ������������������������ط�û�мӡ�
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
 * @brief  ����1����N���ֽ�����
 * @param  byte : ��Ҫ���͵�����
 *         len  : ���ݳ��� 
 **/
void USART1_Send_N_Byte(u8 *byte , int len)
{
	  USART_Send_N_Byte(Usart1 , byte , len);
}

/**
 * @brief  ����2����N���ֽ�����
 * @param  byte : ��Ҫ���͵�����
 *         len  : ���ݳ��� 
 **/
void USART2_Send_N_Byte(u8 *byte , int len)
{
	  USART_Send_N_Byte(Usart2 , byte , len);
}

/**
 * @brief  ����3����N���ֽ�����
 * @param  byte : ��Ҫ���͵�����
 *         len  : ���ݳ��� 
 **/
void USART3_Send_N_Byte(u8 *byte , int len)
{ 
	  USART_Send_N_Byte(Usart3 , byte , len);
}

/**
 * @brief  ����1�жϴ����� ������ʹ��
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
 * @brief  ����1�жϴ����� ������ʹ��
 **/
void USART1_RxBufferDeal(void)
{
	  USART_RxBufferDeal(USART1 , Usart1) ;
}

/**
 * @brief  ����2�жϴ����� ������ʹ��
 **/
void USART2_RxBufferDeal(void)
{
	  USART_RxBufferDeal(USART2 , Usart2) ;
}

/**
 * @brief  ����3�жϴ����� ������ʹ��
 **/
void USART3_RxBufferDeal(void)
{
	  USART_RxBufferDeal(USART3 , Usart3) ;
}
