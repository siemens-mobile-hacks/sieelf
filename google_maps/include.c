#include "include.h"
//connect
int mode=0,
    sock=-1,
    connect_state=0,
    pbuf=0,
    zoom=0,
    cur_x=cub*2,
    cur_y=cub*3,
    all_traf=0,
    timer=50,
    mapi=0,
    mapj=0,
    Type=RIGHT;
    
    
char *buf=0,
     *tag=0;
IMGHDR *map[MAP_X][MAP_Y];

GBSTMR tmr;
char filename[128];
RAMNET *ramnet;
double Lat=0,Lon=0;

char req_buf[512];

char *maptype[5]={"街道","手机","卫星", "地形", "混合"};
char *clr[3]={"红","绿","蓝"};
char *format[3]={"png","jpg","gif"};
char *type[3]={"文本","图片","部分图片"};

double mlat=0,mlon=0;

