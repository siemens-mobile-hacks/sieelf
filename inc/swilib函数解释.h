0.1��

0
void loopback0();

1
void loopback1();

2
void loopback2();

3
void loopback3();

4
void loopback4();

6
int GetAkku(int param1,int param2);

8//��������
long SetIllumination(unsigned char dev,unsigned long param1,unsigned short bright,unsigned long delay);

0x9//�ػ�
void SwitchPhoneOff();

10//���ļ�
int fopen(const char * cFileName, unsigned int iFileFlags, unsigned int iFileMode, unsigned int *ErrorNumber);

11//��ȡ�ļ�
int fread(int FileHandler, void *cBuffer, int iByteCount, unsigned int *ErrorNumber);

12//д���ļ�
unsigned int fwrite(int FileHandler, void const * cBuffer, int iByteCount, unsigned int *ErrorNumber);

13//�ر��ļ�
void fclose(int FileHandler, unsigned int *ErrorNumber);

15//�ļ�ָ���ƶ�
unsigned int lseek(int FileHandler, unsigned int offset, unsigned int origin, unsigned int *ErrorNumber, unsigned int *ErrorNumber2);

16//������Ŀ¼
int mkdir(const char * cFileName, unsigned int *ErrorNumber);

18//�ļ�����
int GetFileAttrib(const char *cFileName, unsigned char *cAttribute, unsigned int *ErrorNumber);

19//�޸��ļ�����
int SetFileAttrib(const char *cFileName, unsigned char cAttribute, unsigned int *ErrorNumber);

20//������̬�ڴ�
void *malloc(unsigned int size);

0x8014
void *malloc_adr(void);

21//��ն�̬�ڴ�
void mfree(void *);

0x8015
void *mfree_adr(void);

22//��ʽ�����
int sprintf(char *buf, const char *str, ...);

23//ƴ��
char * strcat (char *,const char *);

24//�ַ�λ��
char * strchr (const char *,int);

25//�Ա�
int  strcmp (const char *,const char *);

26//����
char * strcpy (char *dest,const char *source);

27//����
unsigned int strlen(const char *);

28//ƴ���ַ�
void  wsAppendChar(WSHDR *ws,int wchar);

29//�����ַ�
int wsInsertChar(WSHDR *ws,int wchar,int pos);

30//ȡ��pit��ַ?
IMGHDR *GetPITaddr(int num);

33//ͼƬ�߶�
int GetImgHeight(int picture);

34//ͼƬ���
int GetImgWidth(int picture);

35//��ͼ
void DrawImg(unsigned int x, unsigned int y, unsigned int picture);

37//������
void DrawCanvas(void *data, int x1, int y1, int x2, int y2, int flag_one);

38//����ɫ���õĻ�ͼ
void DrawImgBW(unsigned int x, unsigned int y, unsigned int picture, char *pen, char *brush);

50//��������
void PlaySound(long param1, long param2, long param3, long tone, long param5);

42//ȡ��EELite���ַ(EEP)
int *GetEELiteBlockAddress(short blocknum);

60//�����ļ���С???
int setfilesize(int FileHandler, unsigned int iNewFileSize, unsigned int *ErrorNumber);

0x0042//����״̬
int IsScreenSaver(void);

67//������״̬
int IsUnlocked(void);

0x0046//�¶���
int HasNewSMS(void);

0x4A//��������
#ifdef X75
short PlayFile(int flags, WSHDR *foldername, WSHDR *filename, int zero, int CepId, int Msg, const PLAYFILE_OPT *sfo);
#else
short PlayFile(int flags, WSHDR *foldername, WSHDR *filename, int CepId, int Msg, const PLAYFILE_OPT *sfo);
#endif

0x004C//δ���¼�
int GetMissedCallsCount(void);

77//ѭ����������PTR(),
void GBS_StartTimerProc(void *htimer, long ms, void ptr());

0x4E//��ʾ����
int MsgBoxError(int flag, int LgpId);

0x4F//��ʾ����
int MsgBoxYesNo(int flag, int LgpID, void CallBackProc(int));

0x50//��ʾ����
int MsgBoxOkCancel(int flag, int LgpID, void CallBackProc(int));

92//ȡ��cpuƵ��
unsigned char GetCPUClock();

93//����cpuƵ��
unsigned char GetCPULoad();

95//ȡ�ÿ���RAM����
int GetFreeRamAvail();

