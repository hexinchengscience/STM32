/****************************************************************************************
* �ļ�����: dma.cpp
* 
* ����ʱ�䣺2019/12/11
*
* �޸�ʱ�䣺2019/12/11
*
* ��    �ߣ����γ�
*
* ��    ����V1.0
*
* ��ժ������DMA��غ���
*
* ˵    ����
****************************************************************************************/ 
#include "dma.h" 

/**
 * @brief  DMA channel 1��ʼ��
 **/
void DMA_Channel1_Init(void)
{
    RCC -> AHBENR |= 1 << 0 ;			           //! ����DMA1ʱ��
	  
	  DMA1_Channel1 -> CPAR = (u32)&ADC1->DR ; //! DMA1 �����ַ 
	  DMA1_Channel1 -> CMAR = (u32)AdcValue ;  //! DMA1,�洢����ַ
	
	  DMA1_Channel1 -> CNDTR = 2 ;    	       //! DMA1,����������
	  DMA1_Channel1 -> CCR = 0x00 ;	           //! ��λ
	  DMA1_Channel1 -> CCR |= 1 << 1 ;  		   //! ����������ж�
	  DMA1_Channel1 -> CCR |= 0 << 4 ;  		   //! �������
	  DMA1_Channel1 -> CCR |= 1 << 5 ;  		   //! ѭ��ģʽ
	  DMA1_Channel1 -> CCR |= 0 << 6 ; 		     //! �����ַ������ģʽ
	  DMA1_Channel1 -> CCR |= 1 << 7 ; 	 	     //! �洢������ģʽ
	  DMA1_Channel1 -> CCR |= 1 << 8 ; 	 	     //! �������ݿ��Ϊ8λ
	  DMA1_Channel1 -> CCR |= 1 << 10 ; 		   //! �洢�����ݿ��8λ
	  DMA1_Channel1 -> CCR |= 1 << 12 ; 		   //! �е����ȼ�
	  DMA1_Channel1 -> CCR |= 0 << 14 ; 		   //! �Ǵ洢�����洢��ģʽ		  	
	
		NVIC->IP[DMA1_Channel1_IRQn]=0X1F;       //! �����ж����ȼ�       
		NVIC->ISER[DMA1_Channel1_IRQn >> 0x05] =(u32)0x01 << (DMA1_Channel1_IRQn & (u8)0x1F);
		
		DMA1_Channel1 -> CCR |= 1 << 0 ;         //! ����DMA����
}

