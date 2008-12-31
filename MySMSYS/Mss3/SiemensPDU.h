#ifndef _SIEMENSPDU_H_
#define _SIEMENSPDU_H_

class SiememPDU
{
public:
//  SiememPDU();
//  ~SiememPDU();
  void Bit7Decode(WSHDR *ws, char *pdata, int skip, int len);
  int PduDecodeTxt(SDLIST *sd, char *data);
  int PduDecodeAll(SDLIST *sd, char *data);
  void DoSmsReport(SDLIST *sd, char *data, WSHDR *ws);
private:
  void Add2WS(char *data, WSHDR *ws, int len);
  void Hex2Num(char *hex, char *num, int len);
};

#endif


