
#ifndef _extern_H_
#define _extern_H_

unsigned short* Opendata(char *recname);
int runFile(char *file);
void Play(const char *fpath, const char *fname);
void copy_unicode_2ws(WSHDR* ws, unsigned short* unicode,int x);

#endif
