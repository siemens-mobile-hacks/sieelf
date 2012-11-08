#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#include "vkp_parser.h" 



#pragma swi_number=20
__swi __arm void *malloc(unsigned int size);

#pragma swi_number=21
__swi __arm void free(void *);


int VKP_CommentsCleaner(char *vkp_body, int vkp_size, int *vkp_new_size)
{
  if (vkp_new_size) *vkp_new_size = 0;
  if (!vkp_body)  return RET_VKPBODY_IS_NULL;
  if (!vkp_size)  return RET_VKPBODY_IS_NULL;
  
  // /* */ Comments Clean
  for (int i = 0; i < vkp_size; i++)
   {
     if (vkp_body[i + 0] == '/' && vkp_body[i + 1] == '*')     
      {
       for (int k = i; k < vkp_size; k++)
        {             
         if (vkp_body[k + 0] == '*' && vkp_body[k + 1] == '/')     
          {                      
           vkp_body[k + 0] = 0x01;
           vkp_body[k + 1] = 0x01;
           i = k + 1;
           break;
          }
          
         if(k >= vkp_size - 1) return -1;
         vkp_body[k] = 0x01;
          
        }         
      }     
   }   
   
  // ';' Comments Clean 
  for (int i = 0; i < vkp_size; i++)
   {
     if (vkp_body[i] == ';')     
      {
       for (int k = i; k < vkp_size; k++)
        {             
         if (vkp_body[k] == '\n' || k == vkp_size)     
          {                      
           i = k;
           break;
          }
         vkp_body[k] = 0x01;
        }         
      }     
   }   
   
  int k = 0, p = 0;
  for (int i = 0; k < vkp_size; i++,k++)
   {
     if (vkp_body[i] == 0x01) 
     {
      k--;  
      p++;
     }
      else vkp_body[k] = vkp_body[i];
   } 
       
  
  int ns = vkp_size - p;
  if (vkp_new_size) *vkp_new_size = ns;
  memset((char *)((unsigned int)vkp_body + ns), 0, vkp_size - ns);
  
  return RET_SUCCESS;
}


int VKP_VoidStringsCleaner(char *vkp_body, int vkp_size, int *vkp_new_size)
{
  int nstrings = 0;
  if (vkp_new_size) *vkp_new_size = 0;
    
  if (!vkp_body)  return RET_VKPBODY_IS_NULL;
  if (!vkp_size)  return RET_VKPBODY_IS_NULL;
  
  //Get Info about number of strings
  for (int i = 0; i < vkp_size; i++) if (vkp_body[i] == '\n') nstrings++;
  
  VKP_STRING *vs = (VKP_STRING *)malloc(nstrings*sizeof(VKP_STRING));
  if (!vs) return RET_IS_NO_MEM;
  
  
  for (int i = 0, k = 0; i < nstrings; i++) 
   { 
     vs[i].offset = k;
     while (k <= vkp_size)
      {
        if (vkp_body[k] == '\n' || k == vkp_size)  
         {
          vs[i].size = k - vs[i].offset;
          k++;
          break;
         }      
        k++; 
      }
   }
   
   //Clearing void strings
   for (int i = 0; i < nstrings; i++) 
    {
      int j = 0;
      for (int k = 0; k <= vs[i].size; k++)  
       {
             if (vkp_body[vs[i].offset + k] == ' ');
        else if (vkp_body[vs[i].offset + k] == '\r');
        else if (vkp_body[vs[i].offset + k] == '\t');
        else if (vkp_body[vs[i].offset + k] == '\n');
        else 
         {
           j = 1;   
           break;  
         }  
       }
        
       if (!j)
         {
           for (int k = 0; k <= vs[i].size; k++) vkp_body[vs[i].offset + k]  = 0x01;  
         }
    }
  
  free((void *)vs);

  int k = 0, p = 0;
  for (int i = 0; k < vkp_size; i++,k++)
   {
     if (vkp_body[i] == 0x01) 
     {
      k--;  
      p++;
     }
      else vkp_body[k] = vkp_body[i];
   } 
       
  
  int ns = vkp_size - p;
  if (vkp_new_size) *vkp_new_size = ns;
  memset((char *)((unsigned int)vkp_body + ns), 0, vkp_size - ns);
  
  return RET_SUCCESS;
}

