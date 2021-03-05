/****************************************************************************************
* �ļ�����: timer.c
* 
* ����ʱ�䣺2019/11/28
*
* �޸�ʱ�䣺2019/11/28
*
* ��    �ߣ����γ�
*
* ��    ����V1.0
*
* ��ժ��������ʱ������
*
* ˵    ����
****************************************************************************************/ 
#include "timer.h"

/**
 * @brief  ��ʱ��2��ʼ��
 **/
void TIM2_Init(u16 arr , u16 psc)
{
    RCC -> APB1ENR |= 1 << 0 ;      //! TIM2ʱ��ʹ��    
	
	  TIM2 -> PSC = psc ;             //! ����Ԥ��Ƶ��ֵ  
	  TIM2 -> ARR = arr ;             //! ������װ�ص�ֵ 
	
	  TIM2 -> DIER |= 1 << 0 ;        //! ��������ж�    
	  TIM2 -> CR1 |= 1 << 0 ;         //! ʹ�ܼ�����      
	
	  NVIC_Set_IRQn(TIM2_IRQn,0x1F) ; //! �����ж����ȼ�
}

/**
 * @brief  ��ʱ��1 CH1 PWM ��ʼ��
 **/
void PWM_TIM1_CH1_Init(u16 arr , u16 psc)
{
    RCC->APB2ENR |= 1 << 11 ;        //! TIM1ʱ��ʹ��
	  	
	  GPIO_Init(GPIOB , 15 , GPIO_Mode_AF_OD) ;  //! PB15 ���츴�����

	  TIM1->ARR = arr ;                //! �趨�������Զ���װֵ 
	  TIM1->PSC = psc ;                //! Ԥ��Ƶ��
	
	  TIM1->CCMR1 |= 6<<4 ;            //! CH1 PWM2ģʽ	
	  TIM1->CCMR1 |= 1<<3 ;            //! CH1 Ԥװ��ʹ��	   
	  TIM1->CCER |= 1<<0 ;             //! OC1 ���ʹ��	    
	
	  TIM1->CR1 = 0x80 ;               //! ARPEʹ�� 
	  TIM1->CR1 |= 0x01 ;              //! ʹ�ܶ�ʱ��1			
	  
	  TIM1->BDTR |= 1 << 15 ;          //! MOE�����ʹ�ܣ���������ͨ��ʱ����ͬ�ĵط�
}

/**
 * @brief  ��ʱ��1 CH1N PWM ��ʼ��
 **/
void PWM_TIM1_CH1N_Init(u16 arr , u16 psc)
{
    RCC->APB2ENR |= 1 << 11 ;        //! TIM1ʱ��ʹ��
	  
	  RCC -> APB2ENR |= 1 << 3 ;       //! ʹ��GPIOBʱ�� 
	
	  GPIO_Init(GPIOB , 13 , GPIO_Mode_AF_OD) ;  //! PB13   �����������

	  TIM1->ARR = arr ;                //! �趨�������Զ���װֵ 
	  TIM1->PSC = psc ;                //! Ԥ��Ƶ��
	
	  TIM1->CCMR1 |= 6<<4 ;            //! CH1 PWM2ģʽ	
	  TIM1->CCMR1 |= 1<<3 ;            //! CH1 Ԥװ��ʹ��	   
	  TIM1->CCER |= 1<<2 ;             //! OC1 ���ʹ��	    

	  TIM1->CR1 = 0x80 ;               //! ARPEʹ�� 
	  TIM1->CR1 |= 0x01 ;              //! ʹ�ܶ�ʱ��3 				
		
		TIM1->BDTR |= 1 << 15 ;          //! MOE�����ʹ�ܣ���������ͨ��ʱ����ͬ�ĵط�
}

/**
 * @brief  ��ʱ��1 CH1N PWM ��ʼ��
 **/
void PWM_TIM1_CH2N_Init(u16 arr , u16 psc)
{
    RCC->APB2ENR |= 1 << 11 ;        //! TIM1ʱ��ʹ��
	  
	  RCC -> APB2ENR |= 1 << 3 ;       //! ʹ��GPIOBʱ�� 
	
	  GPIO_Init(GPIOB , 14 , GPIO_Mode_AF_OD) ;  //! PB14   �����������

	  TIM1->ARR = arr ;                //! �趨�������Զ���װֵ 
	  TIM1->PSC = psc ;                //! Ԥ��Ƶ��
	
	  TIM1->CCMR1 |= 6<<12 ;           //! CH2 PWM2ģʽ	
	  TIM1->CCMR1 |= 1<<11 ;           //! CH2 Ԥװ��ʹ��	   
	  TIM1->CCER |= 1<<6 ;             //! OC2 ���ʹ��	    

	  TIM1->CR1 = 0x80 ;               //! ARPEʹ�� 
	  TIM1->CR1 |= 0x01 ;              //! ʹ�ܶ�ʱ��3 				
		
		TIM1->BDTR |= 1 << 15 ;          //! MOE�����ʹ�ܣ���������ͨ��ʱ����ͬ�ĵط�
}

