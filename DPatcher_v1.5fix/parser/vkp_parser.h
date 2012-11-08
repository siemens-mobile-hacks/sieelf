


typedef struct{
 int offset;
 int size;        
}VKP_STRING;


#define RET_SUCCESS              1

#define RET_VKPBODY_IS_NULL      0
#define RET_UNK_PRAGMA          -1
#define RET_WRONG_PLUS_OFFSET   -2
#define RET_WRONG_MINUS_OFFSET  -3
#define RET_WRONG_STRING_SYMBOL -4
#define RET_BIG_PLUS_OFFSET     -5
#define RET_BIG_MINUS_OFFSET    -6
#define RET_BIG_ADDRESS         -7
#define RET_NOPARITY_DATA       -8
#define RET_OLD_NOT_EQU_NEW     -9
#define RET_IS_NO_MEM           -10
#define RET_ACTION_PROC_ERROR   -11
#define RET_NONEWDATA           -12
#define RET_HEXVALUE_IS_NULL    -13

int VKP_CommentsCleaner(char *vkp_body, int vkp_size, int *vkp_new_size);
int VKP_VoidStringsCleaner(char *vkp_body, int vkp_size, int *vkp_new_size);
int VKP_TabSymbolsCleaner(char *vkp_body, int vkp_size, int *vkp_new_size);
int VKP_PostSpaceCleaner(char *vkp_body, int vkp_size, int *vkp_new_size);
int VKP_LongSpaceCleaner(char *vkp_body, int vkp_size, int *vkp_new_size);
int VKP_0xAddressCleaner(char *vkp_body, int vkp_size, int *vkp_new_size);
int VKP_Hex2DumpConverter(char *vkp_body, int vkp_size, int *vkp_new_size);
int VKP_ToLowRegister(char *vkp_body, int vkp_size, int *vkp_new_size);
int VKP_WrongSymbolsDetecter(char *vkp_body, int vkp_size);
int VKP_MainParser(char *vkp_body, int vkp_size, int VKP_ActionProc(unsigned int offset, int old_byte, int new_byte,
                                                            int warn_no_old_on_apply,
                                                            int warn_if_new_exist_on_apply,
                                                            int warn_if_old_exist_on_undo,
                                                            int undo
                                                            ));

int VKP_Prepair(char *vkp_body, int vkp_size, int *vkp_new_size);
int VKP_Parse(char *vkp_body, int vkp_size, int VKP_ActionProc(unsigned int offset, int old_byte, int new_byte,
                                                            int warn_no_old_on_apply,
                                                            int warn_if_new_exist_on_apply,
                                                            int warn_if_old_exist_on_undo,
                                                            int undo
                                                            ));



