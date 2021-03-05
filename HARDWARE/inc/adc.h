#ifndef _ADC_H_
#define _ADC_H_

#include "DataType.h"
#include "Cortex-M3.h"
#include "STM32F103.h"
#include "gpio.h"

extern u16 AdcValue[3] , AdcAverage[3] ;

void ADC_Init(void) ;          //! ADC ��ʼ��
void ADC_Init2(void) ;
void ADC_Inject_Init(void) ;       //! ADC ע��ͨ����ʼ��
u16 ADC_Read_CH0_Value(void);  //! ADC ��ȡͨ��0��ֵ
void Calculate_Adc_Average(void) ; //! ����ADCƽ��ֵ 

#endif //! _ADC_H_