int VKP_TabSymbolsCleaner(char *vkp_body, int vkp_size, int *vkp_new_size)
{
  if (vkp_new_size) *vkp_new_size = 0;
    
  if (!vkp_body)  return RET_VKPBODY_IS_NULL;
  if (!vkp_size)  return RET_VKPBODY_IS_NULL;
  
  for (int i = 0; i < vkp_size; i++)  
   {
    if (vkp_body[i] == '\r')  vkp_body[i] = 0x01;
    if (vkp_body[i] == '\t')  vkp_body[i] = 0x01;
   }
   
  int k = 0, p = 0;
  for (int i = 0; k < vkp_size; i++,k++)
   {
     if (vkp_body[i] == 0x01) 
     {
      k--;  
      p++;
     }
      else vkp_body[k] = vkp_body[i];
   } 
       
  int ns = vkp_size - p;
  if (vkp_new_size) *vkp_new_size = ns;
  memset((char *)((unsigned int)vkp_body + ns), 0, vkp_size - ns);
  
  return RET_SUCCESS;
   
}

int VKP_PostSpaceCleaner(char *vkp_body, int vkp_size, int *vkp_new_size)
{
  if (vkp_new_size) *vkp_new_size = 0;
    
  if (!vkp_body)  return RET_VKPBODY_IS_NULL;
  if (!vkp_size)  return RET_VKPBODY_IS_NULL;
  
  for (int i = 0; i < vkp_size; i++) 
   {
    if (vkp_body[i] == '\n')  
     {
      if (vkp_body[i-1] == ' ') vkp_body[i-1] = 0x01;                  
     }    
   }
  
  int k = 0, p = 0;
  for (int i = 0; k < vkp_size; i++,k++)
   {
     if (vkp_body[i] == 0x01) 
     {
      k--;  
      p++;
     }
      else vkp_body[k] = vkp_body[i];
   } 
       
  int ns = vkp_size - p;
  if (vkp_new_size) *vkp_new_size = ns;
  memset((char *)((unsigned int)vkp_body + ns), 0, vkp_size - ns);
  
  return RET_SUCCESS; 
}

int VKP_LongSpaceCleaner(char *vkp_body, int vkp_size, int *vkp_new_size)
{
  if (vkp_new_size) *vkp_new_size = 0;
    
  if (!vkp_body)  return RET_VKPBODY_IS_NULL;
  if (!vkp_size)  return RET_VKPBODY_IS_NULL;
  
  for (int i = 0; i < vkp_size; i++)  
   {
     if (vkp_body[i] == ' ')  
      { 
       i++; 
       int k = i - 1;   
       int l = i - 2;   
       while (i < vkp_size)   
        {
          if (vkp_body[l] == '\n' || i == 1) vkp_body[k] = 0x01;
          if (vkp_body[i] == ':')  vkp_body[k] = 0x01;
          if (vkp_body[i] == ' ')  vkp_body[i] = 0x01;
           else break;
          i++;
        }          
      } 
   }
   
  int k = 0, p = 0;
  for (int i = 0; k < vkp_size; i++,k++)
   {
     if (vkp_body[i] == 0x01) 
     {
      k--;  
      p++;
     }
      else vkp_body[k] = vkp_body[i];
   } 
       
  int ns = vkp_size - p;
  if (vkp_new_size) *vkp_new_size = ns;
  memset((char *)((unsigned int)vkp_body + ns), 0, vkp_size - ns);
  
  return RET_SUCCESS; 
}



int VKP_0xAddressCleaner(char *vkp_body, int vkp_size, int *vkp_new_size)
{
  int nstrings = 0;
  if (vkp_new_size) *vkp_new_size = 0;
    
  if (!vkp_body)  return RET_VKPBODY_IS_NULL;
  if (!vkp_size)  return RET_VKPBODY_IS_NULL;
  
  //Get Info about number of strings
  for (int i = 0; i < vkp_size; i++) if (vkp_body[i] == '\n') nstrings++;
  
  VKP_STRING *vs = (VKP_STRING *)malloc(nstrings*sizeof(VKP_STRING));
  if (!vs) return RET_IS_NO_MEM;
  
  for (int i = 0, k = 0; i < nstrings; i++) 
   { 
     vs[i].offset = k;
     while (k <= vkp_size)
      {
        if (vkp_body[k] == '\n' || k == vkp_size)  
         {
          vs[i].size = k - vs[i].offset;
          k++;
          break;
         }      
        k++; 
      }
   }
   
   //Clearing void strings
   for (int i = 0; i < nstrings; i++) 
    {
      if (vkp_body[vs[i].offset + 0] == '0' && vkp_body[vs[i].offset + 1] == 'x')
       {                      
        vkp_body[vs[i].offset + 0] = 0x01;  
        vkp_body[vs[i].offset + 1] = 0x01;                    
       }
       
      if (vkp_body[vs[i].offset + 0] == '+' && vkp_body[vs[i].offset + 1] == '0' && vkp_body[vs[i].offset + 2] == 'x')
       {                      
        vkp_body[vs[i].offset + 1] = 0x01;  
        vkp_body[vs[i].offset + 2] = 0x01;                    
       }
       
      if (vkp_body[vs[i].offset + 0] == '-' && vkp_body[vs[i].offset + 1] == '0' && vkp_body[vs[i].offset + 2] == 'x')
       {                      
        vkp_body[vs[i].offset + 1] = 0x01;  
        vkp_body[vs[i].offset + 2] = 0x01;                    
       }
    }
  
  free((void *)vs);

  int k = 0, p = 0;
  for (int i = 0; k < vkp_size; i++,k++)
   {
     if (vkp_body[i] == 0x01) 
     {
      k--;  
      p++;
     }
      else vkp_body[k] = vkp_body[i];
   } 
       
  int ns = vkp_size - p;
  if (vkp_new_size) *vkp_new_size = ns;
  memset((char *)((unsigned int)vkp_body + ns), 0, vkp_size - ns);
  
  return RET_SUCCESS;
}