107
int  FindFirstFile (DIR_ENTRY *DIRENTRY,char *mask,unsigned int *ErrorNumber);

108
int  FindNextFile (DIR_ENTRY *DIRENTRY,unsigned int *ErrorNumber);

109
int  FindClose (DIR_ENTRY *DIRENTRY,unsigned int *ErrorNumber);

0x06E//��绰״̬
int IsCalling(void);

111//ˢ��gprs������
void RefreshGPRSTraffic();

112//gprs����Ŀ��??
int *GetGPRSTrafficPointer();

0x0073//��绰״̬,0,ȫ�� 1������ 2��ȥ��
int GetTypeOfCall();

116//����ָ���ַ??
void* GetFunctionPointer(char * _shortcut);

124//��
unsigned int SetVibration(unsigned int power);

128//�����¼
int ShowCallList(int list, int zero);

132//ȡ���ļ�ͳ����Ϣ??
int GetFileStats(const char *cFileName, FSTATS * StatBuffer, unsigned int *errornumber);

138//���ڴ��С
int GetFreeFlexSpace(int DriveNum, unsigned int *ErrorNumber);

139//���ڴ��С
int GetTotalFlexSpace(int DriveNum, unsigned int *ErrorNumber);

140
void RegExplorerExt(REGEXPLEXT const *);

142//�����ƶ�??����??
int fmove(const char * SourceFileName, const char * DestFileName, unsigned int *ErrorNumber);

143//ɾ��Ŀ¼
int rmdir(const char * cDirectory, unsigned int *ErrorNumber);

144//�ü�
int truncate(int FileHandler, int length, int *errornumber);

145//�Ƿ�Ŀ¼
int isdir(const char * cDirectory, unsigned int *ErrorNumber);

146//����������̬�ڴ�
void *calloc(size_t nelem, size_t elsize);

148//���г���
int ExecuteFile (WSHDR *filepath, WSHDR *mimetype, void *param);

149
int UnRegExplorerExt(REGEXPLEXT const *);

154//�ı�����
__swi int ChangeVolume(unsigned char Volume);

163//ws->str
void ws_2str(WSHDR *ws, char *str, unsigned int size);

166//����GPRS������Ŀ
void ResetGPRSTraffic();

170//ȡ�õ�ǰ���õ�������Ϣ
char *GetCurrentLocale();

171
void loopback171();

180//ȡ��ʱ������
void GetDateTime(TDate *, TTime *);

181//ȡ������
char GetWeek(TDate*);

182//ȡ���龰
char GetProfile();

183//�����龰
char SetProfile(char);

184//�з��ų���
int sdiv(int denom,int number);

167//gprs��״̬
char IsGPRSEnabled();

168//gprs����״̬
char IsGPRSConnected();

169//������
void KbdLock();

185//������
void KbdUnlock();

186//���·����ڴ�
void *realloc(void *ptr, int size);

187//��Sÿһ�ֽڵ����һλ���c ,n�ǳ���
void *memset(void *s, int c, int n);

188//�޷��ų���
int udiv(unsigned int denom,unsigned int number);

189//10���Ƴ���
int DivBy10(int divident);

198//ȡ�õ������
char GetAkkuCapacity();

0x088//ȡ�ø�������?
char GetAccessoryType(void);

0x93//����
void RebootPhone();

0x80C8//����
unsigned short *RamCap();

0x80C9
unsigned short *RamLS();

0x80CA//�ź�
RAMNET * RamNet();

0x80CC //δ�ӵ绰?
char * RamMissedCalls(); 

0x80CD //δ�Ӷ���?
char * RamMissedSMS();

0x80D4 //δ����Ϣ?
char * RamMissedMessage();

0x80DF//����?
char *RamPressedKey();

0x80E0//��Ļ����
void * RamScreenBuffer();

0x80E1
unsigned int *RamMPlayer_CtrlCode();

0x80F1
void *BuildCanvas(void);

0x80FF
unsigned int AddrLibrary();

0x0100//����ϵͳ��Ϣ
void GBS_SendMessage(int cepid_to, int msg, ...); //int submess, void *data1, void *data2

0x0101//����ϵͳ��Ϣ
int GBS_ReciveMessage(GBS_MSG *);

0x0102//����ϵͳ��Ϣ
void GBS_AcceptMessage(void);

0x0103//���ϵͳ��Ϣ
void GBS_ClearMessage(void);

