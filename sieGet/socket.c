/*
  ������ SieGet Downloader
                          */

#include "..\inc\swilib.h"
#include "socket.h"

//������ ����� ������ ������ ����, ����� ����������� ������
#define SocketError(x, y) SUBPROC((void *)(x->onError), x, y)


typedef struct _SOCKQ
{
  SOCKDATAHANDLER *data;
  struct _SOCKQ *next;
} SOCKQ;

typedef struct _DATAQ
{
  void *data;
  int size;
  struct _DATAQ *next;
  struct _DATAQ *prev;
} DATAQ;

DATAQ *sendq = NULL;

SOCKQ *sock_top = NULL;

//�������� ����� ������������������� ������
SOCKDATAHANDLER *GetSocketHandle(int sock)
{
  SOCKQ *tmp_sock = sock_top;
  while(tmp_sock)
  {
    if (tmp_sock->data->sock==sock)
      return tmp_sock->data;
    tmp_sock = tmp_sock->next;
  }
  return 0;
}

//��������� ������� (������ ������ � �������)
int CheckCepId()
{
  if (GBS_GetCurCepid()==MMI_CEPID) return 1;
  return 0;
}

//��������� ����� �� ip � �����
void SocketConnect(SOCKDATAHANDLER *sock, int ip, short port)
{
  if (CheckCepId())
  {
    SocketError(sock, SOCK_ERROR_INVALID_CEPID);
    return;
  }
  if(sock->sock<0)
  {
    SocketError(sock, SOCK_ERROR_INVALID_SOCKET);
    return;
  }

  SOCK_ADDR sa;
  sa.family=1;
  sa.port=htons(port);
  sa.ip=ip;
  if (connect(sock->sock,&sa,sizeof(sa))==-1)
  {
    SocketError(sock, SOCK_ERROR_CONNECTING);
    return;
  }
  sock->state = SOCK_CREATED;
}

//��������� ������
void SocketSend(SOCKDATAHANDLER *sock, const char *data, int size)
{
  if (CheckCepId())
  {
    SocketError(sock, SOCK_ERROR_INVALID_CEPID);
    return;
  }

  int send_res = send(sock->sock, data, size, 0);
  if (send_res==-1)
  {
    SocketError(sock, SOCK_ERROR_SENDING);
    return;
  }
  /*
  if (send_res<size) // ���� �� ���� ���� �������, ���� ���������� ����� �������. ���� ������� �� �����.
  {
  }
  */

}

//������� �����
void SocketClose(SOCKDATAHANDLER *sock)
{
  if (CheckCepId())
  {
    SocketError(sock, SOCK_ERROR_INVALID_CEPID);
    return;
  }
  if(sock->sock<0)
  {
    SocketError(sock, SOCK_ERROR_INVALID_SOCKET);
    return;
  }

  shutdown(sock->sock,2);
  closesocket(sock->sock);

  sock->state = SOCK_UNDEF;
}

//������� ����� �� ���������
void SocketUnReg(SOCKDATAHANDLER *sock)
{
  SOCKQ *tmp_sock = sock_top;
  if (sock_top->data==sock)
  {
    sock_top = sock_top->next;
    mfree(tmp_sock);
  }
  else
  {
    SOCKQ *prev_sock = sock_top;
    tmp_sock = sock_top->next;
    while (tmp_sock)
    {
      if (tmp_sock->data==sock)
      {
        prev_sock->next = tmp_sock->next;
        mfree(tmp_sock);
      }
      prev_sock = tmp_sock;
      tmp_sock = tmp_sock->next;
    }
  }
}

//������� ����� � ��������� ��� � ������� ���������
void SocketCreate(SOCKDATAHANDLER *sock)
{
  if (CheckCepId())
  {
    SocketError(sock, SOCK_ERROR_INVALID_CEPID);
    return;
  }

  sock->sock = socket(1,1,0);
  if(sock->sock<0)
  {
    SocketError(sock, SOCK_ERROR_CREATING);
    return;
  }

  sock->state = SOCK_CREATED;

  SOCKQ *tmp_sock = malloc(sizeof(SOCKQ)); //������� �����, ��������� ��� � ������
  tmp_sock->data = sock;
  tmp_sock->next = sock_top;
  sock_top = tmp_sock;

  SUBPROC((void *)(sock->onCreate), sock);
}

//---------------------------------------------------------------
//��������� ���������, ��������� � �������
int onSockEvent(int sock, int event)
{
  SOCKDATAHANDLER *hndl;
  if (hndl = GetSocketHandle(sock))
  {
    //���� ��� �����
    switch(event)
    {
    case ENIP_SOCK_CONNECTED: //���������� ����� ����� �����������
      SUBPROC((void *)(hndl->onConnected), hndl);
      break;

    case ENIP_SOCK_DATA_READ: //���������� ������ � ���������
      SUBPROC((void *)(hndl->onDataRead), hndl);
      break;

    case ENIP_SOCK_REMOTE_CLOSED: //���������� ��������� ��������
      SUBPROC((void *)(hndl->onRemoteClose), hndl);
      break;

    case ENIP_SOCK_CLOSED: //���������� �������� ��������
      SUBPROC((void*)(hndl->onClose), hndl);
      break;

    case ENIP_BUFFER_FREE: //����� ������� ����
      //To be implemented...
      break;

    case ENIP_BUFFER_FREE1: //����� ������� ���� (� ��� �������? - ��)
      //To be implemented...
      break;
    }

    return 0; //����� ���, �� ��� ����������
  }
  return 1; //����� �����, ���������� ��������� ������ �� �������
}
