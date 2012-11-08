#include "..\inc\swilib.h"
#include <math.h>

#ifdef ELKA
#define FONT 9
#define cub 40
#else
#define FONT 7
#define cub 22
#endif
#define MAP_X 6
#define MAP_Y 8
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define BUFFSIZE 2048
//connect
extern int sock,connect_state;
extern char *buf;
extern int pbuf;

extern char filename[128];
void save_image_in_cache(int n);
void DrwImg(IMGHDR *img, int x, int y);

extern GBSTMR tmr;
extern int cur_x,cur_y;

extern void send_req(void),get_answer(void),end_socket(void), CreateRequest();

extern const char fname[128],name[2];
extern const int frmt,map_type;
extern  int zoom;
extern const int Zoom;
extern int mode;
char *valuetag(char *src,char *dst, int maxlen);
char * findtag(char *src, char *tag);

extern double Lat,Lon;
double str_to_double(const char *str);
double LToX(double x);
double LToY(double y);
double XToL(double x);
double YToL(double x);


extern IMGHDR *map[MAP_X][MAP_Y];
extern char *tag;
extern int mapi,mapj;

extern RAMNET *ramnet;

extern int Type;
extern char req_buf[512];
extern char *maptype[5];

extern char *format[3];
extern char *type[3];
void free_imghdr(IMGHDR *i);
extern double mlat,mlon;

void c();
extern int all_traf;
void create_connect();
extern int timer;