0x0104//��ͣϵͳ��Ϣ
void GBS_PendMessage(GBS_MSG *);

0x0105//����ѭ��
void CreateGBSproc(int cepid, const char *name, void (*onMsg)(void), int prio, int unk_zero);

0x8106
CSMROOT *CSM_root();

0x0107//����CSM
int CreateCSM(const CSM_DESC*,void *,int);

0x0108//����CSM
CSM_RAM * FindCSMbyID (int id);

0x0109
void DoIDLE(void);

0x010A//��ȡ����
void *GetConfig(unsigned int id); //BoBaPack

0x810B
void *GetMinAdrScan(); //BoBaPack
//adr=0xA0030000

0x810C
void *GetMaxAdrScan(); //BoBaPack
//adr=0xA0040000

0x810D
unsigned short *GetCI();

0x010E//��
void Vibration(unsigned int power, unsigned int duration); //BoBaPack

0x010F//���ussd
void freeUSSD();

0x0110//wstr����
char *wstrcopy(unsigned short *dst, const unsigned short *src);

0x0111//��ȡussd����
char GetTypeUSSD();

0x0112//����USSD
unsigned int SetUSSD(StructUSSDStr *);

0x0113//����S1�г���S2����һ�ַ����ֵ�λ��
char * strpbrk (const char *s1,const char *s2);

0x0114//�г���ƴ��
char * strncat (char *dest,const char *substr,int maxSubLen);

0x0115//�г��ȶԱ�
int  strncmp (const char *s1,const char *s2,int n);

0x0116//�г��ȸ���
int  strncpy (char *dest,const char *source,int maxlen);

0x0117//�����ַ�λ��
char * strrchr (const char *s,int c);

0x0118//�����ַ���λ��
char * strstr (const char *s1,const char *s2);

0x011B//�г��ȵĸ�ʽ�����
int snprintf (char *,int n,const char *format,...);

0x011C//�Ƚ��ڴ�����
int  memcmp (void *m1,void *m2,int n);

0x011D//�ڴ���������
void  zeromem (void *dest,int n);

0x011E//�ڴ����ݸ���
void * memcpy (void *dest,const void *source,int cnt);

0x011F//����
WSHDR * wstrcpy (WSHDR *wshdr_d,WSHDR *wshdr_s);

0x0120//�г��ȵĸ���
WSHDR * wstrncpy (WSHDR *,WSHDR *,int);

0x0121//ƴ��
WSHDR * wstrcat (WSHDR *wshdr_d,WSHDR *wshdr_s);

0x0122//�г��ȵ�ƴ��
WSHDR * wstrncat (WSHDR *wshdr_d,WSHDR *wshdr_s,int n);

0x0123//ȡ�ó���
int  wstrlen (WSHDR *wshdr);

0x0124//��ʽ�����
int wsprintf (WSHDR *,const char *format,...);

0x0125//����
WSHDR * AllocWS (int len);

0x0126//����wstr
void  CutWSTR (void *WSHDR,int len);

0x0127
WSHDR * CreateLocalWS (WSHDR *wshdr,unsigned __int16 *wsbody,int len);

0x0128//����ws
int  CreateWS (void *malloc,void *mfree,int len);

0x0129//���
void  FreeWS (WSHDR *wshdr);

0x012A//����Ŀ
void  DrawObject (DRWOBJ *);

0x012B
void  AddKeybMsgHook (void *proc);

0x012C
int  AddKeybMsgHook_end (void *proc);

0x012D
void  RemoveKeybMsgHook (void *proc);

0x012E
char *GetPaletteAdrByColorIndex (int ColorIndex);

0x012F//��ȡrgbyanse
void  getRGBcolor (int ColorIndex,void *dest);

0x0130
void  getRGBbyPaletteAdr (int *paletteAdr,void *dest);

0x0131//������ɫ
void  setColor (int a,int r,int g,int b,void *dest);

0x0132//�ڴ��ƶ�
void *memmove(void *dest,const void *source,int cnt);

0x0133
void  StoreXYWHtoRECT (void *RECT,int x,int y,int w,int h);

0x0134
void  StoreXYXYtoRECT (void *RECT,int x,int y,int x2,int y2);

0x0135
int  IsGuiOnTop (int id);

0x0136
int  CreateGUI_ID (void *gui,int id);

0x0137//����GUI
int  CreateGUI (void *gui);

