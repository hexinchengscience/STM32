/****************************************************************************************
* �ļ�����: flash.cpp
* 
* ����ʱ�䣺2019/12/12
*
* �޸�ʱ�䣺2020/12/02
*
* ��    �ߣ�science
*
* ��    ����V1.1
*
* ��ժ������FLASH�����ļ�
*
* ˵    ����
*          1������FLASH_Read_N_Byte��FLASH_Write_N_Byte����
****************************************************************************************/ 
#include "flash.h"

/**
 * @brief  FLASH ����
 **/
void FLASH_Unlock(void)
{
    FLASH -> KEYR = FLASH_KEY1 ;  //! д���������.
	  FLASH -> KEYR = FLASH_KEY2 ;
}

/**
 * @brief  FLASH ����
 **/
void FLASH_Lock(void)
{
    FLASH -> CR |= 1 << 7 ;       //! ����
}

/**
 * @brief  FLASH ����ҳ
 * @param  pageAddress ҳ��ַ  ÿҳ1024�ֽ�
 **/
void FLASH_ErasePage(u32 pageAddress)
{
	  while(FLASH ->SR & 0x01) ;   //! �ȴ��������
	  FLASH -> CR |= 1 << 1 ;      //! ҳ����
		FLASH -> AR = pageAddress ;  //! ����ҳ��ַ 
		FLASH -> CR |= 1 << 6 ;      //! ��ʼ����		
	
	  while(FLASH ->SR & 0x01) ;   //! �ȴ��������
	  FLASH -> CR &= ~(1 << 1) ;   //! ���ҳ������־.
}

/**
 * @brief  FLASH д����
 * @param  addr   ���ݵ�ַ
 *         dat    ����
 **/
void FLASH_Write_Word(u32 addr , u16 dat)
{
	  while(FLASH ->SR & 0x01) ;   //! �ȴ��������
	  FLASH -> CR |= 1 << 0 ;		   //! ���ʹ��
	  *(vu16 *) addr = dat ;		   //! д������  
	
	  while(FLASH ->SR & 0x01) ;   //! �ȴ��������
	  FLASH -> CR &= ~(1 << 0) ;	 //! ���PGλ.
}

/**
 * @brief  FLASH д��������
 **/
void FLASH_Write_Practice(void)
{
    FLASH_Unlock()                        ;
    FLASH_ErasePage(0x08004000)           ;
	  FLASH_Write_Word(0x08004000 , 0x1122) ;
	  FLASH_Write_Word(0x08004002 , 0xCCDD) ;
	  FLASH_Write_Word(0x08004004 , 0xEEFF) ;
	  FLASH_Write_Word(0x08004006 , 0x7788) ;
	  FLASH_Write_Word(0x08004008 , 0x5566) ;
	  FLASH_Write_Word(0x0800400A , 0x3344) ;
	  FLASH_Lock()                          ;
}

/**
 * @brief  FLASH ��ĳ����ַ��ȡlen���ȵ����ݱ�����byte��
 * @param  addr  : ��ȡ�ĵ�ַ
 *         byte  : ��������
 *         len   : ��ȡ�ĳ���
 **/
void FLASH_Read_N_Byte(u32 addr , u8 * byte , u16 len)
{
    u32 paramAddr = addr ; 
    for(int i = 0 ; i < len ; ++ i) byte[i] = *(vu8 *) paramAddr ++ ;
}

/**
 * @brief  FLASH �����ݱ�����ָ����ַ��FLASH��
 * @param  addr  : ��ȡ�ĵ�ַ
 *         byte  : ��������
 *         len   : ��ȡ�ĳ���  ������ż��
 **/
void FLASH_Write_N_Byte(u32 addr , u8 * byte , u16 len)
{
    FLASH_Unlock() ;                         //! ����
	  FLASH_ErasePage(addr) ;                  //! ��������
    
	  for(int i = 0 ; i < len / 2 ; ++ i)      //! д����
	  {
		    FLASH_Write_Word(addr + 2 * i , byte[2*i+1] * 256 + byte[2*i]) ;
		}
	  FLASH_Lock() ;                           //! ����
}