int VKP_Hex2DumpConverter(char *vkp_body, int vkp_size, int *vkp_new_size)
{
  if (vkp_new_size) *vkp_new_size = 0;
    
  if (!vkp_body)  return RET_VKPBODY_IS_NULL;
  if (!vkp_size)  return RET_VKPBODY_IS_NULL;
  
  for (int i = 0; i < vkp_size; i++) 
   {
    if (vkp_body[i + 0] == '0')  
     {
      if (vkp_body[i + 1] == 'x')  
       {
        int k = i + 2;
        int s = i;
        int hsz = 0;
        char data[32]; 
        for (int l = 0; l < 16; k++, l++)  
         {
           data[l] = vkp_body[k];
           if (vkp_body[k] == ',' || vkp_body[k] == ' ' || vkp_body[k] == '\n') 
            {
             data[l] = '\0';
             break;
            }  
         }
         hsz = strlen(data);  
         
         vkp_body[s + hsz + 0] = 0x01;
         vkp_body[s + hsz + 1] = 0x01;
         
         
         switch (hsz)
          {
            case 0x00:
             {
              return RET_HEXVALUE_IS_NULL; 
             }   
            case 0x01:
             {
              vkp_body[s + 0] = '0';
              vkp_body[s + 1] = data[0];
              break; 
             }   
            case 0x02:
             {
              vkp_body[s + 0] = data[0];
              vkp_body[s + 1] = data[1];
              break; 
             } 
            case 0x03:
             {
              vkp_body[s + 0] = '0';
              vkp_body[s + 1] = data[2];
              vkp_body[s + 2] = data[0];
              vkp_body[s + 3] = data[1];
              break; 
             } 
            case 0x04:
             {
              vkp_body[s + 0] = data[2];
              vkp_body[s + 1] = data[3];
              vkp_body[s + 2] = data[0];
              vkp_body[s + 3] = data[1];
              break; 
             }
            case 0x05:
             {
              vkp_body[s + 0] = '0';
              vkp_body[s + 1] = data[4];
              vkp_body[s + 2] = data[2];
              vkp_body[s + 3] = data[3];
              vkp_body[s + 4] = data[0];
              vkp_body[s + 5] = data[1];
              break; 
             }
           case 0x06:
             {
              vkp_body[s + 0] = data[4];
              vkp_body[s + 1] = data[5];
              vkp_body[s + 2] = data[2];
              vkp_body[s + 3] = data[3];
              vkp_body[s + 4] = data[0];
              vkp_body[s + 5] = data[1];
              break; 
             }
           case 0x07:
             {
              vkp_body[s + 0] = '0';
              vkp_body[s + 1] = data[6];
              vkp_body[s + 2] = data[4];
              vkp_body[s + 3] = data[5];
              vkp_body[s + 4] = data[2];
              vkp_body[s + 5] = data[3];
              vkp_body[s + 6] = data[0];
              vkp_body[s + 7] = data[1];
              break; 
             }
           case 0x08:
             {
              vkp_body[s + 0] = data[6];
              vkp_body[s + 1] = data[7];
              vkp_body[s + 2] = data[4];
              vkp_body[s + 3] = data[5];
              vkp_body[s + 4] = data[2];
              vkp_body[s + 5] = data[3];
              vkp_body[s + 6] = data[0];
              vkp_body[s + 7] = data[1];
              break; 
             }
           case 0x09:
             {
              vkp_body[s + 0] = data[6];
              vkp_body[s + 1] = data[7];
              vkp_body[s + 2] = data[4];
              vkp_body[s + 3] = data[5];
              vkp_body[s + 4] = data[2];
              vkp_body[s + 5] = data[3];
              vkp_body[s + 6] = data[0];
              vkp_body[s + 7] = data[1];
              vkp_body[s + 8] = '0';
              vkp_body[s + 9] = data[8];
              break; 
             }
           case 0x0A:
             {
              vkp_body[s + 0] = data[6];
              vkp_body[s + 1] = data[7];
              vkp_body[s + 2] = data[4];
              vkp_body[s + 3] = data[5];
              vkp_body[s + 4] = data[2];
              vkp_body[s + 5] = data[3];
              vkp_body[s + 6] = data[0];
              vkp_body[s + 7] = data[1];
              vkp_body[s + 8] = data[8];
              vkp_body[s + 9] = data[9];
              break; 
             }
           case 0x0B:
             {
              vkp_body[s + 0] = data[6];
              vkp_body[s + 1] = data[7];
              vkp_body[s + 2] = data[4];
              vkp_body[s + 3] = data[5];
              vkp_body[s + 4] = data[2];
              vkp_body[s + 5] = data[3];
              vkp_body[s + 6] = data[0];
              vkp_body[s + 7] = data[1];
              vkp_body[s + 8] = '0';
              vkp_body[s + 9] = data[10];
              vkp_body[s +10] = data[8];
              vkp_body[s +11] = data[9];
              break; 
             }
           case 0x0C:
             {
              vkp_body[s + 0] = data[6];
              vkp_body[s + 1] = data[7];
              vkp_body[s + 2] = data[4];
              vkp_body[s + 3] = data[5];
              vkp_body[s + 4] = data[2];
              vkp_body[s + 5] = data[3];
              vkp_body[s + 6] = data[0];
              vkp_body[s + 7] = data[1];
              vkp_body[s + 8] = data[10];
              vkp_body[s + 9] = data[11];
              vkp_body[s +10] = data[8];
              vkp_body[s +11] = data[9];
              break; 
             }
           case 0x0D:
             {
              vkp_body[s + 0] = data[6];
              vkp_body[s + 1] = data[7];
              vkp_body[s + 2] = data[4];
              vkp_body[s + 3] = data[5];
              vkp_body[s + 4] = data[2];
              vkp_body[s + 5] = data[3];
              vkp_body[s + 6] = data[0];
              vkp_body[s + 7] = data[1];
              vkp_body[s + 8] = '0';
              vkp_body[s + 9] = data[12];
              vkp_body[s +10] = data[10];
              vkp_body[s +11] = data[11];
              vkp_body[s +12] = data[8];
              vkp_body[s +13] = data[9];
              break; 
             }
           case 0x0E:
             {
              vkp_body[s + 0] = data[6];
              vkp_body[s + 1] = data[7];
              vkp_body[s + 2] = data[4];
              vkp_body[s + 3] = data[5];
              vkp_body[s + 4] = data[2];
              vkp_body[s + 5] = data[3];
              vkp_body[s + 6] = data[0];
              vkp_body[s + 7] = data[1];
              vkp_body[s + 8] = data[12];
              vkp_body[s + 9] = data[13];
              vkp_body[s +10] = data[10];
              vkp_body[s +11] = data[11];
              vkp_body[s +12] = data[8];
              vkp_body[s +13] = data[9];
              break; 
             }
           case 0x0F:
             {
              vkp_body[s + 0] = data[6];
              vkp_body[s + 1] = data[7];
              vkp_body[s + 2] = data[4];
              vkp_body[s + 3] = data[5];
              vkp_body[s + 4] = data[2];
              vkp_body[s + 5] = data[3];
              vkp_body[s + 6] = data[0];
              vkp_body[s + 7] = data[1];
              vkp_body[s + 8] = '0';
              vkp_body[s + 9] = data[14];
              vkp_body[s +10] = data[12];
              vkp_body[s +11] = data[13];
              vkp_body[s +12] = data[10];
              vkp_body[s +13] = data[11];
              vkp_body[s +14] = data[8];
              vkp_body[s +15] = data[9];
              break; 
             }
           case 0x10:
             {
              vkp_body[s + 0] = data[6];
              vkp_body[s + 1] = data[7];
              vkp_body[s + 2] = data[4];
              vkp_body[s + 3] = data[5];
              vkp_body[s + 4] = data[2];
              vkp_body[s + 5] = data[3];
              vkp_body[s + 6] = data[0];
              vkp_body[s + 7] = data[1];
              vkp_body[s + 8] = data[14];
              vkp_body[s + 9] = data[15];
              vkp_body[s +10] = data[12];
              vkp_body[s +11] = data[13];
              vkp_body[s +12] = data[10];
              vkp_body[s +13] = data[11];
              vkp_body[s +14] = data[8];
              vkp_body[s +15] = data[9];
              break; 
             }
          }
         
                 
       }             
     }    
   }
  
  int k = 0, p = 0;
  for (int i = 0; k < vkp_size; i++,k++)
   {
     if (vkp_body[i] == 0x01) 
     {
      k--;  
      p++;
     }
      else vkp_body[k] = vkp_body[i];
   } 
       
  int ns = vkp_size - p;
  if (vkp_new_size) *vkp_new_size = ns;
  memset((char *)((unsigned int)vkp_body + ns), 0, vkp_size - ns);
  
  return RET_SUCCESS; 
}

