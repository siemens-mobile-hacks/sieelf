//SGoldһЩ������,ûд�Ŀ�����swilib.vkp�ҵ�
//WS_InitByZero = CreateLocalWS
//atou 002200E0013001780B1C093B042B
//GetCalleeNumber 70B5041C0E1CA0B0
//UpdateWndItem B0B500680D1C91004018C4680021201C
//ADDRBook F8B50027051C0C1C002817D0
//SMS_SEND F7B584B0051C059800270290
//SELECT_MENU 002374E7F7B5FFB0151C83B0
/*����MENU_DESC��ַ����
�Ȳ���80B50223C95E0022052901D0��õ�ַ��Ȼ���ַ+1
�ѵ�ַ���ֽ�������ң��õ�����һ����ַ����ȥ4����
*/
//CallIN ????????????70B5061C01200C1C4002
//CallOUT 3078042811D1????????00280DD0
//SMS_SEND_HOOK 0022391C281C????????281C????????251C
//NUM_SELECT_MENU_HOOK 01a9????????01A8????????01300204120c �õ���ַ+2
//NUM_SELECT_MENU_HOOK1 041C??49????????291C201C
//SMS_IN_HOOK 201c??????????49201C????????0021201C????????0121201C �õ���ַ+8
//READ_SMS_HOOK 0A21201C????????2A1C211C

#ifdef CX7Av25
#define ADDR_strlen		0xA0E98C64+1//OK
#define ADDR_atou		0xA020EB00+1//OK
#define ADDR_WS_InitByZero	0xA07899D2+1//OK
#define ADDR_GetCalleeNumber	0xA0797F2A+1//OK
#define ADDR_UpdateWndItem	0xA00B59A2+1//OK
#define ADDR_memcmp		0xA0E97F1C+1//OK
#define ADDR_DrawString		0xA00DC5BC+1//OK
#define ADDR_FreeWS		0xA078936C+1//OK
#define ADDR_AllocWS		0xA0789A3A+1//OK
#define ADDR_GetCurMenuItem	0xA009C0A2+1//OK

#define ADDR_wstrcat		0xA0789BA0+1//OK
#define ADDR_wsAppendChar	0xA0789CC8+1//OK
#define ADDR_IsCalling		0xA00CECDE+1//OK
#define ADDR_CallIN		0xA033D766+1//OK
#define ADDR_CallOUT		0xA033A8A6+1//OK
#define ADDR_ADDRBook		0xA078A1D0+1//OK
#define ADDR_SMS_SEND		0xA0835F70+1//OK

#define UNUSERAM_NUM		0xA8000240
#define UNUSERAM_METHOD		0xA8000300
#define UNUSERAM_OLD_REDRAW	0xA80002F0
#define ADDR_SELECT_MENU	0xA07F31D8+1//OK
#define ADDR_MENU_DESC		0xA077FEB8 //OK

#define ADDR_IncommingPDU	0xA8767F6C //OK

#define BASEADDRESS		0xA0F294B0 //OK
#endif

#ifdef CX7Cv50
#define ADDR_strlen		0xA1F37014+1//OK
#define ADDR_atou		0xA082BD88+1//OK
#define ADDR_WS_InitByZero	0xA11C23BE+1//OK
#define ADDR_GetCalleeNumber	0xA1005DDA+1//OK
#define ADDR_UpdateWndItem	0xA00B5122+1//OK
#define ADDR_memcmp		0xA1F362CC+1//OK
#define ADDR_DrawString		0xA00DAC24+1//OK
#define ADDR_FreeWS		0xA11C1D70+1//OK
#define ADDR_AllocWS		0xA11C2426+1//OK
#define ADDR_GetCurMenuItem	0xA009BD0A+1//OK

#define ADDR_wstrcat		0xA11C258C+1//OK
#define ADDR_wsAppendChar	0xA11C26B4+1//OK
#define ADDR_IsCalling		0xA00CDB32+1//OK
#define ADDR_CallIN		0xA0966EE2+1//OK
#define ADDR_CallOUT		0xA09662B0+1//OK
#define ADDR_ADDRBook		0xA11C2BBC+1//OK
#define ADDR_SMS_SEND		0xA12204E4+1//OK

#define UNUSERAM_NUM		0xA8000240
#define UNUSERAM_METHOD		0xA8000300
#define UNUSERAM_OLD_REDRAW	0xA80002F0
#define ADDR_SELECT_MENU	0xA11F1F2C+1//OK
#define ADDR_MENU_DESC		0xA0BA9DD0 //OK

