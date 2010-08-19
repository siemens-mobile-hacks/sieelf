


//����������� ���������
char nopngf_msg[256];
char nopng_msg[256]="� ����� � ������ ������ �������� ���� png_help.txt, ��� ������� ����������� png-�����, � ������ (���������) �����������.";
char pngsize_msg[256]="PNG - �����:\n0.png - 9.png,\n1s.png - 9s.png ������ ����� ���������� ����������, ��������, 10x10 ��� 15x10!";
char bgsizef_msg[256];
char bgsize_msg[256]="PNG - �����:\nbgg.png � bgm.png ��� ������ �������� ������ ���� �����������:\n";
char nothelp_msg[256]="��� ����� �������:\ncfg\\SuDoKu.hlp";
char sudsizef_msg[256];
char sudsize_msg[256]="������ png - �����:\nsudoku.png ��� ������ �������� ������ ���� �� �����:\n";

extern int checkhelp();
extern char logo[];

extern int logovar;
extern int imgerrors;
extern int pngsizeerr;
extern int bgsizeerr;
extern int sudsizeerr;
extern int suh;

extern int mmenu;
extern int logow;

extern char t[];

//Timers
int ztimer=0;


void PutInCashe()
{
      DrawImg(0, 0, (int)bgg);
      DrawImg(0, 0, (int)bgm);
      DrawImg(0, 0, (int)sudoku);
      for (int i=0;i<30;i++) DrawImg(0, 0, (int)dig[i]);
      DrawRoundedFrame(0,0,SCRW,SCRH,0,0,0,white,white);
}


void LogoRender()
{ 
  if (imgerrors==0 && pngsizeerr==0 && bgsizeerr==0 && checkhelp()==1 && sudsizeerr==0)
   {
  
    startTimer(&ztimer,25);
  
    if (logovar == 1) SUBPROC((void *)PutInCashe);

  
    if (isTimer(&ztimer,0,19)==1)
     {
      DrawRoundedFrame(0,0,SCRW,SCRH,0,0,0,white,white);
      DrawImg((SCRW/2)-(GetImgWidth((int)logo)/2), (SCRH/2)-(GetImgHeight((int)logo)/2), (int)logo);
     }
    if (ztimer > 20 || bcfg_sys_logo_ena==0) {mmenu=1;logow=0;}
  
    if (logovar == 1) logovar = -1;
    logovar=1;
   }

    if (imgerrors==0 && pngsizeerr==1) DrawSoftHeaderLogo("�����","������ *.png",pngsize_msg);
  
    if (imgerrors==0 && bgsizeerr==1 && pngsizeerr==0) 
     {
      sprintf(bgsizef_msg,"%s%dx%d",bgsize_msg,SCRW,SCRH);
      DrawSoftHeaderLogo("�����","������ *.png",bgsizef_msg);
     }
    
     if (imgerrors==0 && bgsizeerr==0 && pngsizeerr==0 && sudsizeerr==1) 
     {
      sprintf(sudsizef_msg,"%s%d %s",sudsize_msg,suh,"��������.");
      DrawSoftHeaderLogo("�����","������ *.png",sudsizef_msg);
     }
    
     if (checkhelp()==0 && bgsizeerr==0 && pngsizeerr==0) DrawSoftHeaderLogo("�����","��� *.hlp",nothelp_msg);
   
    if (imgerrors>0)
     {
      sprintf(nopngf_msg,"%s %d %s\n%s","���",imgerrors,"png-�����(��)",nopng_msg);
      DrawSoftHeaderLogo("�����","��� *.png",nopngf_msg);
     }
  
}

