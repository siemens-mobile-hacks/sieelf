/*
  ������ SieGet Downloader
                          */

//inetapi.h
//��������������� ������� ��� ��������� ������ ������ ������� �� ������ �������

#ifndef _INETAPI_H_
#define _INETAPI_H_

#define RECV_RESULT_ERROR 0
#define RECV_RESULT_OK 1

typedef void (*RecvCallbackProc)(int res, void *data, int size);

//��������� ������, ���������� ����� ������� �������.
//����������, ������� �� ����������� ��������.
//����� ������ � ��� ������ ������������ � ���������� data � size.
void GetDataByReq(const char *req, int ip, short port, RecvCallbackProc rproc);

#endif
