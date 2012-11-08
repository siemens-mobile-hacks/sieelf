#include "include.h"

void create_connect()
{
mode=1;
//send_or_connect=SEND;
SOCK_ADDR sa;

connect_state=0;
sock=socket(1,1,0);
if (sock!=-1)
 {
   sa.family=1;
   sa.port=htons(80);
   sa.ip=htonl(IP_ADDR(213,138,73,90));
    if(connect(sock,&sa,sizeof(sa))!=-1)connect_state=1;
    else
    {
      closesocket(sock);
      sock=-1;
    }
  }
}


void send_req(void)
{
if(buf==0)buf=malloc(BUFFSIZE);
mode=1;
CreateRequest(); 
int j=send(sock,req_buf,strlen(req_buf),0);
all_traf+=j;
connect_state=2;
}

void end_socket(void)
{
   if (sock>=0)
     {
      shutdown(sock,2);
      closesocket(sock);
      //send_or_connect=CONNECT;
      connect_state=0;
      SUBPROC((void *)create_connect);
     }
}


static int parsheader(char *a)
{
int header_size=0;
while(header_size<strlen(a)-3)
{
  if(a[header_size]=='\r'&&a[header_size+1]=='\n'&&a[header_size+2]=='\r'&&a[header_size+3]=='\n')return header_size+4;
  header_size++;
}
return 0;
}


void get_answer()
{
   tag=0;
   
   int header_size=0,
        image_size=0;
  buf=realloc(buf,pbuf+BUFFSIZE); 
  int j=recv(sock,buf+pbuf,BUFFSIZE,0);
  pbuf+=j;
   all_traf+=j;
  

  
  if(header_size==0||image_size==0)
   {
      if(strstr(buf,"\r\n\r\n"))
       {
         if(header_size==0)header_size=parsheader(buf);
         if(image_size==0&&(tag=findtag(buf,"Content-Length:")))
           {
             valuetag(tag, filename, sizeof(filename)-1);
             image_size=(int)str_to_double(filename);
            }
       }
   }
  
  if(pbuf>=(image_size+header_size))
  {
    buf[pbuf]=0;
    save_image_in_cache(0);
  }
}

 void CreateRequest()
{

if(!Lat||!Lon)
{
ramnet=RamNet();
char *p=((char*)ramnet)-11;
char cc1=*p;
char cc2=*(p+1);
char nc=*(p+2);
sprintf(req_buf,"GET /siemens/maps/index.php?cell=%d&op=%d&cc=%d&lac=%d",ramnet[0].ci,(nc&0x0F)*10+(nc>>4),(cc1&0x0F)*100+(cc1>>4)*10+(cc2&0x0F),ramnet[0].lac);  
}
else sprintf(req_buf ,"GET /siemens/maps/index.php?lat=%f&lon=%f",Lat,Lon);

if(mlat&&mlon)sprintf(req_buf ,"%s&mlat=%f&mlon=%f",req_buf,mlat,mlon);

sprintf(req_buf ,"%s&zoom=%d&t=%s&frmt=%s&szx=%d&szy=%d&q=%s&imgx=%d&imgy=%d&cub=%d&color=blue"
" HTTP/1.1\r\nHost: 213.138.73.90\r\n\r\n",req_buf,zoom,maptype[map_type],format[0],ScreenW(),ScreenH(),type[2],mapi,mapj,cub);
}

void c()
{

  mode=1;
  FSTATS fs;
 sprintf(filename,"%scache%f_%f\\",fname,Lon,Lat);
 sprintf(filename,"%smap_%d_%d_%d_%d.png",filename,mapi,mapj,zoom,map_type);
 
 if(GetFileStats(filename,&fs,0)!=-1)SUBPROC((void*)save_image_in_cache,1);
 else
 {
 SUBPROC((void*)send_req);}
}
