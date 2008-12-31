#ifndef _CSMSWAPER_H_
#define _CSMSWAPER_H_

extern "C"
{
void CSMtoTop(int id, int top_id);
void InitUnderIdleCSM(void);
void DoSendBackGround(void *dialog_csm);
}
#endif