0x0138
int  CreateGUI_30or2 (void *gui);

0x0139
int  CreateGUIWithDummyCSM (void *gui,int flag);

0x013A
int  CreateGUIWithDummyCSM_30or2 (void *gui,int flag);

0x013B
void  GeneralFuncF1 (int cmd);

0x013C
void  GeneralFuncF0 (int cmd);

0x013D
void  GeneralFunc_flag1 (int id,int cmd);

0x013E
void  GeneralFunc_flag0 (int id,int cmd);

0x013F
void DirectRedrawGUI (void);

0x0140
void  DirectRedrawGUI_ID (int id);

0x0141
void PendedRedrawGUI (void);

0x0142
CSM_RAM * FindCSM (void *csm_q,int id);

0x0143//��ʼ����
void  GBS_StartTimer (GBSTMR *tmr,int time,int msg,int unk,int cepid);

0x0144//ֹͣ��ת
void  GBS_StopTimer (GBSTMR *tmr);

0x0145//��ȡcepid
int GBS_GetCurCepid (void);

0x0146//
void LockSched(void);

0x0147//
void UnlockSched(void);

0x0148//��ʾ��Ϣ
extern int ShowMSG(int flag, int lgp_id);

0x0149
void SetPropTo_Obj1(DRWOBJ *drwobj,void *rect,int rect_flag,WSHDR *wshdr,int font,int text_flag);

0x014A
void FreeDrawObject_subobj(DRWOBJ *drwobj);

0x014B//������ɫ
void SetColor(DRWOBJ *drwobj, char *color1, char *color2);

0x014C//����
void DrawString(WSHDR *WSHDR,int x1,int y1,int x2,int y2,int font,int text_attribute,const char *Pen,const char *Brush);

0x014D
GUI *GetTopGUI(void);

0x014E
void *FindItemByID(GUI *gui,int id);

0x014F
void *GetDataOfItemByID(GUI *gui,int id);

0x0150//����
void DrawRoundedFrame(int x1,int y1,int x2,int y2,int x_round,int y_round,int flags,const char *pen,const char *brush);

0x0151
void SetPropTo_Obj5(DRWOBJ *, RECT *, int zero, IMGHDR *Image);

0x0152//�����˵�
int CreateMenu(int is_small,int zero1,const MENU_DESC *menu, const HEADER_DESC *hdr,int start_item,int n_items,void *user_pointer,int *to_remove);

0x0153
int GBS_RecActDstMessage(GBS_MSG *);

0x0154//���ѭ��
void KillGBSproc(int cepid);

//===========================================
//pnglib
//===========================================

0x0155
png_structp png_create_read_struct(png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn);

0x0156
png_infop png_create_info_struct(png_structp png_ptr);

0x0157
void png_destroy_read_struct(png_structpp png_ptr_ptr, png_infopp info_ptr_ptr, png_infopp end_info_ptr_ptr);

0x0158
void png_set_sig_bytes(png_structp png_ptr,int num_bytes);

0x0159
void png_read_info(png_structp png_ptr, png_infop info_ptr);

0x015A
png_uint_32 png_get_IHDR(png_structp png_ptr,png_infop info_ptr, png_uint_32 *width, png_uint_32 *height, int *bit_depth, int *color_type, int *interlace_method, int *compression_method, int *filter_method);

0x015B
png_voidp png_malloc(png_structp png_ptr, png_uint_32 size);

0x015C
void png_read_image(png_structp png_ptr, png_bytepp image);

0x015D
void png_read_end(png_structp png_ptr, png_infop info_ptr);

0x015E
png_voidp png_get_io_ptr(png_structp png_ptr);

0x015F
png_uint_32 png_get_rowbytes(png_structp png_ptr,png_infop info_ptr);

0x0160
void png_read_row(png_structp png_ptr,png_bytep row,png_bytep dsp_row);

0x0161
void png_init_io(png_structp png_ptr, int fp);


//===========================================
//===========================================

0x0162
int setjmp(jmp_buf jmpbuf);

0x0163
EDITQ *AllocEQueue(void *malloc_a, void *mfree_a);

0x0164
EDITCONTROL *PrepareEditControl(EDITCONTROL *);

0x0165
void ConstructEditControl(EDITCONTROL *EditControl,int type,int flag,WSHDR *ws,int maxlen);

0x0166
int AddEditControlToEditQend(void *EditQ,EDITCONTROL *EditControl,void *malloc_a);

