#ifdef	E71Csw41
#define GBS_SendMessage_adr	0xA0091EAB
#define DO_IME_BACK		0xA0B1F172+1 //
#define DO_RIGHT		0xA0B1F37E+1 //输入状态已检测
#define	DO_DOWN			0xA0B1F45C+1 //输入状态已检测
#define	DO_SELECT		0xA0B1F248+1 //
#define DO_DIRECT_SELECT	0xA0B1F6D0+1 //只能在非JAVA中使用
#define DO_NOTHING		0xA0B1F55A+1 //不做任何改变
#define	DO_KEY1_BACK		0xA0B1F77C+1 //1键返回
#define	JAVA_EDIT_KOP		0xA8EB0A30   //在JAVA中,这个地址不变
#define	USE_RAM			0xA8D805C0   //4字节,用于存储JAVA中输入法选择菜单状态
#endif

