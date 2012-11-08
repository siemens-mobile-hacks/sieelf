#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "fwork.h"


void fpclear(char *filename)
{   
  DeleteFile(filename); 
}

void fprintf(char *filename, char *format, ...)
{
  char out_buf[FILE_PRINTF_SIZE]; 
   
  va_list arg_ptr;
  va_start(arg_ptr, format);
  vsprintf(out_buf, format, arg_ptr);
  va_end(arg_ptr);
        
  DoSaveFile(filename, out_buf, strlen(out_buf)); 
}

void fbprintf(char *filename, char *format, ...)
{
  char out_buf[FILE_PRINTF_SIZE]; 
   
  va_list arg_ptr;
  va_start(arg_ptr, format);
  vsprintf(out_buf, format, arg_ptr);
  va_end(arg_ptr);
        
  DoSaveFileWithBuffer(filename, out_buf, strlen(out_buf)); 
}

void fbflush(char *filename)
{   
  DoSaveFileFromBuffer(filename); 
}