0x0167
int CreateInputTextDialog(const INPUTDIA_DESC *input_desc, const HEADER_DESC *header_desc,void *editq,int do_mfree,void *user_pointer);

0x0168//�������
void SetSoftKey(void *gui,const SOFTKEY_DESC *,int n);

0x0169//ȡ�ñ༭����
int ExtractEditControl(void *guidata,int n,EDITCONTROL *);

0x016A//���ֱ༭����
int StoreEditControl(void *guidata,int n,EDITCONTROL *);

0x016B//ɾ���ļ�?
int unlink(const char *cFileName,unsigned int *errornumber);

0x016C//ste->ws
int str_2ws(WSHDR *ws,const char *str,unsigned int size);

0x016D
int UnpackABentry(AB_UNPRES *,void *abentry,int filesz,int flag);

0x016E
int FreeUnpackABentry(AB_UNPRES *, void *mfree_adr);

0x016F
int GetTypeOfAB_UNPRES_ITEM(int);

0x0170//��绰
int MakeVoiceCall(const char *number,int _0x10, int _0x20C0);

0x0171
void SUBPROC(void *,...); //(void (*)(void *, int),void *, int);

0x0172//ˢ�»���
void REDRAW(void);

//===========================================
//Sockets
//===========================================
0x0173
int socket(int af,int type,int protocol);

0x0174
int connect(int sock,SOCK_ADDR *,int name_length);

0x0175
int bind(int sock,SOCK_ADDR *,int name_length);

0x0176
int closesocket(int socket);

0x0177
int shutdown(int socket,int how);

0x0178
int recv(int socket,void *buf,int len,int flag);

0x0179
int send(int socket,const void *buf,int len,int flag);

0x017A
unsigned __int16 htons(unsigned __int16);

0x017B
unsigned int htonl(unsigned int);

0x817C
int *socklasterr(void);

//--------------------------------------------------
//IDLE timer
//--------------------------------------------------
0x017D
void SetIDLETMR(int time_ms,int msg);

0x017E
void RestartIDLETMR(void);

0x017F
void DisableIDLETMR(void);

0x0180
int EDIT_GetItemNumInFocusedComboBox(void *gui);

0x0181//��������Ϊ�༭����
void EDIT_SetTextToFocused(void *gui,WSHDR *ws);

0x0182
int EDIT_GetFocus(void *gui);

0x0183
int EDIT_GetUnFocus(void *gui);

0x0184
void ConstructComboBox(EDITCONTROL *EditControl,int type,int attr,WSHDR*,int maxlen,int unk_zero,int num_of_items,int start_item);

0x0185//�ȴ���Ϣ
int GBS_WaitForMsg(const int *msg_list, int msgs_num, GBS_MSG*, int timeout);

0x0186
int RegisterCepidForSocketWork(REGSOCKCEPID_DATA *);

0x0187
int RequestLMANConnect(LMAN_DATA *);

0x8188//��Ļ���
int ScreenW(void);

0x8189//��Ļ�߶�
int ScreenH(void);

0x818A//��Ϣ���߶�
int HeaderH(void);

0x818B//����߶�
int SoftkeyH(void);

0x018C//ɾ����ʱ
void GBS_DelTimer(GBSTMR *);

0x018D
int available0(int sock);

0x018E//����gprs
void GPRS_OnOff(int on, int _1);

0x018F
int GetCurMenuItem(void *gui);

0x0190
void MutexCreate(MUTEX *mtx);

0x0191
void MutexDestroy(MUTEX *mtx);

0x0192
void MutexLock(MUTEX *mtx);

0x0193
void MutexLockEx(MUTEX *mtx, int flag);

0x0194
void MutexUnlock(MUTEX *mtx);

0x0195//���ò˵���Ŀͼ��
void SetMenuItemIcon(void *gui,int item_n,int icon_n);

0x0196//ˢ��
void RefreshGUI(void);

0x0197
void *AllocMenuItem(void *gui);

0x0198
WSHDR *AllocMenuWS(void *gui, int len);

0x0199
void SetMenuItemIconArray(void *gui,void *item,const int *icons);

0x019A
void SetMenuItemText(void *gui,void *item,WSHDR *text,int item_n);

0x019B
void EDIT_SetFocus(void *gui, int item);

0x019C
void SEQKILLER(void *data, void(*next_in_seq)(void *), void *data_to_kill);
0x819C
void *SEQKILLER_ADR();