/**
 * @brief  ��ʱ��1 CH3N PWM ��ʼ��
 **/
void PWM_TIM1_CH3N_Init(u16 arr , u16 psc)
{
    RCC->APB2ENR |= 1 << 11 ;        //! TIM1ʱ��ʹ��
	  	
	  GPIO_Init(GPIOA , 8 , GPIO_Mode_AF_OD) ;   //! PA8  ���츴�����

	  TIM1->ARR = arr ;                //! �趨�������Զ���װֵ 
	  TIM1->PSC = psc ;                //! Ԥ��Ƶ��
	
	  TIM1->CCMR2 |= 6<<4 ;            //! CH3 PWM2ģʽ	
	  TIM1->CCMR2 |= 1<<3 ;            //! CH3 Ԥװ��ʹ��	   
	  TIM1->CCER |= 1<<10 ;            //! OC3 ���ʹ��	 
	
	  TIM1->CR1 = 0x80 ;               //! ARPEʹ�� 
	  TIM1->CR1 |= 0x01 ;              //! ʹ�ܶ�ʱ��1			
	  
	  TIM1->BDTR |= 1 << 15 ;          //! MOE�����ʹ�ܣ���������ͨ��ʱ����ͬ�ĵط�
}

/**
 * @brief  ��ʱ��1 CH4 PWM ��ʼ��
 **/
void PWM_TIM1_CH4_Init(u16 arr , u16 psc)
{
    RCC->APB2ENR |= 1 << 11 ;        //! TIM1ʱ��ʹ��
	  	
	  GPIO_Init(GPIOA , 11 , GPIO_Mode_AF_OD) ;  //! PA11   �������

	  TIM1->ARR = arr ;                //! �趨�������Զ���װֵ 
	  TIM1->PSC = psc ;                //! Ԥ��Ƶ��
	
	  TIM1->CCMR2 |= 6 << 12 ;         //! CH4 PWM2ģʽ	
	  TIM1->CCMR2 |= 1 << 11 ;         //! CH4 Ԥװ��ʹ��	   
	  TIM1->CCER |= 1 << 12 ;          //! OC4 ���ʹ��	    
	
	  TIM1->CR1 = 0x80 ;               //! ARPEʹ�� 
	  TIM1->CR1 |= 0x01 ;              //! ʹ�ܶ�ʱ��1			
	  
	  TIM1->BDTR |= 1 << 15 ;          //! MOE�����ʹ�ܣ���������ͨ��ʱ����ͬ�ĵط�
}

/**
 * @brief  ��ʱ��1 CH1 CH3N CH4 PWM ��ʼ��
 **/
void PWM_TIM1_CH1_CH3_CH4_Init(u16 arr , u16 psc)
{
    RCC->APB2ENR |= 1 << 11 ;        //! TIM1ʱ��ʹ��
	  	
	  GPIO_Init(GPIOB , 15 , GPIO_Mode_AF_OD) ;  //! PB15 ���츴�����
	  GPIO_Init(GPIOA , 8 , GPIO_Mode_AF_OD) ;   //! PA8  ���츴�����
	  GPIO_Init(GPIOA , 11 , GPIO_Mode_AF_OD) ;  //! PA11   �������

	  TIM1->ARR = arr ;                //! �趨�������Զ���װֵ 
	  TIM1->PSC = psc ;                //! Ԥ��Ƶ��
	
	  TIM1->CCMR1 |= 6<<4 ;            //! CH1 PWM2ģʽ	
	  TIM1->CCMR1 |= 1<<3 ;            //! CH1 Ԥװ��ʹ��	   
	  TIM1->CCER |= 1<<0 ;             //! OC1 ���ʹ��	    
	
	  TIM1->CCMR2 |= 6<<4 ;            //! CH3 PWM2ģʽ	
	  TIM1->CCMR2 |= 1<<3 ;            //! CH3 Ԥװ��ʹ��	   
	  TIM1->CCER |= 1<<10 ;            //! OC3 ���ʹ��	 

	  TIM1->CCMR2 |= 6 << 12 ;         //! CH4 PWM2ģʽ	
	  TIM1->CCMR2 |= 1 << 11 ;         //! CH4 Ԥװ��ʹ��	   
	  TIM1->CCER |= 1 << 12 ;          //! OC4 ���ʹ��	    
	
	  TIM1->CR1 = 0x80 ;               //! ARPEʹ�� 
	  TIM1->CR1 |= 0x01 ;              //! ʹ�ܶ�ʱ��1			
	  
	  TIM1->BDTR |= 1 << 15 ;          //! MOE�����ʹ�ܣ���������ͨ��ʱ����ͬ�ĵط�
}

