

#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#include "..\api\low_api.h"
#include "virtual.h"


#pragma swi_number=20
__swi __arm void *malloc(unsigned int size);

#pragma swi_number=21
__swi __arm void free(void *);



void *virtual2physical(void *addr)
{

 UnLockAccess();
 

 int *trans_base = GetTBaseAddr();
 

 unsigned short element = ((int)addr>>0x14)&0xFFF;
 

 if (((trans_base[element])&0x03) == 0x00) return (void *)0xFFFFFFFF;
 

 if (((trans_base[element])&0x03) == 0x01)
  {

   int *coarse_table = (int *)(((int)trans_base[element])&0xFFFFFE00);
   unsigned short subelement = ((int)addr>>0x0C)&0xFF;
   

   if (((coarse_table[subelement])&0x03) == 0x00) return (void *)0xFFFFFFFF;
   

   if (((coarse_table[subelement])&0x03) == 0x01)
    {
     int addr_page = (int)(((int)coarse_table[subelement])&0xFFFF0000);
     int offset = ((int)addr)&0xFFFF;
     return (void *)(addr_page + offset);
    }
   

   if (((coarse_table[subelement])&0x03) == 0x02)
    {
     int addr_page = (int)(((int)coarse_table[subelement])&0xFFFFF000);
     int offset = ((int)addr)&0xFFF;
     return (void *)(addr_page + offset);
    }
  }
 

  if (((trans_base[element])&0x03) == 0x02)
  {
    int addr_section = (int)(((int)trans_base[element])&0xFFF00000);
    int offset = ((int)addr)&0xFFFFF;
    return (void *)(addr_section + offset);
  }
 
 return addr;
}



int RelocateFAddresToRAM(void *addr)
{

 UnLockAccess();


 int *trans_base = GetTBaseAddr();
 unsigned short element = ((int)addr>>0x14)&0xFFF;
  

  if (((trans_base[element])&0xFF) == 0x1E)
   {

     

    char *addr_section = (char *)(((int)addr)&0xFFF00000);
    int *coarse_table = (int *)malloc(0x100 + ADD_SIZE);
    if (!coarse_table)   return 0;
         coarse_table = (int *)virtual2physical((void *)coarse_table);
         

    unsigned short element_d1 = ((int)coarse_table>>0x14)&0xFFF;
    if (((int)(trans_base[element_d1])&0x03) == 0x00)
    trans_base[element_d1] = (((int)coarse_table)&0xFFF00000) + 0xFFE;
    if (((int)(trans_base[element_d1])&0x03) == 0x01)
     {

      int *coarse_table_d = (int *)(((int)trans_base[element_d1])&0xFFFFFE00);
      unsigned short subelement_d = ((int)coarse_table>>0x0C)&0xFF;
      if (((int)(coarse_table_d[subelement_d])&0x03) == 0x00)
      coarse_table_d[subelement_d] = (((int)coarse_table)&0xFFFFF000) + 0xFFE;
     }
    

    int *coarse_table_a = (int *)MALIGN(coarse_table);
    

    for (int i = 0; i < 0x100; i++) coarse_table_a[i] = (int)addr_section + 0x1000*i + 0xFFE;
    

    coarse_table_a[0x100] = (int)coarse_table;
    

    unsigned short subelement = ((int)addr>>0x0C)&0xFF;
    char *addr_page = (char *)((coarse_table_a[subelement])&0xFFFFF000);
    char *rampage = (char *)malloc(0x1000 + ADD_SIZE);
    if  (!rampage)  {free(coarse_table); return 0;}
          rampage = (char *)virtual2physical((void *)rampage);
          

    unsigned short element_d2 = ((int)rampage>>0x14)&0xFFF;
    if ((((int)(trans_base[element_d2])&0x03)) == 0x00)
    trans_base[element_d2] = (((int)rampage)&0xFFF00000) + 0xFFE;
    if ((((int)(trans_base[element_d2])&0x03)) == 0x01)
     {

      int *coarse_table_d = (int *)(((int)trans_base[element_d2])&0xFFFFFE00);
      unsigned short subelement_d = ((int)rampage>>0x0C)&0xFF;
      if (((int)(coarse_table_d[subelement_d])&0x03) == 0x00)
      coarse_table_d[subelement_d] = (((int)rampage)&0xFFFFF000) + 0xFFE;
     }
    
  
    char *rampage_a = (char *)MALIGN(rampage);
    memcpy(rampage_a, addr_page, 0x1000);
    

    int *rampage_int = (int *)rampage_a;
    rampage_int[0x1000] = (int)rampage;
 

    DisableInterrupts();

    ExecuteIMB();

    coarse_table_a[subelement] = (int)rampage_a + 0xFFE;
    trans_base[element] = (int)coarse_table_a + 0x11;
    

    EnableInterrupts();

    return 1;
   }

    else
     {

      int *coarse_table = (int *)(((int)trans_base[element])&0xFFFFF000);
      unsigned short subelement = ((int)addr>>0x0C)&0xFF;
      char stat_page = (coarse_table[subelement]&0x0F000000)>>0x18;
      

      if ((stat_page > 0x00 && stat_page < 0x07) || stat_page == 0x00)
       {

        char *addr_page = (char *)((coarse_table[subelement])&0xFFFFF000);
        char *rampage = (char *)malloc(0x1000 + ADD_SIZE);
        if  (!rampage)  {free(coarse_table); return 0;}
              rampage = (char *)virtual2physical((void *)rampage);
              

        unsigned short element_d2 = ((int)rampage>>0x14)&0xFFF;
        if (((int)(trans_base[element_d2])&0x03) == 0x00)
        trans_base[element_d2] = (((int)rampage)&0xFFF00000) + 0xFFE;
        if (((int)(trans_base[element_d2])&0x03) == 0x01)
        {

          int *coarse_table_d = (int *)(((int)trans_base[element_d2])&0xFFFFFE00);
          unsigned short subelement_d = ((int)rampage>>0x0C)&0xFF;
          if (((int)(coarse_table_d[subelement_d])&0x03) == 0x00)
          coarse_table_d[subelement_d] = (((int)rampage)&0xFFFFF000) + 0xFFE;
         }
    

        char *rampage_a = (char *)MALIGN(rampage);
        memcpy(rampage_a, addr_page, 0x1000);
       

        int *rampage_int = (int *)rampage_a;
        rampage_int[0x1000] = (int)rampage;
    
        

        DisableInterrupts();

        ExecuteIMB();

        coarse_table[subelement] = (int)rampage_a + 0xFFE;
    

        EnableInterrupts();

        return 1;
       }
      

       else return 1;
      
     }
}



