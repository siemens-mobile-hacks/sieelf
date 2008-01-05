//function define for special phone by bennie
//MiniGPS         EQU	    0xA0FC7600+1

//RamUnuse		EQU     0xA8D8A000
strlen			EQU	0xA0FF1BFC+1    ;int strlen(const char* src); //30B4441C8107
atou			EQU	0xA0643348+1	;uint atou(const char* src); //002200E001300178
WS_InitByZero		EQU	0xA051072E+1	;WString*  WS_InitByZero(WString*, word* buf, int count)//func 127
GetCalleeNumber 	EQU	0xA094D15E+1	;void GetCalleeNumber(int index, WString *ws);//70B50E1C041C0128A0B0
UpdateWndItem		EQU	0xA0A4EA4C+1	;void UpdateWndItem(void* Countext, WString* ws, int index);//B0B500680D1C91004018C4680021201C 
memcmp			EQU	0xA0FF0DA4+1	;int memcmp(const void* dst, const void* src, int size)

malloc			EQU     0xA0092F51
fopen			EQU     0xA057EC9C
fread			EQU     0xA057ED5C
fwrite			EQU	0xA057EE8C
fclose			EQU     0xA057EBF0
OpenReadCloseFile	EQU	0xA006F001

/*
//not port
RamPressedKey		EQU	0xA8DF32BC	;//0xA8D35004
RamNetOnline		EQU	0xA8E69060	;//0xA8DACBE0
StartMidlet		EQU	0xA0B04460	;//0xA0AAC51C
GetDateTime		EQU	0xA08FA66B	;//0xA0962E13
PlaySound		EQU	0xA05BCC1C	;//0xA0283464
PlaySoundLoop		EQU	0xA0BAC3A0	;//0xA0B279C0
PlaySoundVibra		EQU	0xA006F211
*/