#define BASEADDRESS		0xA0E55A00
#endif

#ifdef M6Cv50
#define ADDR_strlen		0xA159BB38+1
#define ADDR_atou		0xA082BD88+1
#define ADDR_WS_InitByZero      0xA0A55262+1
#define ADDR_GetCalleeNumber    0xA0A634EE+1
#define ADDR_UpdateWndItem	0xA00B4D62+1
#define ADDR_memcmp		0xA159B178+1
#define ADDR_DrawString		0xA00DA864+1
#define ADDR_FreeWS             0xA0A55306+1
#define ADDR_AllocWS            0xA0A552CA+1
#define ADDR_GetCurMenuItem	0xA009B914+1

#define ADDR_wstrcat            0xA0A55430+1
#define ADDR_wsAppendChar       0xA0A55558+1
#define ADDR_IsCalling		0xA00CD772+1
#define ADDR_CallIN		0xA0974F2A+1
#define ADDR_CallOUT		0xA09742F8+1
#define ADDR_ADDRBook           0xA0A55A60+1
#define ADDR_SMS_SEND           0xA0AF7E58+1
#define BASEADDRESS		0xA0C61220
#define UNUSERAM_NUM		0xA8000240
#define UNUSERAM_METHOD		0xA8000300
#define UNUSERAM_OLD_REDRAW	0xA80002F0
#define ADDR_SELECT_MENU        0xA0ABF1FC+1
#define ADDR_MENU_DESC          0xA0C5E4C0

#define ADDR_IncommingPDU	0xA873AA8C

#endif

#ifdef CX6Cv50
#define ADDR_strlen		0xA159BF14+1//
#define ADDR_atou		0xA082BD88+1//
#define ADDR_WS_InitByZero	0xA0A55266+1//
#define ADDR_GetCalleeNumber	0xA0A634F2+1//
#define ADDR_UpdateWndItem	0xA00B4D5E+1//
#define ADDR_memcmp		0xA159B554+1//
#define ADDR_DrawString		0xA00DA860+1//
#define ADDR_FreeWS		0xA0A54C18+1//
#define ADDR_AllocWS		0xA0A552CE+1//
#define ADDR_GetCurMenuItem	0xA009B946+1//

#define ADDR_wstrcat		0xA0A55434+1//
#define ADDR_wsAppendChar	0xA0A5555C+1//
#define ADDR_IsCalling		0xA00CD76E+1//
#define ADDR_CallIN		0xA0974F2A+1//
#define ADDR_CallOUT		0xA09742F8+1//
#define ADDR_ADDRBook		0xA0A55A64+1//
#define ADDR_SMS_SEND		0xA0AF7E60+1//

#define UNUSERAM_NUM		0xA8000240
#define UNUSERAM_METHOD		0xA8000300
#define UNUSERAM_OLD_REDRAW	0xA80002F0
#define ADDR_SELECT_MENU	0xA0ABF204+1//
#define ADDR_MENU_DESC		0xA0C5E0F0 //

#define ADDR_IncommingPDU	0xA873AC0C

#define BASEADDRESS		0xA0CC0000
#endif

#ifdef S6Cv53
#define ADDR_strlen		0xA1609C0C+1
#define ADDR_atou		0xA082BD88+1
#define ADDR_WS_InitByZero	0xA10010C2+1
#define ADDR_GetCalleeNumber	0xA0A9650A+1
#define ADDR_UpdateWndItem	0xA00B4F3E+1
#define ADDR_memcmp		0xA160924C+1
#define ADDR_DrawString		0xA00DAA40+1
#define ADDR_FreeWS		0xA1000A74+1
#define ADDR_AllocWS		0xA100112A+1
#define ADDR_GetCurMenuItem	0xA009BB26+1

#define ADDR_wstrcat		0xA1001290+1
#define ADDR_wsAppendChar	0xA10013B8+1
#define ADDR_IsCalling		0xA00CD94E+1
#define ADDR_CallIN		0xA098FE1A+1
#define ADDR_CallOUT		0xA098F1D4+1
#define ADDR_ADDRBook		0xA10018C0+1
#define ADDR_SMS_SEND		0xA101FE58+1
#define UNUSERAM_NUM		0xA8000240
#define UNUSERAM_METHOD		0xA8000300
#define UNUSERAM_OLD_REDRAW	0xA80002F0
#define ADDR_SELECT_MENU	0xA0B06B0C+1
#define ADDR_MENU_DESC		0xA0CAE0E8

