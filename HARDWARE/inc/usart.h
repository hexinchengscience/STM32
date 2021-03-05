#ifndef _USART_H_
#define _USART_H_

#include "DataType.h"
#include "Cortex-M3.h"
#include "STM32F103.h"
#include "system.h"
#include "gpio.h"

#define defRxOverTime  5                     //! ���ճ�ʱʱ�� ms
#define BufferLength   512                   //! �������ݳ���
#define USART_RenewalPointer(p) p = (p + 1) % BufferLength  //! ���´���ָ��

#define USART1_BaudRate  BaudRate115200      //! ����1������115200
#define USART2_BaudRate  BaudRate115200      //! ����2������115200
#define USART3_BaudRate  BaudRate115200      //! ����3������115200

/*********************���ڴ���ṹ��****************************************************/
typedef struct 
{
    u16 RxHead ;                   //! �������ݽ���ͷ
	  u16 RxTail ;                   //! �������ݽ���β
	  u16 TxHead ;                   //! �������ݷ���ͷ
	  u16 TxTail ;                   //! �������ݷ���β
	
	  u8 RxBuffer[BufferLength] ;    //! �������ݽ��ջ�����
	  u8 TxBuffer[BufferLength] ;    //! �������ݷ��ͻ�����
	
    u8 TxFlag:1 ;                  //! ���ͱ�־    
	  u8 TxEnd:1 ;                   //! ���ͽ���  
	  u8 RxFlag:1 ;                  //! ���ձ�־   
		u8 RxTime:5 ;                  //! ���ճ�ʱʱ��                             
}UsartDataTypeDef ;

/**
 * @brief   ͨ�ô���Э�鴦����
 * @note    �����߼����£�
 *          1�������жϽ���ʱ���Ƿ�ʱ��
 *          2���ж�����֡ͷ�Ƿ���ȷ���������ȷ������ָ��+1
 *          3���ж����ݳ����Ƿ񹻣����������ֱ���ӵ���ǰ��������
 *          4����ȡ���ݣ�����һ��ָ�������
 *          5���ж��Ƿ��ж�������û�д������У��ظ�����Ĳ��衣
 *
 * @note    5A A5 len dat1 dat2 .......
**/ 
#define UsartRxBuffer_Deal(USART) void USART##_Read_RxBuffer(void)                                    \
{                                                                                                     \
	  if(USART##Usart.RxFlag && USART##Usart.RxTime > defRxOverTime)                                    \
		{                                                                                                 \
			  u8 i ; USART##Usart.RxFlag = 0 ;  /*! �����״̬λ     */                                     \
			  if(USART##Usart.RxHead == USART##Usart.RxTail) return ; /*! ͷβ��Ȳ�����*/                  \
				Read_RxBuffer_Start:              /*! �ж�֡ͷ�Ƿ���ȷ */                                     \
				if(USART##Usart.RxBuffer[USART##Usart.RxHead] == Frame_H && USART##Usart.RxBuffer[(USART##Usart.RxHead + 1) % BufferLength] == Frame_L)\
				{                                                                                             \
					  /*! �ж����ݳ����Ƿ�                                                              */    \
					  u8 length = (USART##Usart.RxBuffer[(USART##Usart.RxHead + 2) % BufferLength] + 3) ;       \
				    if((USART##Usart.RxTail - USART##Usart.RxHead + BufferLength) % BufferLength >= length)   \
						{                                                                                         \
						    for(i = 0 ; i < length ; ++ i)               /*! ���洮������                   */    \
							  {                                                                                     \
								    USART##RxBuffer[i] = USART##Usart.RxBuffer[USART##Usart.RxHead] ;                 \
									  USART_RenewalPointer(USART##Usart.RxHead) ;                                       \
								}                                                                                     \
								USART##_RxBuffer_Deal() ;                    /*! �������ݴ���*/                       \
								if(USART##Usart.RxFlag) return ;             /*! �����յ����ݣ��˳��ȴ�������� */    \
								if(USART##Usart.RxHead != USART##Usart.RxTail) goto Read_RxBuffer_Start ;             \
						}                                                                                         \
						else USART##Usart.RxHead = USART##Usart.RxTail ; /*! ����ָ��                       */    \
				}                                                                                             \
				else if((USART##Usart.RxHead + 1) % BufferLength != USART##Usart.RxTail)                      \
				{                                                                                             \
					  USART_RenewalPointer(USART##Usart.RxHead) ;                                               \
					  goto Read_RxBuffer_Start ;                       /*! ����ָ������ж�               */    \
				}                                                                                             \
				else USART##Usart.RxHead = USART##Usart.RxTail ;     /*! ����ָ��                       */    \
		}                                                                                                 \
}

extern UsartDataTypeDef Usart1 , Usart2 , Usart3 ;    //! ���崮�����ݽṹ��

void USART1_Init(void) ;                     //! ����1��ʼ��
void USART2_Init(void) ;                     //! ����2��ʼ��
void USART3_Init(void) ;                     //! ����3��ʼ��
void USART1_Send_N_Byte(u8 *byte , int len); //! ����1����N���ֽ�����
void USART2_Send_N_Byte(u8 *byte , int len); //! ����2����N���ֽ�����
void USART3_Send_N_Byte(u8 *byte , int len); //! ����3����N���ֽ�����
void USART1_RxBufferDeal(void);              //! ����1�жϴ����� ������
void USART2_RxBufferDeal(void);              //! ����2�жϴ����� ������
void USART3_RxBufferDeal(void);              //! ����3�жϴ����� ������

#endif //! _USART_H_