/**
 * @brief  ��ʱ��3 All CH PWM ��ʼ��
 **/
void PWM_TIM1_All_CH_Init(u16 arr , u16 psc)
{
    RCC->APB2ENR |= 1 << 11 ;        //! TIM1ʱ��ʹ��
	  
	  RCC -> APB2ENR |= 1 << 2 ;       //! ʹ��GPIOAʱ�� 
	  RCC -> APB2ENR |= 1 << 3 ;       //! ʹ��GPIOBʱ�� 
	
	  GPIO_Init(GPIOA , 11 , GPIO_Mode_AF_OD) ;  //! PA11   �����������
	  GPIO_Init(GPIOB , 13 , GPIO_Mode_AF_OD) ;  //! PB13   �����������
	  GPIO_Init(GPIOB , 14 , GPIO_Mode_AF_OD) ;  //! PB14   �����������
	  GPIO_Init(GPIOB , 15 , GPIO_Mode_AF_OD) ;  //! PB15   �����������

	  TIM1->ARR = arr ;                //! �趨�������Զ���װֵ 
	  TIM1->PSC = psc ;                //! Ԥ��Ƶ��
	
	  TIM1->CCMR1 |= 6<<4 ;            //! CH1 PWM2ģʽ	
	  TIM1->CCMR1 |= 1<<3 ;            //! CH1 Ԥװ��ʹ��	   
	  TIM1->CCER |= 1<<2 ;             //! OC1 ���ʹ��	    
	
	  TIM1->CCMR1 |= 6<<12 ;           //! CH2 PWM2ģʽ	
	  TIM1->CCMR1 |= 1<<11 ;           //! CH2 Ԥװ��ʹ��	   
	  TIM1->CCER |= 1<<6 ;             //! OC2 ���ʹ��	    
	
	  TIM1->CCMR2 |= 6<<4 ;            //! CH3 PWM2ģʽ	
	  TIM1->CCMR2 |= 1<<3 ;            //! CH3 Ԥװ��ʹ��	   
	  TIM1->CCER |= 1<<10 ;             //! OC3 ���ʹ��	    
	
	  TIM1->CCMR2 |= 6<<12 ;           //! CH4 PWM2ģʽ	
	  TIM1->CCMR2 |= 1<<11 ;           //! CH4 Ԥװ��ʹ��	   
	  TIM1->CCER |= 1<<12 ;            //! OC4 ���ʹ��	    

	  TIM1->CR1 = 0x80 ;               //! ARPEʹ�� 
	  TIM1->CR1 |= 0x01 ;              //! ʹ�ܶ�ʱ��3 				
		
		TIM1->BDTR |= 1 << 15 ;          //! MOE�����ʹ�ܣ���������ͨ��ʱ����ͬ�ĵط�
}

/**
 * @brief  ��ʱ��2 CH1 PWM ��ʼ��
 * @note   PA15 ��Ϊ��ͨIO��ʱ����Ҫ����������������AFIO�Ĵ���������Ҫ��AFIOʱ��
 **/
