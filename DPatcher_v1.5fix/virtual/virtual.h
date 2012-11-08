
#define ADD_SIZE  0x1000
#define MALIGN(A) (((int)A&0xFFFFF000) + 0x1000)


void *virtual2physical(void *addr);
int RelocateFAddresToRAM(void *addr);



