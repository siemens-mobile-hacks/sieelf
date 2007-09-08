/*
  ������ SieGet Downloader
                          */

//socketapi.h
//��������������� ��������� ��������� �������

#ifndef _SOCKETAPI_H_
#define _SOCKETAPI_H_

typedef enum
{
  SOCK_UNDEF,
  SOCK_CREATED,
  SOCK_CONNECTED
} SOCK_STATE;

typedef enum
{
  SOCK_ERROR_CREATING,
  SOCK_ERROR_CONNECTING,
  SOCK_ERROR_SENDING,
  SOCK_ERROR_CLOSING,
  SOCK_ERROR_INVALID_SOCKET,
  SOCK_ERROR_INVALID_CEPID
} SOCK_ERROR;

typedef void (*socket_handle_func)(void* sockdata);
typedef void (*socket_error_handle_func)(void* sockdata, SOCK_ERROR err);

typedef struct
{
  int sock;
  SOCK_STATE state;
  socket_handle_func onCreate;
  socket_handle_func onDataRead;
  socket_handle_func onConnected;
  socket_handle_func onClose;
  socket_handle_func onRemoteClose;
  socket_error_handle_func onError;
  void *data; //�������������� ����, ����� ����� ������ ���.������ �������
} SOCKDATAHANDLER;

//��������� ����� �� ip � �����
//ip ������ ����� ������� ������ ���� (htonl)
void SocketConnect(SOCKDATAHANDLER *sock, int ip, short port);

//��������� ������
void SocketSend(SOCKDATAHANDLER *sock, const char *data, int size);

//������� �����
void SocketClose(SOCKDATAHANDLER *sock);

//������� ����� � ��������� ��� � ������� ���������
void SocketCreate(SOCKDATAHANDLER *sock);

//������� ����� �� ���������
void SocketUnReg(SOCKDATAHANDLER *sock);
#endif
