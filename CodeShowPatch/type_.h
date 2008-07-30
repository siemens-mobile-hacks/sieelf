typedef unsigned char  byte;
typedef unsigned short word;
typedef unsigned int   dword;
typedef unsigned int   uint;

typedef struct WString{
	word* pstr;
	int unknown[3];
	int buflen;
}WSTRING; 

typedef struct {
    byte Flag;
    byte ID;
    byte Version;
    byte Year;
    byte Month;
    byte Day;
    byte ProvinceNameLen;
    byte CityNameLen;
    dword CodeTableOffset;
    dword CodeCount;
    dword LocaleTableOffset;
    dword LocaleCount;
    dword ProvinceTableOffset;
    dword ProvinceCount;
    dword CityTableOffset;
    dword CityCount;
}CODESHOWHEAD;

#pragma pack(2)
typedef struct {
    word ProvinceName[3];
    word StartOffset;
    word EndOffset;
}PROVINCE;

typedef struct {
    word CityName[6];
    word LocaleNo     :10;
    word ProvinceNo   :6;
}CITY;
#pragma pack()

typedef struct {
    word LocaleNo;
    word CityNo;
}LOCALE;

typedef struct {
    word CRNo;
    byte Names[14];
}CRNO;
