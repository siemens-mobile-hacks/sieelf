
#define FILE_PRINTF_SIZE  4*1024
#define FILE_ADDBUFFER_SIZE  64*1024

int file_exists(const char *fname);
int get_file_size(char *fname);

void *LoadFile(char *fname, unsigned int *size);
int   SaveFile(char *fname, void *p, unsigned int size);
int   DoSaveFile(char *fname, void *p, unsigned int size);
int   DoSaveFileWithBuffer(char *fname, void *p, unsigned int size);
int   DoSaveFileFromBuffer(char *fname);
void  DeleteFile(char *fname);

void fpclear(char *filename);
void fprintf(char *filename, char *format, ...);
void fbprintf(char *filename, char *format, ...);
void fbflush(char *filename);