0x019D
long long getCpuUsedTime_if_ena(void);

0x019E
void StartCpuUsageCount(void);

0x019F
int inflateInit2_ (z_streamp strm, int windowBits,const char *version, int stream_size);

0x01A0
int inflate (z_streamp strm, int flush);

0x01A1
int inflateEnd (z_streamp strm);

0x01A2
int ActivateDialUpProfile(unsigned int cep_id,int profile_num);

0x01A3
int GetCurrentGPRSProfile(void);

0x01A4
int GetDisconnectTime(void);

0x01A5
void RegisterCepIdForCurProfile(unsigned int cep_id,int profile_num,unsigned int csd_or_gprs);

0x01A6
int IsTimerProc(GBSTMR *);

0x1A7
char* Get_CC_NC();

//===========================================
//pnglib part 2
//===========================================
0x1A8
png_structp png_create_read_struct_2(png_const_charp user_png_ver, png_voidp error_ptr,
                                                 png_error_ptr error_fn, png_error_ptr warn_fn, png_voidp mem_ptr,
                                                 png_malloc_ptr malloc_fn, png_free_ptr free_fn);

0x1A9
void png_set_read_fn(png_structp png_ptr, png_voidp io_ptr, png_rw_ptr read_data_fn);

0x1AA
void png_read_update_info(png_structp png_ptr,void *info_ptr);

0x1AB
void png_set_palette_to_rgb(png_structp png_ptr);

0x1AC
png_uint_32 png_get_valid(png_structp png_ptr,png_infop info_ptr, png_uint_32 flag);

0x1AD
void png_set_tRNS_to_alpha(png_structp png_ptr);

0x1AE
void png_set_filler(png_structp png_ptr,png_uint_32 filler, int flags);

0x1AF
void png_set_strip_16(png_structp png_ptr);

0x1B0
void png_set_packing(png_structp png_ptr);

0x1B1
void png_set_gray_to_rgb(png_structp png_ptr);

0x1B2
int png_check_sig(png_bytep sig, int num);

//===========================================
//===========================================

0x1B3//����
void DrawLine(int x,int y,int x2,int y2,int type,const char *pen);

0x1B4//������
void DrawRectangle(int x,int y,int x2,int y2,int flags,const char *pen,const char *brush);

0x81B5
__swi int isnewSGold(void);

0x1B6
int async_gethostbyname(const char *host_name,int ****DNR_RES,int *DNR_ID);

0x1B7
unsigned int str2ip(const char *);

0x81B8
void *EXT_TOP(void);

0x81B9
void *PNG_TOP(void);

0x81BA
void *LIB_TOP(void);

0x81BB
void *DATA_N_SFB(void);

//===========================================
//openssl_lib
//===========================================

0x1BC
void SHA1_Init(SHA_CTX *c);

0x1BD
void SHA1_Update(SHA_CTX *c, const void *data, unsigned long len);

0x1BE
void SHA1_Final(char *md, SHA_CTX *c);

0x1BF
RSA * RSA_new_method(RSA_METHOD *method);

0x1C0
void RSA_free (RSA *r);
 
0x1C1
int RSA_sign(int type, char *m, unsigned int m_len, char *sigret, unsigned int *siglen, RSA *rsa);

0x1C2
BIGNUM *BN_bin2bn(const char *s,int len,BIGNUM *ret);

0x1C3
void SetMenuItemCount(void *gui,int n);

0x1C4
void SetCursorToMenuItem(void *gui,int n);

0x1C5//������
int GetFontYSIZE(int font);

0x1C6
void EDIT_ExtractFocusedControl(void *gui,EDITCONTROL *ec);

0x1C7
int EDIT_StoreControlToFocused(void *gui,EDITCONTROL *ec);

0x1C8
EDITC_OPTIONS *PrepareEditCOptions(EDITC_OPTIONS *ec_options);

0x1C9
void SetInvertToEditCOptions(EDITC_OPTIONS *ec_options, int invert);

0x1CA
void SetFontToEditCOptions(EDITC_OPTIONS *ec_options, int font);

0x1CB
void SetAlignToEditCOptions(EDITC_OPTIONS *ec_options, int align);

0x1CC
void SetPenColorToEditCOptions(EDITC_OPTIONS *ec_options, int pen);

