int NewMsgReader(void);
int IsHaveNewSMS(void);
SMS_DATA *GetTheLastNew(int reload);
int CheckThisSMS(int index); //return, 0:do nothing, 1:need to reload all, 2:need to refresh gui
