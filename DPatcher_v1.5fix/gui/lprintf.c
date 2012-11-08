#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "lprintf.h"


void lprintf(char *format, ...)
{
  char out_buf[LOG_PRINTF_SIZE]; 
   
  va_list arg_ptr;
  va_start(arg_ptr, format);
  vsprintf(out_buf, format, arg_ptr);
  va_end(arg_ptr);
        
  lprint(out_buf);     
}