#define ADDR_IncommingPDU	0xA87A092C

#define BASEADDRESS		0xA0CC0000
#endif

#ifdef E71Cv41
#define ADDR_strlen		0xA0FF1BFC+1
#define ADDR_atou		0xA0643348+1
#define ADDR_WS_InitByZero	0xA051072E+1
#define ADDR_GetCalleeNumber	0xA094D15E+1
#define ADDR_UpdateWndItem	0xA0A4EA4C+1
#define ADDR_memcmp		0xA0FF0DA4+1
//#define ADDR_DrawString		0xA0970C52+1
//#define ADDR_FreeWS		0xA0510058+1
#define ADDR_AllocWS		0xA0965EB4+1
//#define ADDR_GetCurMenuItem	0xA097931A+1
#define ADDR_IncommingPDU	0xA8F1F6BC
//#define ADDR_wstrcat		0xA05108E4+1
#define ADDR_wsAppendChar	0xA05109AC+1
#define ADDR_IsCalling		0xA0D0CF80+1

#define ADDR_CallIN		0xA067DACC+1
//#define ADDR_CallOUT		0xA067DDAC+1
#define ADDR_ADDRBook		0xA0510D1A+1
#define ADDR_GetPhoneBookNum	0xA09546FE+1
#define BASEADDRESS		0xA1580000
//#define ADDR_CREATE_SELECT_MENU	0xA097A63A+1
//#define ADDR_MENU_DESC		0xA08D3474
//#define UNUSERAM_NUM		0xA8D80800
//#define UNUSERAM_METHOD		0xA8D808E0
//#define UNUSERAM_OLD_REDRAW	0xA8D808D0
#define	AllocMLMenuItem_adr	0xA08198E4
#define GetMLMenuGUI_adr	0xA0819FB8
#define ADDR_CallOUT2		0xA0ACACCA+1
#define AllocMenuWS_adr		0xA097ABFD
#define SetMLMenuItemText_adr	0xA097DDBF
#endif


#ifdef ELC1v41
#define ADDR_strlen 0xA0FFCF8C+1
#define ADDR_atou 0xA06471E4+1
#define ADDR_WS_InitByZero	0xA05162CA+1
#define ADDR_GetCalleeNumber	0xA095391E+1
#define ADDR_UpdateWndItem	0xA0A55234+1
#define ADDR_memcmp	0xA0FFC134+1
//#define ADDR_DrawString		0xA0977412+1
//#define ADDR_FreeWS		    0xA0515BF4+1
#define ADDR_AllocWS		0xA096C674+1
//#define ADDR_GetCurMenuItem	0xA097FADA+1
#define ADDR_IncommingPDU	0xA8F1EF70  
//#define ADDR_wstrcat 0xA0C4D128
#define ADDR_wsAppendChar 0xA0C4D09C
#define ADDR_IsCalling 0xA0D158C8+1

#define ADDR_CallIN 0xA0681B64+1
//#define ADDR_CallOUT 0xA0681E44+1
#define ADDR_ADDRBook 0xA05168B6+1
#define ADDR_GetPhoneBookNum 0xA095AEBE+1 ;//90b50c1c8bb06946
#define BASEADDRESS			0xA1580000
//#define ADDR_CREATE_SELECT_MENU	0xA0980DFA+1
//#define ADDR_MENU_DESC		0xA08D2F34
//#define UNUSERAM_NUM		0xA8D80800
//#define UNUSERAM_METHOD		0xA8D808E0
//#define UNUSERAM_OLD_REDRAW	0xA8D808D0
#define	AllocMLMenuItem_adr	0xA081A860
#define GetMLMenuGUI_adr	0xA081AE80
#define ADDR_CallOUT2		0xA0AD2552+1
#define AllocMenuWS_adr		0xA09813BD
#define SetMLMenuItemText_adr	0xA098457F
#endif


