
#ifdef E71Csw41
#define	DO_DIRECT_SELECT	0xA0B214E6+1
#define	DO_START_SELECT		0xA0B2113C+1
#define	DO_EBACK		0xA0B20FF8+1
#define	DO_NOTHING		0xA0B211FA+1
#define	WGET_KBS_KSTATE		0xA0A49F4E+1 //1:ON, 0:OFF
#define	UNK_RAM_adr		0xA8EBCA10 //�������ж��Ƿ��ڱ༭״̬
#define	WSET_KBS_KSTATE		0xA0A49CB0+1
#define	DO_SELECT_EBACK		0xA0B21678+1
#define	KDB_KPOP_FUNC1_RAM	0xA8F2BED0
#define	KDB_KPOP_EBACK		0xA06EF290+1
#define	KDB_KPOP_EBNE_adr	0xA06EF328+1

/* ���²��ֺ�ƴ�����뷨�޸� v1.x �е�һ�� */
#define GBS_SendMessage_adr	0xA0091EAB
#define	JAVA_EDIT_KOP		0xA8EB0A30
#define	USE_RAM			0xA8D805C0   //�հ�RAM,4�ֽ�,��ƴ�����뷨�޸�v1.x��һ��
#define	GET_INPUT_STATE		0xA06EF026+1 //��ȡ����״̬,1Ϊ�ȴ�����,0Ϊƴ��ѡ���ѡ��״̬
#define	KEY0_FUNC1		0xA06EDDC6+1 //0����תλ�õ�һ������,����ʱҪ��ִ���������
#define	KEY0_BACK		0xA06EF1DC+1 //0����ת���ص�ַ
#define	KEY0_GOTO_IME		0xA06EF1EC+1 //0����ת�򳣹�����

#endif

#ifdef ELC1sw41
#define	DO_DIRECT_SELECT	0xA0B28D6E+1
#define	DO_START_SELECT		0xA0B289C4+1
#define	DO_EBACK		0xA0B28880+1
#define	DO_NOTHING		0xA0B27BA2+1
#define	WGET_KBS_KSTATE		0xA0A50736+1 //1:ON, 0:OFF
#define	UNK_RAM_adr		0xA8EBC98C //�������ж��Ƿ��ڱ༭״̬
#define	WSET_KBS_KSTATE		0xA0A50498+1
#define	DO_SELECT_EBACK		0xA0B28F00+1
#define	KDB_KPOP_FUNC1_RAM	0xA8F2B658
#define	KDB_KPOP_EBACK		0xA06F6BBC+1
#define	KDB_KPOP_EBNE_adr	0xA06F6C54+1

/* ���²��ֺ�ƴ�����뷨�޸� v1.x �е�һ�� */
#define GBS_SendMessage_adr	0xA0091EAB
#define	JAVA_EDIT_KOP		0xA8EB0730   //��JAVA��,�����ַ����
#define	USE_RAM			0xA8D805C0   //4�ֽ�,���ڴ洢JAVA�����뷨ѡ��˵�״̬
#define	GET_INPUT_STATE		0xA06F6952+1 //��ȡ����״̬,1Ϊ�ȴ�����,0Ϊƴ��ѡ���ѡ��״̬
#define	KEY0_FUNC1		0xA06F56F2+1 //0����תλ�õ�һ������,����ʱҪ��ִ���������
#define	KEY0_BACK		0xA06F6B08+1 //0����ת���ص�ַ
#define	KEY0_GOTO_IME		0xA06F6B18+1 //0����ת�򳣹�����

#endif
