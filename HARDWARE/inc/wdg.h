#ifndef __WDG_H__
#define __WDG_H__

#include "DataType.h"

#include "STM32F103.h"

//!��defWdgPR=4  defWdgRLR=625 ��ι��ʱ��Ϊ64(4��Ӧ��Ƶ��)*625/40K=1S
#define defWdgPR4      0       //! 4��Ƶ
#define defWdgPR8      1       //! 8��Ƶ
#define defWdgPR16     2       //! 16��Ƶ
#define defWdgPR32     3       //! 32��Ƶ
#define defWdgPR64     4       //! 64��Ƶ
#define defWdgPR128    5       //! 128��Ƶ
#define defWdgPR256    6       //! 256��Ƶ


#define defWdgPR    defWdgPR128 //! Ԥ��Ƶ
#define defWdgRLR   625        //! ��װ����

void IWDG_Init(void) ;         //! ��ʼ��
void IWDG_Feed(void) ;         //! �������Ź�ι��

#endif /*  __WDG_H__  */