#ifdef S7Cv47
#define ADDR_strlen		0xA14270BC+1
#define ADDR_atou		0xA02C6AA0+1
#define ADDR_WS_InitByZero	0xA01F7A76+1
#define ADDR_GetCalleeNumber	0xA09833EE+1
#define ADDR_UpdateWndItem	0xA0A35900+1
#define ADDR_memcmp		0xA142627C+1
//#define ADDR_DrawString		0xA09A150F
//#define ADDR_FreeWS		0xA01F73A1
//#define ADDR_AllocWS		0xA09974F9
//#define ADDR_GetCurMenuItem	0xA09A997B
#define ADDR_IncommingPDU	0xA8E57F90

//#define ADDR_wstrcat		0xA01F7C2C+1
#define ADDR_wsAppendChar	0xA01F7CF4+1
#define ADDR_IsCalling		0xA0DE7EA4+1
#define ADDR_CallIN		0xA02FCB7C+1
//#define ADDR_CallOUT		0xA02FCD22+1
//#define ADDR_ADDRBook		0xA01F8062+1

#define BASEADDRESS		0xA1580000

#define ADDR_GetPhoneBookNum	0xA098A4CE+1
//#define BASEADDRESS		0xA1580000
//#define UNUSERAM_NUM		0xA8A7F300
//#define UNUSERAM_METHOD		0xA8A7F3E0
//#define UNUSERAM_OLD_REDRAW	0xA8A7F3D0

#define ADDR_CallOUT2		0xA0A7D666+1
#define	AllocMLMenuItem_adr	0xA09AE477
#define GetMLMenuGUI_adr	0xA09ADC68+1
#define AllocMenuWS_adr		0xA09AB25D
#define SetMLMenuItemText_adr	0xA09AE04F

#endif

#ifdef C81Cv50
#define ADDR_strlen		0xA1417C68+1 //30B4441C810708D001780130
#define ADDR_atou		0xA02C77F8+1 //002200E001300178
#define ADDR_WS_InitByZero	0xA01F7022+1 //70B5061C151C0C1C002903D06900
#define ADDR_GetCalleeNumber	0xA097A3AE+1 //70B50E1C041C0128A0B0
#define ADDR_UpdateWndItem	0xA0A3784C+1 //B0B500680D1C91004018C4680021201C
#define ADDR_memcmp		0xA1416E28+1 //10B4042A0ED3031C0B439B07
#define ADDR_IncommingPDU	0xA8ED6C90 //lib

#define ADDR_wsAppendChar	0xA01F72A0+1 //10B5021C0DD0101CFFF750FF
#define ADDR_IsCalling		0xA0DDF044+1 //70B50025????????1E4E0124
#define ADDR_CallIN		0xA02FB4BC+1 //10B586B0????????00240004

#define BASEADDRESS		0xA1580000

#define ADDR_GetPhoneBookNum	0xA098148E+1 //90B50C1C8BB069462A22

#define ADDR_CallOUT2		0xA0A85C96+1 //F0B5051C0E1C91B006A9
#define	AllocMLMenuItem_adr	0xA09A539B //B5051CFCF763FE041C
#define GetMLMenuGUI_adr	0xA09A4B8C+1 //B0B5041C11200D1C4001A047
#define AllocMenuWS_adr		0xA09A2181 //1C011CFF31813180B51204
#define SetMLMenuItemText_adr	0xA09A4F73 //B587B01099051CFFF7

#endif

#ifdef SL7Cv47
#define ADDR_strlen		0xA1426220+1 //30B4441C810708D001780130
#define ADDR_atou		0xA02C6650+1 //002200E001300178
#define ADDR_WS_InitByZero	0xA01F7A76+1 //70B5061C151C0C1C002903D06900
#define ADDR_GetCalleeNumber	0xA0981A66+1 //70B50E1C041C0128A0B0
#define ADDR_UpdateWndItem	0xA0A34838+1 //B0B500680D1C91004018C4680021201C
#define ADDR_memcmp		0xA14253E0+1 //10B4042A0ED3031C0B439B07
#define ADDR_IncommingPDU	0xA8E57F20 //lib

#define ADDR_wsAppendChar	0xA01F7CF4+1 //10B5021C0DD0101CFFF750FF
#define ADDR_IsCalling		0xA0DE8870+1 //70B50025????????1E4E0124
#define ADDR_CallIN		0xA02FA488+1 //10B586B0????????00240004

#define BASEADDRESS		0xA1580000

#define ADDR_GetPhoneBookNum	0xA0988B46+1 //90B50C1C8BB069462A22

