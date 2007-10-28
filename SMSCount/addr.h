#ifndef _ADDR_H_
  #define _ADDR_H_
  
#ifdef E71Cv41
#define RamSMSNum	0xA8F1F519 //1.????8C3C201C????????7068  2.ida 3.-0x153
//*(7168002088847068+18)-153
#define uitostr		0xA050F42C+1 //BFB50C1C69460C22
#endif

#ifdef S7Cv47
#define RamSMSNum	0xA8E57DED
#define uitostr		0xA01F71AC+1
#endif
  
#ifdef ELC1v41
#define RamSMSNum	0xA8F1EDCD
#define uitostr		0xA0514FC8+1
#endif

#ifdef S68Cv51
#define RamSMSNum	0xA8E48239
#define uitostr		0xA01B94D8+1
#endif

#ifdef M81Cv51
#define RamSMSNum	0xA8ED6AED
#define uitostr		0xA01F687C+1
#endif

#ifdef SL7Cv47
#define RamSMSNum	0xA8E57D7D
#define uitostr		0xA01F71AC+1
#endif

#endif