void PWM_TIM2_CH1_Init(u16 arr , u16 psc)
{
    RCC->APB1ENR |= 1 << 0 ;         //! TIM2ʱ��ʹ��
	  RCC->APB2ENR |= 1 << 0 ;         //! AFIOʱ��ʹ��
	  RCC->APB2ENR |= 1 << 2 ;         //! ʹ��GPIOAʱ�� 
	  
	  AFIO -> MAPR |= (2 << 24) ;      //! PA15 �ر�JTAG���湦��
	  AFIO -> MAPR |= (1 << 8) ;       //! TIM2 CH1 ѡ��PA15
	  
	  GPIO_Init(GPIOA , 15 , GPIO_Mode_AF_OD) ;  //! PA15 ���츴�����

	  TIM2->ARR = arr ;                //! �趨�������Զ���װֵ  
	  TIM2->PSC = psc ;                //! Ԥ��Ƶ��
	
	  TIM2->CCMR1 |= 7<<4 ;            //! CH1 PWM2ģʽ	
	  TIM2->CCMR1 |= 1<<3 ;            //! CH1 Ԥװ��ʹ��	   

	  TIM2->CCER |= 1<<0 ;             //! OC1 ���ʹ��	    

	  TIM2->CR1 = 0x80 ;               //! ARPEʹ�� 
	  TIM2->CR1 |= 0x01 ;              //! ʹ�ܶ�ʱ��3 				 
}

/**
 * @brief  ��ʱ��2 CH2 PWM ��ʼ��
 **/
void PWM_TIM2_CH2_Init(u16 arr , u16 psc)
{
    RCC -> APB1ENR |= 1 << 0 ;       //! TIM2ʱ��ʹ��
	  RCC -> APB2ENR |= 1 << 3 ;       //! ʹ��GPIOBʱ�� 
	
	  RCC -> APB2ENR |= 1 << 0 ;       //! AFIOʱ��ʹ��
	
	  AFIO -> MAPR &= ~(3 << 24) ;     //! �ر�JTAG-DP������SW-DP��
	  AFIO -> MAPR |= (2 << 24) ;
	
	  AFIO -> MAPR &= ~(3 << 8) ;      //! PB3��ΪTIM2_CH2ͨ��
	  AFIO -> MAPR |= (1 << 8) ;
	  
	  GPIO_Init(GPIOB , 3 , GPIO_Mode_AF_OD) ;  //! PB3   �������

	  TIM2->ARR = arr ;                //! �趨�������Զ���װֵ 
	  TIM2->PSC = psc ;                //! Ԥ��Ƶ��
	
	  TIM2->CCMR1 |= 7<<12 ;           //! CH2 PWM2ģʽ	
	  TIM2->CCMR1 |= 1<<11 ;           //! CH2 Ԥװ��ʹ��	   
	  TIM2->CCER |= 1<<4 ;             //! OC2 ���ʹ��	    

	  TIM2->CR1 = 0x80 ;               //! ARPEʹ�� 
	  TIM2->CR1 |= 0x01 ;              //! ʹ�ܶ�ʱ��2		
}

/**
 * @brief  ��ʱ��3 CH1 PWM ��ʼ��
 **/
void PWM_TIM3_CH1_Init(u16 arr , u16 psc)
{
    RCC -> APB1ENR |= 1 << 1 ;       //! TIM3ʱ��ʹ��
	  RCC -> APB2ENR |= 1 << 3 ;       //! ʹ��GPIOBʱ�� 
	
	  RCC -> APB2ENR |= 1 << 0 ;       //! AFIOʱ��ʹ��
	
	  AFIO -> MAPR &= ~(3 << 24) ;     //! �ر�JTAG-DP������SW-DP��
	  AFIO -> MAPR |= (2 << 24) ;
	
	  AFIO -> MAPR &= ~(3 << 10) ;     //! PB4��ΪTIM3_CH1ͨ��
	  AFIO -> MAPR |= (2 << 10) ;
	  
	  GPIO_Init(GPIOB , 4 , GPIO_Mode_AF_OD) ;  //! PB4   �������
	 
	  TIM3->ARR = arr ;                //! �趨�������Զ���װֵ 
	  TIM3->PSC = psc ;                //! Ԥ��Ƶ��
	
	  TIM3->CCMR1 |= 6<<4 ;            //! CH1 PWM2ģʽ	
	  TIM3->CCMR1 |= 1<<3 ;            //! CH1 Ԥװ��ʹ��	   
	  TIM3->CCER |= 1<<0 ;             //! OC1 ���ʹ��	    

	  TIM3->CR1 = 0x80 ;               //! ARPEʹ�� 
	  TIM3->CR1 |= 0x01 ;              //! ʹ�ܶ�ʱ��3 				
}

/**
 * @brief  ��ʱ��3 CH2 PWM ��ʼ��
 **/
