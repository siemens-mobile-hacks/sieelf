#include "..\inc\swilib.h"

#define ANTIHACK_DISABLE
#define ANTIHACK_ID 0xDACADA
#define elf_exit() SUBPROC((void*)kill_data,__segment_begin("ELFBEGIN"),(void (*)(void *))mfree_adr());

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

void kill_data( void * p, void(*fptr)(void *));

void maincsm_oncreate(CSM_RAM *data);
void maincsm_onclose(CSM_RAM *csm);
int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg);


