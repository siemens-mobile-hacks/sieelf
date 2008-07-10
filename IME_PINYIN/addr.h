#ifdef	E71Csw41
#define GBS_SendMessage_adr	0xA0091EAB
#define DO_IME_BACK		0xA0B1F172+1 //
#define DO_RIGHT		0xA0B1F37E+1 //输入状态已检测
#define	DO_LEFT			0xA0B1F314+1
#define	DO_DOWN			0xA0B1F45C+1 //输入状态已检测
#define	DO_UP			0xA0B1F43A+1
#define	DO_SELECT		0xA0B1F248+1 //
#define DO_DIRECT_SELECT	0xA0B1F6D0+1 //只能在非JAVA中使用
#define DO_NOTHING		0xA0B1F55A+1 //不做任何改变
#define	DO_KEY1_BACK		0xA0B1F77C+1 //1键返回
#define	JAVA_EDIT_KOP		0xA8EB0A30   //在JAVA中,这个地址不变
#define	USE_RAM			0xA8D805C0   //4字节,用于存储JAVA中输入法选择菜单状态
#define DO_XING_FIX		0xA06EEAE8+1 //解决*键在JAVA中选字状态向右无用问题
#define	GET_INPUT_STATE		0xA06EF026+1 //获取输入状态,1为等待输入,0为拼音选择或选字状态
#define	KEY0_FUNC1		0xA06EDDC6+1 //0键跳转位置的一个函数,返回时要先执行这个函数
#define	KEY0_BACK		0xA06EF1DC+1 //0键跳转返回地址
#define	KEY0_GOTO_IME		0xA06EF1EC+1 //0键跳转向常规输入
#endif