void PWM_TIM3_CH2_Init(u16 arr , u16 psc)
{
    RCC->APB1ENR |= 1 << 1 ;         //! TIM3ʱ��ʹ��
	  
	  GPIO_Init(GPIOA , 7 , GPIO_Mode_AF_OD) ;  //! PA7   �������

	  TIM3->ARR = arr ;                //! �趨�������Զ���װֵ 
	  TIM3->PSC = psc ;                //! Ԥ��Ƶ��
	
	  TIM3->CCMR1 |= 6<<12 ;           //! CH2 PWM2ģʽ	
	  TIM3->CCMR1 |= 1<<11 ;           //! CH2 Ԥװ��ʹ��	   
	  TIM3->CCER |= 1<<4 ;             //! OC2 ���ʹ��	    

	  TIM3->CR1 = 0x80 ;               //! ARPEʹ�� 
	  TIM3->CR1 |= 0x01 ;              //! ʹ�ܶ�ʱ��3 				
}

/**
 * @brief  ��ʱ��3 CH3 PWM ��ʼ��
 **/
void PWM_TIM3_CH3_Init(u16 arr , u16 psc)
{
    RCC->APB1ENR |= 1 << 1 ;         //! TIM3ʱ��ʹ��
	  
	  GPIO_Init(GPIOB , 0 , GPIO_Mode_AF_OD) ;  //! PB0   �������
	  
	  TIM3->ARR = arr ;                //! �趨�������Զ���װֵ 
	  TIM3->PSC = psc ;                //! Ԥ��Ƶ��
	
	  TIM3->CCMR2 |= 6<<4 ;            //! CH3 PWM2ģʽ	
	  TIM3->CCMR2 |= 1<<3 ;            //! CH3 Ԥװ��ʹ��	   
	  TIM3->CCER |= 1<<8 ;             //! OC3 ���ʹ��	    

	  TIM3->CR1 = 0x80 ;               //! ARPEʹ�� 
	  TIM3->CR1 |= 0x01 ;              //! ʹ�ܶ�ʱ��3 				
}

/**
 * @brief  ��ʱ��3 CH4 PWM ��ʼ��
 **/
void PWM_TIM3_CH4_Init(u16 arr , u16 psc)
{
    RCC->APB1ENR |= 1 << 1 ;         //! TIM3ʱ��ʹ��
	  
	  GPIO_Init(GPIOB , 1 , GPIO_Mode_AF_OD) ;  //! PB1   �������
	  
	  TIM3->ARR = arr ;                //! �趨�������Զ���װֵ 
	  TIM3->PSC = psc ;                //! Ԥ��Ƶ��
	
	  TIM3->CCMR2 |= 6 << 12 ;         //! CH4 PWM2ģʽ	
	  TIM3->CCMR2 |= 1 << 11 ;         //! CH4 Ԥװ��ʹ��	   
	  TIM3->CCER |= 1 << 12 ;          //! OC4 ���ʹ��	    

	  TIM3->CR1 = 0x80 ;               //! ARPEʹ�� 
	  TIM3->CR1 |= 0x01 ;              //! ʹ�ܶ�ʱ��3 				
}

/**
 * @brief  ��ʱ��3 All CH PWM ��ʼ��
 **/
void PWM_TIM3_All_CH_Init(u16 arr , u16 psc)
{
    RCC->APB1ENR |= 1 << 1 ;         //! TIM3ʱ��ʹ��
	
	  RCC -> APB2ENR |= 1 << 2 ;                //! ��A��ʱ��
	  RCC -> APB2ENR |= 1 << 3 ;                //! ��B��ʱ��
	
	  GPIO_Init(GPIOA , 6 , GPIO_Mode_AF_OD) ;  //! PA6   �������
	  GPIO_Init(GPIOA , 7 , GPIO_Mode_AF_OD) ;  //! PA7   �������
	  GPIO_Init(GPIOB , 0 , GPIO_Mode_AF_OD) ;  //! PB0   �������
	  GPIO_Init(GPIOB , 1 , GPIO_Mode_AF_OD) ;  //! PB1   �������

	  TIM3->ARR = arr ;                //! �趨�������Զ���װֵ 
	  TIM3->PSC = psc ;                //! Ԥ��Ƶ��
	
	  TIM3->CCMR1 |= 6<<4 ;            //! CH1 PWM2ģʽ	
	  TIM3->CCMR1 |= 1<<3 ;            //! CH1 Ԥװ��ʹ��	   
	  TIM3->CCER |= 1<<0 ;             //! OC1 ���ʹ��	    
	
	  TIM3->CCMR1 |= 6<<12 ;           //! CH2 PWM2ģʽ	
	  TIM3->CCMR1 |= 1<<11 ;           //! CH2 Ԥװ��ʹ��	   
	  TIM3->CCER |= 1<<4 ;             //! OC2 ���ʹ��	    
	
	  TIM3->CCMR2 |= 6<<4 ;            //! CH3 PWM2ģʽ	
	  TIM3->CCMR2 |= 1<<3 ;            //! CH3 Ԥװ��ʹ��	   
	  TIM3->CCER |= 1<<8 ;             //! OC3 ���ʹ��	    
	
	  TIM3->CCMR2 |= 6<<12 ;           //! CH4 PWM2ģʽ	
	  TIM3->CCMR2 |= 1<<11 ;           //! CH4 Ԥװ��ʹ��	   
	  TIM3->CCER |= 1<<12 ;            //! OC4 ���ʹ��	    

	  TIM3->CR1 = 0x80 ;               //! ARPEʹ�� 
	  TIM3->CR1 |= 0x01 ;              //! ʹ�ܶ�ʱ��3 				
}

