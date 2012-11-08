
#define FLASH_BASE			0xA0000000
#define FLASH_BASE_MASK			0xB0000000

#define FLASH_BUS_16(O)			*((unsigned short *)(O))
#define FLASH_BUS_16_MUL		0x02

#define FLASH_CMD_CFI			0x98
#define FLASH_CMD_READ_ID		0x90
#define FLASH_CMD_RESET			0xFF
#define FLASH_CMD_BLOCK_ERASE		0x20
#define FLASH_CMD_ERASE_CONFIRM		0xD0
#define FLASH_CMD_WRITE			0x40
#define FLASH_CMD_PROTECT		0x60
#define FLASH_CMD_PROTECT_SET		0x01
#define FLASH_CMD_PROTECT_CLEAR		0xD0
#define FLASH_CMD_CLEAR_STATUS		0x50
#define FLASH_CMD_WRITE_TO_BUFFER	0xE8 //0xE8
#define FLASH_CMD_WRITE_TO_BUFFER_ALT	0xE9
#define FLASH_CMD_WRITE_BUFFER_CONFIRM	0xD0
#define FLASH_CMD_READ_STATUS           0x70

#define FLASH_STATUS_DONE		0x80
#define FLASH_STATUS_ESS		0x40
#define FLASH_STATUS_ECLBS		0x20
#define FLASH_STATUS_PSLBS		0x10
#define FLASH_STATUS_VPENS		0x08
#define FLASH_STATUS_PSS		0x04
#define FLASH_STATUS_DPS		0x02
#define FLASH_STATUS_R			0x01
#define FLASH_STATUS_PROTECT		0x01

#define AMD_CMD_RESET			0xF0
#define AMD_CMD_UNLOCK_BYPASS_ENTRY	0x20
#define AMD_CMD_UNLOCK_BYPASS_ENTRY_ALT	0xE0
#define AMD_CMD_WRITE			0xA0
#define AMD_CMD_ERASE_START		0x80
#define AMD_CMD_ERASE_SECTOR		0x30
#define AMD_CMD_UNLOCK_START		0xAA
#define AMD_CMD_UNLOCK_ACK		0x55
#define AMD_CMD_WRITE_TO_BUFFER		0x25
#define AMD_CMD_WRITE_BUFFER_CONFIRM	0x29
#define AMD_CMD_ZERO      	        0x00
#define AMD_CMD_ONE      	        0x01


#define AMD_STATUS_TOGGLE		0x40
#define AMD_STATUS_ERROR		0x20

#define FLASH_OFFSET_UNK          	0x2AA

#define FLASH_OFFSET_MANUFACTURER_ID	0x00
#define FLASH_OFFSET_DEVICE_ID		0x01
#define FLASH_OFFSET_DEVICE_ID2		0x0E
#define FLASH_OFFSET_DEVICE_ID3		0x0F
#define FLASH_OFFSET_CFI		0x55
#define FLASH_OFFSET_CFI_ALT		0x555
#define FLASH_OFFSET_CFI_RESP		0x10
#define FLASH_OFFSET_PRIMARY_VENDOR	0x13
#define FLASH_OFFSET_TYPE_WRITE 	0x14
#define FLASH_OFFSET_EXT_QUERY_T_P_ADDR	0x15	/* extended query table primary addr */
#define FLASH_OFFSET_WTOUT		0x1F
#define FLASH_OFFSET_WBTOUT		0x20
#define FLASH_OFFSET_ETOUT		0x21
#define FLASH_OFFSET_CETOUT		0x22
#define FLASH_OFFSET_WMAX_TOUT		0x23
#define FLASH_OFFSET_WBMAX_TOUT		0x24
#define FLASH_OFFSET_EMAX_TOUT		0x25
#define FLASH_OFFSET_CEMAX_TOUT		0x26
#define FLASH_OFFSET_SIZE		0x27
#define FLASH_OFFSET_INTERFACE		0x28
#define FLASH_OFFSET_BUFFER_SIZE	0x2A
#define FLASH_OFFSET_NUM_ERASE_REGIONS	0x2C
#define FLASH_OFFSET_ERASE_REGIONS	0x2D
#define FLASH_OFFSET_PROTECT		0x02
#define FLASH_OFFSET_USER_PROTECTION	0x85
#define FLASH_OFFSET_INTEL_PROTECTION	0x81
#define FLASH_OFFSET_ZERO       	0x00

#define MAN_FLASH_NOSUP                 0x0090

#define MAN_AMD                         0x0001
#define MAN_FUJITSU                     0x0004
#define MAN_ATMEL                       0x001F
#define MAN_ST                          0x0020
#define MAN_INTEL                       0x0089 
#define MAN_TOSHIBA                     0x0098
#define MAN_SST                         0x00BF 
#define MAN_MACRONIX                    0x00C2 

#define MAN_AM29F800BB_1                0x2218
#define MAN_AM29F800BB_2                0x2258 
#define MAN_AM29LV800BB                 0x225B
#define MAN_AM29F800BT                  0x22D6 

#define MAN_MBM29LV650UE                0x22D7 
#define MAN_MBM29LV320TE                0x22F6



#define true   1
#define false  0

typedef struct {
   unsigned short man_id;
   unsigned short dev_id;
   unsigned short dev_id2;
   unsigned short dev_id3;
   unsigned int   f_size; 
   unsigned int   b_size; 
   unsigned short wtype; 
   unsigned short alt_work; 
   unsigned short num_er; 
   unsigned short er; 
}FLASH_INFO;

void flash_get_info(FLASH_INFO *f_info, unsigned int flash_base);

void flash_erase_block_intel(void *addr_block);
void flash_write_word_intel(void *addr_word, unsigned short word);
void flash_write_buf_intel(void *address, unsigned short *buffer, short buffer_size);
void flash_write_buf_ext_intel(void *address, unsigned short *buffer, unsigned short buffer_size, unsigned int block_size, int wtype);

int flash_erase_block_amd(void *addr_block);
int flash_write_word_amd(void *address, unsigned short word, unsigned int block_size);
void flash_write_block_ext_amd(void *addr_block, unsigned short *block, unsigned int block_size);