int VKP_ToLowRegister(char *vkp_body, int vkp_size, int *vkp_new_size)
{
  if (vkp_new_size) *vkp_new_size = 0;
    
  if (!vkp_body)  return RET_VKPBODY_IS_NULL;
  if (!vkp_size)  return RET_VKPBODY_IS_NULL;
  
  for (int i = 0; i < vkp_size; i++)  
   {
    if (vkp_body[i] >= 'A' && vkp_body[i] <= 'Z')  vkp_body[i] = vkp_body[i] + 0x20;
    if (vkp_body[i] >= 'À' && vkp_body[i] <= 'ß')  vkp_body[i] = vkp_body[i] + 0x20;
    if (vkp_body[i] == '¨')  vkp_body[i] = '¸';
   }
   
  int k = 0, p = 0;
  for (int i = 0; k < vkp_size; i++,k++)
   {
     if (vkp_body[i] == 0x01) 
     {
      k--;  
      p++;
     }
      else vkp_body[k] = vkp_body[i];
   } 
       
  int ns = vkp_size - p;
  if (vkp_new_size) *vkp_new_size = ns;
  memset((char *)((unsigned int)vkp_body + ns), 0, vkp_size - ns);
  
  return RET_SUCCESS;
}

int VKP_ZapSymbolsCleaner(char *vkp_body, int vkp_size, int *vkp_new_size)
{
  if (vkp_new_size) *vkp_new_size = 0;
    
  if (!vkp_body)  return RET_VKPBODY_IS_NULL;
  if (!vkp_size)  return RET_VKPBODY_IS_NULL;
  
  for (int i = 0; i < vkp_size; i++)  
   {
    if (vkp_body[i] == ',')  vkp_body[i] = 0x01;
   }
   
  int k = 0, p = 0;
  for (int i = 0; k < vkp_size; i++,k++)
   {
     if (vkp_body[i] == 0x01) 
     {
      k--;  
      p++;
     }
      else vkp_body[k] = vkp_body[i];
   } 
       
  int ns = vkp_size - p;
  if (vkp_new_size) *vkp_new_size = ns;
  memset((char *)((unsigned int)vkp_body + ns), 0, vkp_size - ns);
  
  return RET_SUCCESS;
}