/**
 * @brief  ��ʱ��3 CH1 PWM ��ʼ��
 **/
void PWM_TIM4_CH1_Init(u16 arr , u16 psc)
{
    RCC -> APB1ENR |= 1 << 2 ;       //! TIM4ʱ��ʹ��
	  RCC -> APB2ENR |= 1 << 3 ;       //! ʹ��GPIOBʱ�� 
	  
	  GPIO_Init(GPIOB , 6 , GPIO_Mode_AF_OD) ;  //! PB6   �������
	 
	  TIM4->ARR = arr ;                //! �趨�������Զ���װֵ 
	  TIM4->PSC = psc ;                //! Ԥ��Ƶ��
	
	  TIM4->CCMR1 |= 6<<4 ;            //! CH1 PWM2ģʽ	
	  TIM4->CCMR1 |= 1<<3 ;            //! CH1 Ԥװ��ʹ��	   
	  TIM4->CCER |= 1<<0 ;             //! OC1 ���ʹ��	    

	  TIM4->CR1 = 0x80 ;               //! ARPEʹ�� 
	  TIM4->CR1 |= 0x01 ;              //! ʹ�ܶ�ʱ��4				
}

/**
 * @brief  ��ʱ��4 All CH PWM ��ʼ��
 **/
void PWM_TIM4_All_CH_Init(u16 arr , u16 psc)
{
    RCC->APB1ENR |= 1 << 2 ;         //! TIM4ʱ��ʹ��
	  
	  GPIO_Init(GPIOB , 6 , GPIO_Mode_AF_OD) ;  //! PB6   �������
	  GPIO_Init(GPIOB , 7 , GPIO_Mode_AF_OD) ;  //! PB7   �������
	  GPIO_Init(GPIOB , 8 , GPIO_Mode_AF_OD) ;  //! PB8   �������
	  GPIO_Init(GPIOB , 9 , GPIO_Mode_AF_OD) ;  //! PB9   �������

	  TIM4->ARR = arr ;                //! �趨�������Զ���װֵ 
	  TIM4->PSC = psc ;                //! Ԥ��Ƶ��
	
	  TIM4->CCMR1 |= 6<<4 ;            //! CH1 PWM2ģʽ	
	  TIM4->CCMR1 |= 1<<3 ;            //! CH1 Ԥװ��ʹ��	   
	  TIM4->CCER |= 1<<0 ;             //! OC1 ���ʹ��	  
	
	  TIM4->CCMR1 |= 6<<12 ;           //! CH2 PWM2ģʽ	
	  TIM4->CCMR1 |= 1<<11 ;           //! CH2 Ԥװ��ʹ��	   
	  TIM4->CCER |= 1<<4 ;             //! OC2 ���ʹ��	    
	
	  TIM4->CCMR2 |= 6<<4 ;            //! CH3 PWM2ģʽ	
	  TIM4->CCMR2 |= 1<<3 ;            //! CH3 Ԥװ��ʹ��	   
	  TIM4->CCER |= 1<<8 ;             //! OC3 ���ʹ��	    
	
	  TIM4->CCMR2 |= 6<<12 ;           //! CH4 PWM2ģʽ	
	  TIM4->CCMR2 |= 1<<11 ;           //! CH4 Ԥװ��ʹ��	   
	  TIM4->CCER |= 1<<12 ;            //! OC4 ���ʹ��	    

	  TIM4->CR1 = 0x80 ;               //! ARPEʹ�� 
	  TIM4->CR1 |= 0x01 ;              //! ʹ�ܶ�ʱ��3 				
}
