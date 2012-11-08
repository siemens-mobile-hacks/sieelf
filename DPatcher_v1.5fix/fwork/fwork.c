#include "..\..\inc\swilib.h"
#include "fwork.h"

char file_add_buffer[FILE_ADDBUFFER_SIZE];
unsigned int file_add_buffer_size = 0;

int file_exists(const char *fname)
{
  int handle;
  unsigned int err;
  handle = fopen(fname, A_ReadOnly, P_READ, &err);
  if (handle == -1)
    return 0;
  fclose(handle, &err);
  return 1;
}

int get_file_size(char *fname)
{
  if (!file_exists(fname)) return -1;
  FSTATS stats;
  unsigned int err;
  if (GetFileStats(fname, &stats, &err)) return -1;
  return (stats.size);
}


void *LoadFile(char *fname, unsigned int *size)
{
  if (file_exists(fname) == 1)
   {
    int sz = get_file_size(fname);
    void *fbuf = malloc(sz);
    if (fbuf)
     {
      int bfile = fopen(fname,A_ReadWrite+A_BIN,P_READ,0);
      fread(bfile,fbuf,sz,0);
      fclose(bfile,0);
     } else
        {
         *size = 0;
         return 0;
        }
    *size = sz;
    return fbuf;
   }
  
  *size = 0;
  return 0;
}

int SaveFile(char *fname, void *p, unsigned int size)
{
  if (file_exists(fname) == 1) unlink(fname, 0);
  int bfile = fopen(fname,A_ReadWrite+A_Create+A_BIN,P_READ+P_WRITE,0);
  fwrite(bfile,p,size,0);
  fclose(bfile,0);  
  return 1;
}

int DoSaveFile(char *fname, void *p, unsigned int size)
{
  if (file_exists(fname) == 0) 
   {
    int bfile = fopen(fname,A_ReadWrite+A_Create+A_BIN,P_READ+P_WRITE,0);
    fwrite(bfile,p,size,0);
    fclose(bfile,0);  
    return 0;
   } else
     {
      int bfile = fopen(fname,A_ReadWrite+A_Create+A_Append+A_BIN,P_READ+P_WRITE,0);
      lseek(bfile, 0x0, S_END, 0, 0);
      fwrite(bfile,p,size,0);
      fclose(bfile,0);  
      return 0;
     }
}

int DoSaveFileWithBuffer(char *fname, void *p, unsigned int size)
{
  if (p)
   {
    if (size)
     {
      if (file_add_buffer_size + size >= FILE_ADDBUFFER_SIZE)
       {
        DoSaveFile(fname, file_add_buffer, file_add_buffer_size);
        file_add_buffer_size = 0;
        memcpy(file_add_buffer, p, size);
        file_add_buffer_size += size;
       } else
         {
          memcpy((char *)((unsigned int)file_add_buffer + file_add_buffer_size), p, size);
          file_add_buffer_size += size;
         }
     }
   }
 return 0;
}

int DoSaveFileFromBuffer(char *fname)
{
 DoSaveFile(fname, file_add_buffer, file_add_buffer_size);
 file_add_buffer_size = 0;
 return 0;
}

void DeleteFile(char *fname)
{
  if (file_exists(fname) == 1) unlink(fname, 0);
}



