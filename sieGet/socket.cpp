/*
  ������ SieGet Downloader
                          */

#include "..\inc\swilib.h"
#include "socket.h"

extern void Log(char *str);

//�������� ����� ������������������� ������
Socket *SocketHandler::GetSocket(int sock)
{
  SocketQ *tmp_sock = queue;
  while(tmp_sock)
  {
    if (tmp_sock->sock->id==sock)
      return tmp_sock->sock;
    tmp_sock = tmp_sock->next;
  }
  return 0;
}

void SocketHandler::Reg(Socket *sock)
{
  SocketQ *tmp_sock = new SocketQ; //������� �����, ��������� ��� � ������
  tmp_sock->sock = sock;
  tmp_sock->next = queue;
  queue = tmp_sock;
}

//������� ����� �� ���������
void SocketHandler::UnReg(Socket *sock)
{
  SocketQ *tmp_sock = queue;
  if (queue->sock==sock)
  {
    queue = queue->next;
    delete tmp_sock;
  }
  else
  {
    SocketQ *prev_sock = queue;
    tmp_sock = queue->next;
    while (tmp_sock)
    {
      if (tmp_sock->sock==sock)
      {
        prev_sock->next = tmp_sock->next;
        delete tmp_sock;
      }
      prev_sock = tmp_sock;
      tmp_sock = tmp_sock->next;
    }
  }
}

void SocketHandler::onSockEvent(int sock, int event)
{
  Socket *sock_class;
  if (sock_class = GetSocket(sock))
  {
    //���� ��� �����
    switch(event)
    {
    case ENIP_SOCK_CONNECTED: //���������� ����� ����� �����������
      sock_class->state = SOCK_CONNECTED;
      sock_class->onConnected();
      break;

    case ENIP_SOCK_DATA_READ: //���������� ������ � ���������
      sock_class->onDataRead();
      break;

    case ENIP_SOCK_REMOTE_CLOSED: //���������� ��������� ��������
      sock_class->onRemoteClose();
      break;

    case ENIP_SOCK_CLOSED: //���������� �������� ��������
      sock_class->id = -1;
      sock_class->onClose();
      break;

    case ENIP_BUFFER_FREE: //����� ������� ����
      //To be implemented...
      break;

    case ENIP_BUFFER_FREE1: //����� ������� ���� (� ��� �������? - ��)
      //To be implemented...
      break;
    }
  }
}

SocketHandler::SocketHandler()
{
  queue = NULL;
}

SocketHandler::~SocketHandler()
{
  SocketQ *tmp;
  while (tmp = queue)
  {
    queue = queue->next;
    delete tmp;
  }
}

//---------------------------------------------------

//��������� ������� (������ ������ � �������)
int CheckCepId()
{
  if (GBS_GetCurCepid()==MMI_CEPID) return 1;
  return 0;
}

//---------------------------------------------------

SOCK_STATE Socket::GetState() const
{
  return state;
}

//��������� ����� �� ip � �����
void Socket::Connect(int ip, short port)
{
  if (CheckCepId())
  {
    onError(SOCK_ERROR_INVALID_CEPID);
    return;
  }
  if(id<0)
  {
    onError(SOCK_ERROR_INVALID_SOCKET);
    return;
  }

  SOCK_ADDR sa;
  sa.family=1;
  sa.port=htons(port);
  sa.ip=ip;
  if (connect(id, &sa, sizeof(sa))==-1)
  {
    onError(SOCK_ERROR_CONNECTING);
    return;
  }
  state = SOCK_CREATED;
}

//��������� ������
void Socket::Send(const char *data, int size)
{
  if (CheckCepId())
  {
    onError(SOCK_ERROR_INVALID_CEPID);
    return;
  }

  int send_res = send(id, data, size, 0);
  if (send_res==-1)
  {
    onError(SOCK_ERROR_SENDING);
    return;
  }
  /*
  if (send_res<size) // ���� �� ���� ���� �������, ���� ���������� ����� �������. ���� ������� �� �����.
  {
  }
  */

}

//������� ������
int Socket::Recv(char *data, int size)
{
  return recv(id, data, size, 0);
}

//������� �����
void Socket::Close()
{
  if (CheckCepId())
  {
    onError(SOCK_ERROR_INVALID_CEPID);
    return;
  }
  if(id<0)
  {
    onError(SOCK_ERROR_INVALID_SOCKET);
    return;
  }

  shutdown(id, 2);
  closesocket(id);

  state = SOCK_UNDEF;
}

void Socket::Create()
{
  if (CheckCepId())
  {
    onError(SOCK_ERROR_INVALID_CEPID);
    return;
  }

  id = socket(1,1,0);
  if(id<0)
  {
    onError(SOCK_ERROR_CREATING);
    return;
  }

  state = SOCK_CREATED;
  onCreate();
}

//������� �����
Socket::Socket(SocketHandler *_handler)
{
  state = SOCK_UNDEF;

  handler = _handler;
  handler->Reg(this);
}

// ����������� ������
Socket::~Socket()
{

}