0x1CD
void SetBrushColorToEditCOptions(EDITC_OPTIONS *ec_options, int brush);

0x1CE
void CopyOptionsToEditControl(EDITCONTROL *ec,EDITC_OPTIONS *ec_options);

#ifdef NEWSGOLD
  #define TREGEXPLEXT REGEXPLEXT
#else
  #define TREGEXPLEXT REGEXPLEXT_ARM_NEW 
#endif

0x1CF
TREGEXPLEXT *get_regextpnt_by_uid(int uid);

0x1D0
int GetExtUid_ws(WSHDR * ext);

0x1D1
void EDIT_RemoveEditControl(void *gui,int n);

0x1D2
void EDIT_InsertEditControl(void *gui,int n,EDITCONTROL *);

0x1D3//ȡ�ù��λ��
int EDIT_GetCursorPos(void *gui);

0x1D4//���ù��λ��
void EDIT_SetCursorPos(void *gui, int pos);

0x1D5//�ֻ���Ϣ
char *Get_Phone_Info(int InfoIndex);

0x1D6
void png_set_gray_1_2_4_to_8(png_structp png_ptr);

0x1D7
void png_set_invert_mono(png_structp png_ptr);

0x1D8//��ʶ����
int EDIT_IsMarkModeActive(void *gui);

0x1D9//��ʶ��
int EDIT_GetMarkedText(void *gui,WSHDR *dest);

0x1DA//���Ͷ���
void SendSMS(WSHDR *ws,const char *num,int cepid,int msg,int flag);

0x81DB//����������?
PDU *IncommingPDU(void);

0x1DC//�ַ�λ�ò���(��ʼλ��)
short wstrchr(WSHDR *ws,unsigned int start_pos,unsigned int wchar);

0x1DD//�ַ�λ�ò���(���λ��)
short wstrrchr(WSHDR *ws,unsigned int max_pos,unsigned int wchar);

0x1DE
int EDIT_SetTextToEditControl(void *gui,int n,WSHDR *ws);

0x1DF
void *EDIT_GetUserPointer(void *gui);

0x1E0
void *MenuGetUserPointer(void *gui);

0x1E1//ȡ���ַ����
int GetSymbolWidth(int wchar,int font);

0x1E2//ws->utf8
int ws_2utf8( WSHDR *from, char *to , int *result_length, int max_len);

0x1E3//utf8->ws
int utf8_2ws(WSHDR *ws,const char *utf8_str, unsigned int maxLen);

0x1E4
int GetPicNByUnicodeSymbol(int wchar);

0x1E5
int EDIT_OpenOptionMenuWithUserItems(void *gui, void (*itemhandler)(USR_MENU_ITEM *item), void *user_pointer, int to_add);

0x1E6
void Menu_SetItemCountDyn(void *gui, int n);

0x1E7//������е�java�����ַ
char *GetLastJavaApplication();

0x1E8//������java״̬
int IsNoJava();

0x1E9
IMGHDR *CreateIMGHDRFromPngFile(const char *fname, int type);

0x1EA
int GetMaxDynIcon(void);

0x81EB
char *RAM_IMSI(void);

0x1EC
void FreeDynIcon(int picture);

0x1ED
int IsDynIconBusy(int picture);

0x1EF
void SetDynIcon(int picture,IMGHDR *img,char *bitmap);

0x1F3
unsigned int GetSessionAge(void);

0x1F5
int sscanf(const char *, const char *, ...);

0x1F6
IMGHDR* GetPitAdrBy0xE200Symbol(int uni_symbol);

0x81FB
char *RamMediaIsPlaying();

0x1FC//�ر�csm
void CloseCSM(int id);

0x201
void SetProp2ImageOrCanvas(DRWOBJ *, RECT *, int zero, IMGHDR *Image, int bleed_x, int bleed_y);

0x202
void fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int flag, char *pen, char *brush);

0x203
void SetPixel(int x,int y,char *color);

0x204//��Բ
void drawArc(int x1,int y1,int x2,int y2,int a1,int a2,int flag,char *pen,char *brush);

0x205
void SetProp2Square_v1(void);

0x206//��rand()�����趨����
void srand(unsigned int seed);

0x207//��ѭ��������
void DrawScrollString(WSHDR *WSHDR,int x1,int y1,int x2,int y2,int xdisp,int font,int text_attribute,const char *Pen,const char *Brush);

0x208//���ֳ���
int Get_WS_width(WSHDR *ws, int font);