/* VKP FAIL DETECTOR */

int VKP_WrongSymbolsDetecter(char *vkp_body, int vkp_size)
{
  int nstrings = 0;
  
  if (!vkp_body)  return RET_VKPBODY_IS_NULL;
  if (!vkp_size)  return RET_VKPBODY_IS_NULL;
  
  //Get Info about number of strings
  for (int i = 0; i < vkp_size; i++) if (vkp_body[i] == '\n') nstrings++;
  
  VKP_STRING *vs = (VKP_STRING *)malloc(nstrings*sizeof(VKP_STRING));
  if (!vs) return RET_IS_NO_MEM;          

  for (int i = 0, k = 0; i < nstrings; i++) 
   { 
     vs[i].offset = k;
     while (k <= vkp_size)
      {
        if (vkp_body[k] == '\n' || k == vkp_size)  
         {
          vs[i].size = k - vs[i].offset;
          k++;
          break;
         }      
        k++; 
      }
   }
   
   //Parsing
   for (int i = 0; i < nstrings; i++) 
    {
      char *pstr = (char *)malloc(vs[i].size + 10); 
      if (!pstr)
        {
          free((void *)vs); 
          return RET_IS_NO_MEM;          
        }
      
      memcpy(pstr, (char *)((unsigned int)vkp_body + vs[i].offset),vs[i].size);
      pstr[vs[i].size] = '\0';
      
      //Get String pstr
      //lprintf("PATCH_STRING: %s\r\n", pstr); 
   
      switch  (pstr[0])
       {
        case '#':
          {
            if(!strcmp(pstr,"#pragma disable warn_no_old_on_apply"));       else
            if(!strcmp(pstr,"#pragma enable warn_no_old_on_apply"));        else
            if(!strcmp(pstr,"#pragma disable warn_if_new_exist_on_apply")); else
            if(!strcmp(pstr,"#pragma enable warn_if_new_exist_on_apply"));  else
            if(!strcmp(pstr,"#pragma disable warn_if_old_exist_on_undo"));  else
            if(!strcmp(pstr,"#pragma enable warn_if_old_exist_on_undo"));   else
            if(!strcmp(pstr,"#pragma disable undo"));                       else
            if(!strcmp(pstr,"#pragma enable undo"));                        else
            if(!strcmp(pstr,"#pragma enable old_equal_ff"));                else
            if(!strcmp(pstr,"#pragma disable old_equal_ff"));               else
             {
              free((void *)pstr);
              free((void *)vs); 
              return RET_UNK_PRAGMA;                       
             }
            break;
          } 
          
        case '+':
          {
           for (int s = 1; s < strlen(pstr); s++)
            {
               if ((pstr[s] >= '0' && pstr[s] <= '9') || (pstr[s] >= 'a' && pstr[s] <= 'f')) ;
               else
                {
                 free((void *)pstr);
                 free((void *)vs); 
                 return RET_WRONG_PLUS_OFFSET;       
                }   
            }
            
            break;       
          }    
          
       case '-':
          {
           for (int s = 1; s < strlen(pstr); s++)
            {
               if ((pstr[s] >= '0' && pstr[s] <= '9') || (pstr[s] >= 'a' && pstr[s] <= 'f')) ;
               else
                {
                 free((void *)pstr);
                 free((void *)vs); 
                 return RET_WRONG_MINUS_OFFSET;              
                }   
            }
             
            break;       
          }   
          
       default:
          {
           for (int s = 0; s < strlen(pstr); s++)
            {
               if (pstr[s] == ' ' || pstr[s] == ':' || (pstr[s] >= '0' && pstr[s] <= '9') || (pstr[s] >= 'a' && pstr[s] <= 'f')) ;
               else
                {
                 free((void *)pstr);
                 free((void *)vs); 
                 return RET_WRONG_STRING_SYMBOL;        
                }   
            }
            
            break;       
          } 
       }
        
       
       
      free((void *)pstr);
    }
  
  free((void *)vs);

  return RET_SUCCESS;
}