#define ADDR_CallOUT2		0xA0A7D0EA+1 //F0B5051C0E1C91B006A9
#define	AllocMLMenuItem_adr	0xA09ACA53 //B5051CFCF763FE041C
#define GetMLMenuGUI_adr	0xA09AC244+1 //B0B5041C11200D1C4001A047
#define AllocMenuWS_adr		0xA09A9839 //1C011CFF31813180B51204
#define SetMLMenuItemText_adr	0xA09AC62B //B587B01099051CFFF7

#endif


#ifdef SK6Cv50
#define ADDR_strlen		0xA0D9626C+1
#define ADDR_atou		0xA020E4CC+1
#define ADDR_WS_InitByZero	0xA07197EA+1
#define ADDR_GetCalleeNumber	0xA0733432+1
#define ADDR_UpdateWndItem	0xA0999A5E+1
#define ADDR_memcmp		0xA0D958AC+1
#define ADDR_DrawString		0xA07F43B8+1
#define ADDR_FreeWS		0xA071988E+1
#define ADDR_AllocWS		0xA0719852+1
#define ADDR_GetCurMenuItem	0xA098B9E2+1

#define ADDR_wstrcat		0xA07199B8+1
#define ADDR_wsAppendChar	0xA0719AE0+1
#define ADDR_IsCalling		0xA09E5142+1
#define ADDR_CallIN		0xA038F496+1
#define ADDR_CallOUT		0xA038E854+1
#define ADDR_ADDRBook		0xA0719FE8+1
#define ADDR_SMS_SEND		0xA07D3BC0+1
#define BASEADDRESS		0xA0E30000
#define UNUSERAM_NUM		0xA8000240
#define UNUSERAM_METHOD		0xA8000300
#define UNUSERAM_OLD_REDRAW	0xA80002F0
#define ADDR_SELECT_MENU	0xA079188C+1
#define ADDR_MENU_DESC		0xA0711F5C
#define ADDR_IncommingPDU	0xA8F40F78

#endif

#ifdef S68Cv51
#define ADDR_strlen		0xA110632C+1 //30B4441C810708D001780130
#define ADDR_atou		0xA02B9190+1 //002200E001300178
#define ADDR_WS_InitByZero	0xA01B9DA2+1 //70B5061C151C0C1C002903D06900
#define ADDR_GetCalleeNumber	0xA08334CA+1 //70B50E1C041C0128A0B0
#define ADDR_UpdateWndItem	0xA08D427C+1 //B0B500680D1C91004018C4680021201C
#define ADDR_memcmp		0xA11054D4+1 //10B4042A0ED3031C0B439B07
#define ADDR_IncommingPDU	0xA8E48208 //lib

#define ADDR_wsAppendChar	0xA01BA020+1 //10B5021C0DD0101CFFF750FF
#define ADDR_IsCalling		0xA0C26E00+1 //70B50025????????1E4E0124
#define ADDR_CallIN		0xA02E8BA8+1 //10B586B0????????00240004

#define BASEADDRESS		0xA1580000

#define ADDR_GetPhoneBookNum	0xA083A5AA+1 //90B50C1C8BB069462A22

#define ADDR_CallOUT2		0xA08F747A+1 //F0B5051C0E1C91B006A9
#define	AllocMLMenuItem_adr	0xA085E4B7 //B5051CFCF763FE041C
#define GetMLMenuGUI_adr	0xA085DCA8+1 //B0B5041C11200D1C4001A047
#define AllocMenuWS_adr		0xA085B29D //1C011CFF31813180B51204
#define SetMLMenuItemText_adr	0xA085E08F //B587B01099051CFFF7
#endif

#ifdef M81Cv51
#define ADDR_strlen 0xA1418200+1
#define ADDR_atou 0xA02C78F8+1
#define ADDR_WS_InitByZero	0xA01F7146+1
#define ADDR_GetCalleeNumber	0xA097AEE6+1
#define ADDR_UpdateWndItem	0xA0A38380+1
#define ADDR_memcmp	0xA14173C0+1

#define ADDR_wstrcat 0xA0BB5114
#define ADDR_wsAppendChar 0xA0BB5050
#define ADDR_IsCalling 0xA0DE44C8+1
#define ADDR_CallIN 0xA02FB630+1
#define ADDR_CallOUT 0xA02FB7D6+1
#define ADDR_ADDRBook 0xA01F7732+1

#define BASEADDRESS			0xA1580000
#endif