0x209
void *FindGUIbyId(int id, CSM_RAM **csm);

0x20A//��������
void EDIT_SetDate(void *gui,int n,TDate *dd);

0x20B//����ʱ��
void EDIT_SetTime(void *gui,int n,TTime *tt);

0x20C//��ȡ����
void EDIT_GetDate(void *gui,int n,TDate *dd);

0x20D//��ȡʱ��
void EDIT_GetTime(void *gui,int n,TTime *tt);

0x20E
int ConstructEditTime(EDITCONTROL *EditControl,TTime *time);

0x20F
int ConstructEditDate(EDITCONTROL *EditControl,TDate *date);

0x212
int CardExplGetCurItem(void *csm);

0x213
void CardExplGetFName(void *csm, int cur_item, WSHDR *dest);

0x214
void wstrcpybypos(WSHDR *dest,WSHDR *src,int from,int len);

0x215
void wsRemoveChars(WSHDR *ws,int from,int to);

0x216//��ʽ��ƴ��
void wstrcatprintf(WSHDR *,const char *format,...);

0x217
int CreateMultiLinesMenu(int dummy,int dummy2,const ML_MENU_DESC *,const HEADER_DESC *,int to_item,int n);

0x218
void SetMLMenuItemText(void *data,void *item,WSHDR *ws1,WSHDR *ws2,int n);

0x219
void *AllocMLMenuItem(void *data);

0x21A
int EDIT_SetTextInvert(void *gui,int cursor_pos,int len);

0x21B
void EDIT_RemoveTextInvert(void *gui);

0x21C//�༭��æ״̬
int EDIT_IsBusy(void *gui);

0x21D
int GSMTXT_Decode(WSHDR *dest,void *pkt,int len,int encoding_type, void *(*malloc_adr)(int), void (*mfree_adr)(void));

0x21E//����gui
void FocusGUI(int id);

0x21F//�ǽ���gui
void UnfocusGUI(void);

0x225//�ı�����
int PlayMelody_ChangeVolume(int handle,int volume);

0x226//ֹͣ����
int PlayMelody_StopPlayback(int handle);

0x227//��ͣ����
int PlayMelody_PausePlayback(int handle);

0x228//��������
int PlayMelody_ResumePlayBack(int handle);

0x229
void longjmp(jmp_buf, int);

#ifdef NEWSGOLD
0x8052
#else
0x0052
#endif
char *GetIlluminationDataTable();

0x0035//������
void AlarmClockRing();

0x22A
void FreeGSMTXTpkt(void *pkt);

0x234//ũ������
int GetLunarDate(TDate* pdate, TDate* pLdate);

0x235
int GetLunarYearID(int year);

0x236
int GetLunarAnimal(int year);

0x237
char *RamIconBar(void);

0x8237
char *RamIconBar();

0x86
void ReadEEPROMData(int block, void *buf, int offset, int size);

0x7E//����һ��α�������
int Rand(void);

0x2C//��ȡeefull����Ϣ
int EEFullGetBlockInfo(unsigned int block,int *size,char *version); // res : 0 -OK; 2 - block not found

0x86//��ȡeefull��
void EEFullReadBlock(int block, void *buf, int offset, int size, int cepid, int msg); //cepid=0xFFFF (allow 0x0 on NSG) ; 

0x87//д��eefull��
void EEFullWriteBlock(int block, void *buf, int offset, int size, int cepid, int msg); 

0x239//ɾ��eefull��
int EEFullDeleteBlock(unsigned int block,int cepid,int msg); //cepid=msg=0

0x23A//����eefull��
int EEFullCreateBlock(unsigned int block,int size,int version,int cepid,int msg);

0x23B
void DisableIconBar(int disable); //disable=1 - iconbar don`t autoredraw

0x45//��ȡwav�ļ����� 
#ifdef NEWSGOLD 
int GetWavLen(char *filename); 
#else 
int GetWavLen(TWavLen *wl); 
#endif

0x23C
int SetCurrentGPRSProfile(int profile);

0x23D
void MD5_Init(MD5_CTX *c);

0x23E
void MD5_Update(MD5_CTX *c, const void *data, unsigned long len); 

0x23F
void MD5_Final(unsigned char *md, MD5_CTX *c);

0x240
char *MD5_Hash(const unsigned char *data, unsigned long n, unsigned char *md); //md can be NULL