/* VKP MAIN PARSER */ 

int VKP_MainParser(char *vkp_body, int vkp_size, int VKP_ActionProc(unsigned int offset, int old_byte, int new_byte,
                                                            int warn_no_old_on_apply,
                                                            int warn_if_new_exist_on_apply,
                                                            int warn_if_old_exist_on_undo,
                                                            int undo
                                                            ))
{
  int nstrings = 0;
  //#pragma
  int pragma_warn_no_old_on_apply = 1;
  int pragma_warn_if_new_exist_on_apply = 1;
  int pragma_warn_if_old_exist_on_undo = 1;
  int pragma_undo = 1;
  int pragma_old_equal_ff = 0;
  //Offset + / -
  int global_offset_plus = 0;
  int global_offset_minus = 0;
  
  if (!vkp_body)  return RET_VKPBODY_IS_NULL;
  if (!vkp_size)  return RET_VKPBODY_IS_NULL;
  
  //Get Info about number of strings
  for (int i = 0; i < vkp_size; i++) if (vkp_body[i] == '\n') nstrings++;
  
  VKP_STRING *vs = (VKP_STRING *)malloc(nstrings*sizeof(VKP_STRING));
  if (!vs) return RET_IS_NO_MEM;          

  for (int i = 0, k = 0; i < nstrings; i++) 
   { 
     vs[i].offset = k;
     while (k <= vkp_size)
      {
        if (vkp_body[k] == '\n' || k == vkp_size)  
         {
          vs[i].size = k - vs[i].offset;
          k++;
          break;
         }      
        k++; 
      }
   }
   
   //Parsing
   for (int i = 0; i < nstrings; i++) 
    {
      char *pstr = (char *)malloc(vs[i].size + 10); 
      if (!pstr)
        {
          free((void *)vs); 
          return RET_IS_NO_MEM;          
        }
      
      memcpy(pstr, (char *)((unsigned int)vkp_body + vs[i].offset),vs[i].size);
      pstr[vs[i].size] = '\0';
      
      //Get String pstr
      //lprintf("PATCH_STRING: %s\r\n", pstr); 
   
      switch  (pstr[0])
       {
        case '#':
          {
            if(!strcmp(pstr,"#pragma disable warn_no_old_on_apply"))       pragma_warn_no_old_on_apply = 0; 
            if(!strcmp(pstr,"#pragma enable warn_no_old_on_apply"))        pragma_warn_no_old_on_apply = 1; 
            if(!strcmp(pstr,"#pragma disable warn_if_new_exist_on_apply")) pragma_warn_if_new_exist_on_apply = 0; 
            if(!strcmp(pstr,"#pragma enable warn_if_new_exist_on_apply"))  pragma_warn_if_new_exist_on_apply = 1; 
            if(!strcmp(pstr,"#pragma disable warn_if_old_exist_on_undo"))  pragma_warn_if_old_exist_on_undo = 0; 
            if(!strcmp(pstr,"#pragma enable warn_if_old_exist_on_undo"))   pragma_warn_if_old_exist_on_undo = 1; 
            if(!strcmp(pstr,"#pragma disable undo"))                       pragma_undo = 0; 
            if(!strcmp(pstr,"#pragma enable undo"))                        pragma_undo = 1; 
            if(!strcmp(pstr,"#pragma enable old_equal_ff"))                pragma_old_equal_ff = 1; 
            if(!strcmp(pstr,"#pragma disable old_equal_ff"))               pragma_old_equal_ff = 0; 
            break;       
          } 
          
        case '+':
          {
            unsigned int i = 0;
            sscanf(pstr + 1, "%x", &i);
            global_offset_plus = i;
            
            if (global_offset_plus > 0x00100000*256) // Offset very big
             {
              free((void *)pstr);
              free((void *)vs); 
              return RET_BIG_PLUS_OFFSET;                       
             }
            
            //lprintf("++++ 0x%08X\r\n", global_offset_plus);
            
            break;       
          }    
          
       case '-':
          {
            unsigned int i = 0;
            sscanf(pstr + 1, "%x", &i);
            global_offset_minus = i;
            
            if (global_offset_minus > 0x00100000*256) // Offset very small
             {
              free((void *)pstr);
              free((void *)vs); 
              return RET_BIG_MINUS_OFFSET;                       
             }
            
            //lprintf("--- 0x%08X\r\n", global_offset_minus); 
            
            break;       
          }   
          
       default:
          {
            //ADDRESS 
            int addr_sz = 0;
            char *addr_str = (char *)malloc(vs[i].size + 10); 
            if (!addr_str)
             {
               free((void *)vs); 
               free((void *)pstr); 
               return RET_IS_NO_MEM;          
             }
            
            strcpy(addr_str, pstr);
            while (addr_sz < strlen(pstr))
             {
              if (addr_str[addr_sz] == ':')
               {
                 addr_str[addr_sz] = '\0';
                 break;
               } else addr_sz++; 
             }
             
            unsigned int address = 0;
            sscanf(addr_str, "%x", &address);
            address += global_offset_plus;
            address -= global_offset_minus;
            
            free((void *)addr_str);
            
            if (address > 0x00100000*256) // Address very big
             {
               free((void *)vs); 
               free((void *)pstr); 
               return RET_BIG_ADDRESS;          
             }
            
            //lprintf("ADDRESS: 0x%08X\r\n", address); 
            
            //Check OLDDATA     
            int spaces = 0;
            for (int o = 0; o < strlen(pstr); o++)   if (pstr[o] == ' ') spaces++;     

            int  data_size = 0;
            char *old_data = 0; 
            char *new_data = 0; 

            if (spaces == 1) // No Old DATA
             {
              new_data = pstr + addr_sz + 2;
              data_size = strlen(new_data);
              
              if (data_size%2 != 0) // No parity data >>>>>>>>>>>>>>
               {
                free((void *)vs); 
                free((void *)pstr); 
                return RET_NOPARITY_DATA; 
               }
              
               for(int p = 0; p < data_size; p+=2)
                { 
                 int  old_byte;
                 int  new_byte;
                 unsigned int  paddress;      
                         
                 old_byte = -1;
                 
                 sscanf(new_data+p, "%02x", &new_byte);
                 if (pragma_old_equal_ff) old_byte = 0xFF;
                 
                 new_byte = new_byte&0xFF;
                      
                 paddress = address + p/2;
             
                 int der = VKP_ActionProc(paddress, old_byte, new_byte, pragma_warn_no_old_on_apply, 
                                                                        pragma_warn_if_new_exist_on_apply,
                                                                        pragma_warn_if_old_exist_on_undo,
                                                                        pragma_undo);
                 if (!der)
                  {
                   free((void *)vs); 
                   free((void *)pstr); 
                   return RET_ACTION_PROC_ERROR;       
                  }
                
                 //lprintf("ADDRESS: 0x%08X\r\nNEWBYTE: 0x%02X\r\n", paddress, new_byte); 
                }
             } else
                {
                 if (spaces == 2)  // Old DATA Exist
                   {
                    int od = addr_sz + 2;
                    while (od < strlen(pstr))
                     {
                      if (pstr[od] == ' ')
                       {
                        data_size = od - addr_sz - 2;
                        break;
                       } else od++; 
                     } 
                    
                    old_data = (char *)malloc(data_size + 10);
                    if (!old_data)
                     {
                        free((void *)vs); 
                        free((void *)pstr); 
                        return RET_IS_NO_MEM;          
                     }
                    
                    memcpy(old_data, pstr + addr_sz + 2, data_size);
                    old_data[data_size] = '\0';
                    
                    new_data = pstr + addr_sz + data_size + 3; 
                    
                    if(data_size%2 != 0)// No parity data >>>>>>>>>>>>>>
                     {
                      free((void *)vs); 
                      free((void *)pstr); 
                      free((void *)old_data);
                      return RET_NOPARITY_DATA; 
                     }
                     
                    if (strlen(new_data) != strlen(old_data)) // Len data old and new not equal >>>>>>>>>>>>>>
                     {
                      free((void *)vs); 
                      free((void *)pstr); 
                      free((void *)old_data);
                      return RET_OLD_NOT_EQU_NEW; 
                     }
                    
                    for(int p = 0; p < data_size; p+=2)
                     {
                      int  old_byte = 0;
                      int  new_byte = 0;
                      unsigned int  paddress = 0;
                      
                      sscanf(old_data+p, "%02x", &old_byte);
                      sscanf(new_data+p, "%02x", &new_byte);
                      
                      old_byte = old_byte&0xFF;
                      new_byte = new_byte&0xFF;
                      
                      paddress = address + p/2;
                      
                      int der = VKP_ActionProc(paddress, old_byte, new_byte, pragma_warn_no_old_on_apply, 
                                                                             pragma_warn_if_new_exist_on_apply,
                                                                             pragma_warn_if_old_exist_on_undo,
                                                                             pragma_undo);
                      if (!der)
                        {
                         free((void *)vs); 
                         free((void *)pstr); 
                         free((void *)old_data);
                         return RET_ACTION_PROC_ERROR;       
                        }
                      
                      //lprintf("ADDRESS: 0x%08X\r\nOLDBYTE: 0x%02X\r\nNEWBYTE: 0x%02X\r\n", paddress, old_byte, new_byte); 
                     }
                    
                    //lprintf("OLDDATA: %s\r\nNEWDATA: %s\r\nDATA SIZE: %d\r\n", old_data, new_data, data_size/2); 

                    free((void *)old_data);     
                   } else 
                       {
                        free((void *)vs); 
                        free((void *)pstr); 
                        return RET_NONEWDATA; 
                       } 
                }
            
            break;       
          } 
       }
        
       
       
      free((void *)pstr);
    }
  
  free((void *)vs);

  return RET_SUCCESS;
}






