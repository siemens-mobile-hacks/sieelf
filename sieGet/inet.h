/*
  ������ SieGet Downloader
                          */

//inetapi.h
//��������������� ������� ��� ��������� ������ ������ ������� �� ������ �������

#ifndef _INETAPI_H_
#define _INETAPI_H_

#define RECV_RESULT_ERROR 0
#define RECV_RESULT_OK 1

class HttpGet: public Socket
{
public:
  virtual void onCreate();
  virtual void onDataRead();
  virtual void onConnected();
  virtual void onClose();
  virtual void onRemoteClose();
  virtual void onError(SOCK_ERROR err);

  virtual void onFinish(int result) = 0;
  virtual void onEvent(int event, int data) = 0;

  void Start(const char *req, int ip, short port);

  char *body;
  int body_size;
  char *headers;
  int headers_size;

  HttpGet(SocketHandler *handler);
  ~HttpGet();
private:
  char *buf;
  int buf_size;
  int recvsize;

  int ip;
  short port;
  const char *req;
};

#endif