int VKP_Prepair(char *vkp_body, int vkp_size, int *vkp_new_size)
{
 int nsz = 0;      
 int err = 0;
 err = VKP_CommentsCleaner(vkp_body, vkp_size, &nsz);
 if (err == RET_SUCCESS)
  {
   err = VKP_VoidStringsCleaner(vkp_body, nsz, &nsz); 
   if (err == RET_SUCCESS)
    {
     /*        VKP_String2DumpConverter       */
     err = VKP_TabSymbolsCleaner(vkp_body, nsz, &nsz); 
     if (err == RET_SUCCESS)
      {
       err = VKP_ToLowRegister(vkp_body, nsz, &nsz); 
       if (err == RET_SUCCESS)
        {
         err = VKP_LongSpaceCleaner(vkp_body, nsz, &nsz); 
         if (err == RET_SUCCESS)
          {
           err = VKP_PostSpaceCleaner(vkp_body, nsz, &nsz); 
           if (err == RET_SUCCESS)
            {
             err = VKP_0xAddressCleaner(vkp_body, nsz, &nsz); 
             if (err == RET_SUCCESS)
              {
               /*        VKP_Int2HexConverter           */
               err = VKP_Hex2DumpConverter(vkp_body, nsz, &nsz); 
               if (err == RET_SUCCESS)
                {
                 err = VKP_ZapSymbolsCleaner(vkp_body, nsz, &nsz); 
                 if (err == RET_SUCCESS) 
                  {
                   *vkp_new_size = nsz;
                    return VKP_WrongSymbolsDetecter(vkp_body, nsz); 
                   }
                 }
               }
             }
          }
         }
       }
     }
   }
         
 return err;
}


int VKP_Parse(char *vkp_body, int vkp_size, int VKP_ActionProc(unsigned int offset, int old_byte, int new_byte,
                                                            int warn_no_old_on_apply,
                                                            int warn_if_new_exist_on_apply,
                                                            int warn_if_old_exist_on_undo,
                                                            int undo
                                                            ))
{
 int nsz = 0;
 int err = VKP_Prepair(vkp_body, vkp_size, &nsz);
 if (err == RET_SUCCESS) return VKP_MainParser(vkp_body, nsz, VKP_ActionProc);
 else return err;
}


